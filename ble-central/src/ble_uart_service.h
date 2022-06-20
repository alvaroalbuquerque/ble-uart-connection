#pragma once

#include <zephyr.h>
#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <sys/util.h>
#include <ble_application.h>


typedef void (* ble_uart_service_tx_callback) (const uint8_t *data, size_t length);

int ble_uart_service_register(/*const ble_uart_service_tx_callback callback*/);
int ble_service_transmit(const uint8_t *buffer, size_t len, struct bt_conn *conn);