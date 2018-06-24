#include "sdk_common.h"
#include <string.h>
#include "ble_srv_common.h"
#include "ble_conn_state.h"
#include "nrf_log.h"
#include "app_error.h"
#include "ble_servo.h"


void on_write_event(ble_evt_t const * p_ble_evt, ble_servo_t * p_ble_servo)
{
    NRF_LOG_INFO("Received data!");
    
    // Get the Write event data structure
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
    
    // Get length of data and pointer to the actual data
    uint16_t data_length = p_evt_write->len;
    uint8_t const * data = p_evt_write->data;
    
    // Check whether the data written was a servo value. 
    if(p_evt_write->handle == p_ble_servo->servo_value_handles.value_handle)
    {
	uint16_t new_servo_value = 0;
	
	// Convert data to an uint16_t. 
	if(data_length == 1)
	{
	    new_servo_value = data[0];	
	}
	else if(data_length == 2)
	{
	    new_servo_value= (data[0] << 8) | data[1];
	}
	else
	{
	    // Should never happen.
	    new_servo_value = 0; 
	}

	NRF_LOG_INFO("Got new servo values:");
	NRF_LOG_INFO("Value: 0x%04X (%d)", new_servo_value, new_servo_value);
	NRF_LOG_INFO("Data lenght: %d", data_length);
	
	// Call the Servo Service event handler. This should call set_servo_value() in main.c
	p_ble_servo->evt_handler(new_servo_value);
    }
}

/** Function used to propagate BLE events from main.c into ble_servo.c
 */
void ble_servo_on_ble_evt(ble_evt_t const * p_ble_evt, ble_servo_t * p_ble_servo)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTS_EVT_WRITE:
	    on_write_event(p_ble_evt, p_ble_servo);
            break;

        default:
            // No implementation needed.
            break;
    }
}


/** Function for initializing our Servo Characteristic. 
 */
static void servo_char_add(ble_servo_t * p_ble_servo)
{
    ret_code_t          err_code;
    
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          characteristic_uuid;
    ble_gatts_attr_md_t attr_md;
    
    //TODO Initialize the characteristic
    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.write         = 1;

    characteristic_uuid.type = p_ble_servo->uuid_index;
    characteristic_uuid.uuid = SERVO_CHARACTERISTIC_UUID;

    memset(&attr_md, 0, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.read_perm); // Set security mode to require no protection, open link
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm); // Set security mode to require no protection, open link

    attr_md.vloc    = BLE_GATTS_VLOC_STACK; // We chose to store the characteristic value in Softdevice (stack) controlled part of memory.

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &characteristic_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(uint16_t);
    attr_char_value.max_len   = sizeof(uint16_t);

    err_code = sd_ble_gatts_characteristic_add(p_ble_servo->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_ble_servo->servo_value_handles);
    APP_ERROR_CHECK(err_code); 
}


/** Function for initializing our Servo service. 
 */
ret_code_t ble_servo_service_init(ble_servo_t * p_ble_servo)
{
    ret_code_t err_code;
    ble_uuid_t service_uuid;
    ble_uuid128_t servo_base_uuid = SERVO_BASE_UUID;
    

    // Adding proprietary Service to the SoftDevice
    err_code = sd_ble_uuid_vs_add(&servo_base_uuid, &p_ble_servo->uuid_index); // Add SERVO_BASE_UUID to table of UUIDs and get the UUID's index
    APP_ERROR_CHECK(err_code); 
    
    service_uuid.type = p_ble_servo->uuid_index;
    service_uuid.uuid = SERVO_SERVICE_UUID; 
    
    // Add the service.
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &p_ble_servo->service_handle);
	APP_ERROR_CHECK(err_code); 				
	
	//TODO Add characteristic by calling servo_char_add()
    servo_char_add(p_ble_servo);

    return NRF_SUCCESS;
}


