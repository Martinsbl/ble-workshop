
#ifndef BLE_SERVO_H__
#define BLE_SERVO_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

/* The base UUID (also known as vendor specific UUID) for our Service and Characteristic 
 * Properly formatted it looks like this: 
 * F364xxxx-01B0-4240-BA50-05CA55BF8ABC
 */
#define SERVO_BASE_UUID		   {0xBC, 0x8A, 0xBF, 0x55, 0xCA, 0x05, 0x50, 0xBA, \
				    0x40, 0x42, 0xB0, 0x01, 0x00, 0x00, 0x64, 0xF3}

#define SERVO_SERVICE_UUID	    0x5E55 // 16 bit UUID for our Service
#define SERVO_CHARACTERISTIC_UUID   0x5E5C // 16 bit UUID for our Characteristic



/** Servo Service event handler. 
 * This is just a simple event handler used to pass new servo values from ble_servo.c to main.c
 */
typedef void (* ble_servo_evt_handler_t) (uint16_t servo_value);


/**@brief Servo Service structure. This contains various status information for the service. */
typedef struct
{
    ble_servo_evt_handler_t  evt_handler;               /**< Event handler to be called for handling events in the Servo Service. */
    uint16_t                 service_handle;            /**< Handle of Servo Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t servo_value_handles;	/**< Handles related to the Servo Level characteristic. */
    uint8_t                  uuid_index;		/**< The softdevice will make a table of UUIDs. This variable is used to refer to an index in that table to get the base UUID. */
}ble_servo_t;

/** Function for initializing our Servo service. 
 */
ret_code_t ble_servo_service_init(ble_servo_t * p_servo);

/** Function used to propagate BLE events from main.c into ble_servo.c
 */
void ble_servo_on_ble_evt(ble_evt_t const * p_ble_evt, ble_servo_t * p_ble_servo);

#endif // BLE_SERVO_H__

/** @} */
