
// mesh_node_demo.h generated from ../../example/mesh_node_demo.gatt for BTstack
// it needs to be regenerated when the .gatt file is updated. 

// To generate mesh_node_demo.h:
// ../../tool/compile_gatt.py ../../example/mesh_node_demo.gatt mesh_node_demo.h

// att db format version 1

// binary attribute representation:
// - size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#ifndef MESH_NODE_DEMO1_H
#define MESH_NODE_DEMO1_H

#include <stdint.h>

// Reference: https://en.cppreference.com/w/cpp/feature_test
#if __cplusplus >= 200704L
constexpr
#endif
const uint8_t profile_data_provisioning[] =
{
    // ATT DB Version
    1,

    // 0x0001 PRIMARY_SERVICE-GAP_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x00, 0x18, 
    // 0x0002 CHARACTERISTIC-GAP_DEVICE_NAME-READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x02, 0x03, 0x00, 0x00, 0x2a, 
    // 0x0003 VALUE-GAP_DEVICE_NAME-READ | DYNAMIC-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x03, 0x00, 0x00, 0x2a, 
    // #import <mesh_provisioning_service.gatt> -- BEGIN
    // Specification Type org.bluetooth.service.mesh_provisioning
    // https://www.bluetooth.com/api/gatt/xmlfile?xmlFileName=org.bluetooth.service.mesh_provisioning.xml
    // Mesh Provisioning Service 1827

    // 0x0004 PRIMARY_SERVICE-ORG_BLUETOOTH_SERVICE_MESH_PROVISIONING
    0x0a, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x28, 0x27, 0x18, 
    // 0x0005 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROVISIONING_DATA_IN-DYNAMIC | WRITE_WITHOUT_RESPONSE
    0x0d, 0x00, 0x02, 0x00, 0x05, 0x00, 0x03, 0x28, 0x04, 0x06, 0x00, 0xdb, 0x2a, 
    // 0x0006 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROVISIONING_DATA_IN-DYNAMIC | WRITE_WITHOUT_RESPONSE-''
    // WRITE_ANYBODY
    0x08, 0x00, 0x04, 0x01, 0x06, 0x00, 0xdb, 0x2a, 
    // 0x0007 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROVISIONING_DATA_OUT-DYNAMIC | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x07, 0x00, 0x03, 0x28, 0x10, 0x08, 0x00, 0xdc, 0x2a, 
    // 0x0008 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROVISIONING_DATA_OUT-DYNAMIC | NOTIFY-''
    // 
    0x08, 0x00, 0x00, 0x01, 0x08, 0x00, 0xdc, 0x2a, 
    // 0x0009 CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a, 0x00, 0x0e, 0x01, 0x09, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // #import <mesh_provisioning_service.gatt> -- END

    // END
    0x00, 0x00, 
}; // total size 97 bytes 

#endif /* MESH_NODE_DEMO1_H */
