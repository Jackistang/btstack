/*
 * Copyright (C) 2014 BlueKitchen GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the names of
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 * 4. Any redistribution, use, or modification is done solely for
 *    personal benefit and not for any commercial purpose or for
 *    monetary gain.
 *
 * THIS SOFTWARE IS PROVIDED BY BLUEKITCHEN GMBH AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MATTHIAS
 * RINGWALD OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Please inquire about commercial licensing options at 
 * contact@bluekitchen-gmbh.com
 *
 */

#define BTSTACK_FILE__ "main.c"

// *****************************************************************************
//
// minimal setup for HCI code
//
// *****************************************************************************

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "btstack_config.h"

#include "btstack_debug.h"
#include "btstack_event.h"
#include "btstack_memory.h"
#include "btstack_run_loop.h"
#include "btstack_run_loop_rtthread.h"
#include "btstack_uart.h"
#include "bluetooth_company_id.h"
#include "ble/le_device_db.h"
#include "hci.h"
#include "hci_dump.h"
#include "hci_dump_rtthread_stdout.h"
#include "hci_transport.h"
#include "hci_transport_h4.h"
#include "btstack_stdin.h"
#include "btstack_chipset_zephyr.h"

int btstack_main(int argc, const char * argv[]);
const btstack_uart_t * btstack_uart_rtthread_instance(void);

static hci_transport_config_uart_t config = {
    HCI_TRANSPORT_CONFIG_UART,
    115200,
    0,  // main baudrate
    1,  // flow control
    NULL,
};

static btstack_packet_callback_registration_t hci_event_callback_registration;

static const uint8_t read_static_address_command_complete_prefix[] = { 0x0e, 0x1b, 0x01, 0x09, 0xfc };
static bd_addr_t static_address;

static void packet_handler (uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    if (packet_type != HCI_EVENT_PACKET) return;
    switch (hci_event_packet_get_type(packet)){
        case BTSTACK_EVENT_STATE:
            if (btstack_event_state_get_state(packet) != HCI_STATE_WORKING) break;
            printf("BTstack up and running as %s\n",  bd_addr_to_str(static_address));

            le_device_db_init();

            break;
        case HCI_EVENT_COMMAND_COMPLETE:
            if (memcmp(packet, read_static_address_command_complete_prefix, sizeof(read_static_address_command_complete_prefix)) == 0){
                reverse_48(&packet[7], static_address);
                gap_random_address_set(static_address);
            }
            break;
        default:
            break;
    }
}

static int led_state = 0;
void hal_led_toggle(void){
    led_state = 1 - led_state;
    printf("LED State %u\n", led_state);
}

int rt_btstack_main(int argc, const char * argv[]){

	/// GET STARTED with BTstack ///
	btstack_memory_init();
    btstack_run_loop_init(btstack_run_loop_rtthread_get_instance());

    // const hci_dump_t * hci_dump_impl = hci_dump_rtthread_stdout_get_instance();
    // hci_dump_init(hci_dump_impl);

    // pick serial port
    config.device_name = "uart1"; // PCA10056 nRF52840 

    // accept path from command line
    if (argc >= 3 && strcmp(argv[1], "-u") == 0){
        config.device_name = argv[2];
        argc -= 2;
        memmove(&argv[1], &argv[3], (argc-1) * sizeof(char *));
    }
    printf("H4 device: %s\n", config.device_name);

    // init HCI
    const btstack_uart_t * uart_driver = btstack_uart_rtthread_instance();
	const hci_transport_t * transport = hci_transport_h4_instance_for_uart(uart_driver);
	hci_init(transport, (void*) &config);

    hci_set_chipset(btstack_chipset_zephyr_instance());
    
    // inform about BTstack state
    hci_event_callback_registration.callback = &packet_handler;
    hci_add_event_handler(&hci_event_callback_registration);

    // setup app
    btstack_main(argc, argv);

    // sm required to setup static random Bluetooth address
    sm_init();

    // go
    btstack_run_loop_execute();    

    return 0;
}

#include <rtthread.h>
static void btstack_thread_entry(void *args)
{
    rt_btstack_main(0, NULL);
}

static int btstack_rtthread_port_init(void)
{
    rt_thread_t tid = rt_thread_create("btstack", btstack_thread_entry, NULL, 2048, 10, 10);
    
    rt_thread_startup(tid);
    
    return RT_EOK;
}
INIT_APP_EXPORT(btstack_rtthread_port_init);
