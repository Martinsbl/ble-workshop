#include "sdk_common.h"
#include <string.h>
#include "ble_srv_common.h"
#include "ble_conn_state.h"
#include "nrf_log.h"
#include "ble_servo.h"

void ble_servo_on_ble_evt(ble_evt_t const * p_ble_evt, ble_servo_t * p_ble_servo)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTS_EVT_WRITE:
            break;

        default:
            // No implementation needed.
            break;
    }
}


static ret_code_t servo_char_add(ble_servo_t * p_ble_servo)
{
    ret_code_t          err_code;
    
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    return NRF_SUCCESS;
}


ret_code_t ble_servo_init(ble_servo_t * p_ble_servo)
{
    ret_code_t err_code;
    ble_uuid_t ble_uuid;

    return NRF_SUCCESS;
}


