- CORE：btstack 运行核心组件
- COMMON：通用工具
- CLASSIC：Bluetooth Classic 需要
- SDP_CLIENT：Classic sdp 服务
- ATT：BLE att
- GATT_SERVER：BLE
- GATT_CLIENT：BLE
- PAN：CLASSIC
- MBEDTLS：未使用
- LWIP_*：网络相关
- SBC_*：音频相关
- CVSD_PLC：音频相关
- AVDTP：Classic
- AVRCP：Classic
- HXCMOD_PLAYER：Classic，音视频相关
- MESH：Mesh 相关



```makefile
# List of Examples that only use Bluetooth LE

EXAMPLES_LE_ONLY=           		\
	ancs_client_demo        		\
	att_delayed_response    		\
	gap_le_advertisements   		\
	gatt_battery_query      		\
	gatt_browser            		\
	gatt_counter            		\
	gatt_device_information_query	\
	gatt_heart_rate_client  		\
	gatt_streamer_server    		\
	hog_boot_host_demo      		\
	hog_host_demo      		        \
	hog_keyboard_demo       		\
	hog_mouse_demo          		\
	le_data_channel_client  		\
	le_data_channel_server  		\
	le_mitm                 		\
	le_streamer_client      		\
	mesh_node_demo          		\
	nordic_spp_le_counter   		\
	nordic_spp_le_streamer  		\
	sm_pairing_central      		\
	sm_pairing_peripheral   		\
	ublox_spp_le_counter    		\
```

BLE 相关内容：CORE, 	, ATT, GATT_SERVER, GATT_CLIENT 。

头文件路径：src/ble, src/mesh, src





le_device_db：LE 设备的 db

- posix/le_device_db_fs.c 利用 POSIX 环境下的文件实现的数据库（持久化）
- le_device_db_memory.c 利用 memory 实现的数据库（不可持久）
- le_device_db_tlv.c 利用移植的接口 tag-value 实现的数据库（持久化）