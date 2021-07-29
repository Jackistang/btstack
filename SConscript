from building import *

cwd = GetCurrentDir()

inc = []
src = []

# Example
src += [
    # 'example/gap_le_advertisements.c'
    'example/gatt_counter.c'
]

#     platform/posix/btstack_uart_posix.c   not have a instance
#     platform/posix/le_device_db_fs.c    complict with le_device_db_tlv.c
#     src/hci_transport_h4.c    complict with hm component
#     platform/posix/btstack_run_loop_posix.c   complict with btstack_run_loop_rtthread.c
# Core
src += Split('''
    platform/rtthread/btstack_run_loop_rtthread.c

    platform/posix/btstack_stdin_posix.c
    platform/posix/btstack_tlv_posix.c
    platform/posix/hci_dump_posix_fs.c
    platform/posix/hci_dump_posix_stdout.c
    
    chipset/zephyr/btstack_chipset_zephyr.c

    port/rtthread/main.c

    src/ble/le_device_db_tlv.c
	src/btstack_memory.c
	src/btstack_linked_list.c
	src/btstack_memory_pool.c
    src/btstack_run_loop_base.c
	src/btstack_run_loop.c
	src/btstack_util.c
''')

# Common
src += Split('''
	src/ad_parser.c
	src/hci.c
	src/hci_cmd.c
	src/hci_dump.c
	src/l2cap.c
	src/l2cap_signaling.c
	src/btstack_tlv.c
	src/btstack_crypto.c
	src/ble/sm.c

    3rd-party/micro-ecc/uECC.c
''')

# ATT
src += Split('''
    src/ble/att_dispatch.c
''')

# GATT_Server
src += Split('''
    src/ble/att_db.c
    src/ble/att_server.c
    src/ble/gatt-service/battery_service_server.c
''')

# GATT_Client
src += Split('''
    src/ble/gatt_client.c
    src/ble/gatt-service/battery_service_client.c
    src/ble/gatt-service/device_information_service_client.c
    src/ble/gatt-service/scan_parameters_service_client.c
    src/ble/gatt-service/hids_client.c
''')

inc += [
    cwd + '/port/rtthread',
    cwd + '/platform/posix',
    cwd + '/platform/rtthread',
    cwd + '/chipset/zephyr',

    cwd + '/src',
    cwd + '/src/ble',
    cwd + '/src/mesh',

    cwd + '/3rd-party/micro-ecc'
]

group = DefineGroup('btstack', src, depend = [''], CPPPATH = inc)

Return('group')