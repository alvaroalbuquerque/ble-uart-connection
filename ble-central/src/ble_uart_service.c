#include <ble_uart_service.h>

#define BLE_UART_SERVICE_TX_CHAR_OFFSET    3

static ble_uart_service_tx_callback tx_callback = NULL;
static uint8_t read_info = NULL;

static struct bt_uuid_128 ble_uart_svc_uuid = BT_UUID_INIT_128(
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0x00, 0x89, 0x67, 0x43, 0x21);

static struct bt_uuid_128 ble_uart_rx_uuid = BT_UUID_INIT_128(
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0x01, 0x89, 0x67, 0x43, 0x21);

static struct bt_uuid_128 ble_uart_tx_uuid = BT_UUID_INIT_128(
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0x02, 0x89, 0x67, 0x43, 0x21);

static ssize_t write_function (struct bt_conn *conn,
					 const struct bt_gatt_attr *attr,
					 const void *buf, uint16_t len,
					 uint16_t offset, uint8_t flags) {
	(void)conn;
	(void)attr;
	(void)offset;
	(void)flags;

    if(tx_callback) {
        tx_callback((const uint8_t *)buf,len);
    }

    return len;
}

static ssize_t read_function (struct bt_conn *conn,
					 const struct bt_gatt_attr *attr,
					 const void *buf, uint16_t len,
					 uint16_t offset, uint8_t flags) {
	(void)conn;
	(void)attr;
	(void)offset;
	(void)flags;

	const uint8_t *read_info_aux = buf;

	if (!len)
	{
		return (-1);
	}

	read_info = read_info_aux;
    return len;
}

static struct bt_gatt_attr ble_uart_attr_table[] = {
	BT_GATT_PRIMARY_SERVICE(&ble_uart_svc_uuid),
	BT_GATT_CHARACTERISTIC(&ble_uart_rx_uuid.uuid, BT_GATT_CHRC_READ,
			BT_GATT_PERM_READ, read_function, NULL, NULL),
	BT_GATT_CHARACTERISTIC(&ble_uart_tx_uuid.uuid, BT_GATT_CHRC_WRITE,
			BT_GATT_PERM_WRITE, NULL, write_function, NULL)
};

static struct bt_gatt_service ble_uart_service = BT_GATT_SERVICE(ble_uart_attr_table);


int ble_uart_service_register(const ble_uart_service_tx_callback callback) {
    tx_callback = callback;
	return 	bt_gatt_service_register(&ble_uart_service);
}

// quando recebe a mensagem em maiúsculo, irá printar no terminal
int ble_uart_service_receive(const uint8_t *buffer, size_t len) {

	if(!buffer || !len) {
		return -1;
	}
	
	//printk("Hello! I'm using Zephyr %s on %s, a %s board. \n\n", KERNEL_VERSION_STRING, CONFIG_BOARD, CONFIG_ARCH);
	printk("Hello World!!!. \n\n");
}