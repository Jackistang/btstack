from building import *

cwd = GetCurrentDir()

inc = []
src = []

# Example
src += [
    # 'example/gap_le_advertisements.c'
    'example/gatt_counter.c'
    # 'example/mesh_node_demo.c'
]

src += Split('''
    src/hci_transport_h4.c
    platform/rtthread/btstack_uart_rtthread.c
    port/rtthread/main.c
''')
inc += [ cwd + '/port/rtthread' ]

# Core
src += Split('''
    platform/rtthread/btstack_run_loop_rtthread.c
    platform/rtthread/hci_dump_rtthread_stdout.c
    
    chipset/zephyr/btstack_chipset_zephyr.c

    src/ble/le_device_db_memory.c
    
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

# Mesh
src += Split('''
    src/ble/gatt-service/mesh_provisioning_service_server.c
    src/ble/gatt-service/mesh_proxy_service_server.c

    src/mesh/adv_bearer.c
    src/mesh/mesh_health_server.c
    src/mesh/beacon.c
    src/mesh/mesh_iv_index_seq_number.c
    src/mesh/gatt_bearer.c
    src/mesh/mesh_keys.c
    src/mesh/mesh_access.c
    src/mesh/mesh_lower_transport.c
    src/mesh/mesh.c
    src/mesh/mesh_network.c
    src/mesh/mesh_configuration_client.c
    src/mesh/mesh_node.c
    src/mesh/mesh_configuration_server.c
    src/mesh/mesh_peer.c
    src/mesh/mesh_crypto.c
    src/mesh/mesh_proxy.c
    src/mesh/mesh_foundation.c
    src/mesh/mesh_upper_transport.c
    src/mesh/mesh_generic_default_transition_time_client.c
    src/mesh/mesh_virtual_addresses.c
    src/mesh/mesh_generic_default_transition_time_server.c
    src/mesh/pb_adv.c
    src/mesh/mesh_generic_level_client.c
    src/mesh/pb_gatt.c
    src/mesh/mesh_generic_level_server.c
    src/mesh/provisioning.c
    src/mesh/mesh_generic_on_off_client.c
    src/mesh/provisioning_device.c
    src/mesh/mesh_generic_on_off_server.c
    src/mesh/provisioning_provisioner.c
''')

inc += [
    cwd + '/platform/rtthread',
    cwd + '/chipset/zephyr',

    cwd + '/src',
    cwd + '/src/ble',
    cwd + '/src/mesh',

    cwd + '/3rd-party/micro-ecc'
]

group = DefineGroup('btstack', src, depend = [''], CPPPATH = inc)

Return('group')