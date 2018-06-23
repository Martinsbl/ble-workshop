
#ifndef BLE_SERVO_H__
#define BLE_SERVO_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

/**@brief Macro for defining a ble_servo instance.
 *
 * @param   _name  Name of the instance.
 * @hideinitializer
 */
#define BLE_SERVO_DEF(_name)                          \
    static ble_servo_t _name;                         \
    NRF_SDH_BLE_OBSERVER(_name ## _obs,             \
                         BLE_SERVO_BLE_OBSERVER_PRIO, \
                         ble_servo_on_ble_evt,        \
                         &_name)


/**@brief Servo Service event handler type. */
typedef void (* ble_servo_evt_handler_t) (uint16_t pwm_value);


/**@brief Servo Service structure. This contains various status information for the service. */
typedef struct
{
    ble_servo_evt_handler_t    evt_handler;               /**< Event handler to be called for handling events in the Servo Service. */
    uint16_t                 service_handle;            /**< Handle of Servo Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t servo_value_handles;     /**< Handles related to the Servo Level characteristic. */
}ble_servo_t;


ret_code_t ble_servo_service_init(ble_servo_t * p_servo);


void ble_servo_on_ble_evt(ble_evt_t const * p_ble_evt, ble_servo_t * p_ble_servo);

#endif // BLE_SERVO_H__

/** @} */
