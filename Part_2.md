# Part 2: Adding the PWM driver
The goal of this workshop is to control a servo ([SG90 Datahseet](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)) with a phone using BLE. The angle of the servo arm is manipulated using a PWM signal with varying duty-cycle, so in this next part of the workshop we will add the necessary PWM driver files to our project, initiate the drivers, and implement a simple function for controlling the servo.  

## The nRF52840's PWM Peripheral
The [PWM](http://infocenter.nordicsemi.com/topic/com.nordic.infocenter.nrf52840.ps/pwm.html?cp=2_0_0_5_16) peripheral in the nRF52840 includes four sepparate instances, also known as modules. Each instance controls groups of four different PWM channels. This allows you to control up to 16 individual PWM channeles. In our case we will use PWM instance 0, and channel number one shall fade an LED and channel number 1 will control the servo. 

## Adding files to our project
1. The first thing we need to do is to add the [PWM driver's](http://infocenter.nordicsemi.com/topic/com.nordic.infocenter.sdk5.v15.0.0/hardware_driver_pwm.html?cp=4_0_0_2_0_8) source code to our project. Do that by righclicking on the "Application" folder in the Project Item vindow and click "Add Existing File":

    ![Add existing file](./images/part2/add_file.png)

1. Navigate to _"..\your_sdk_15_folder\modules\nrfx\drivers\src"_ and add the file _nrfx_pwm.c_.

    ![Add PWM driver file](./images/part2/driver_path.png)

1. We also need to make sure that the path to the corresponding include file, _nrfx_pwm.h_, is included in our project settings. So enter your project options again, set the Release/Debug configuration to 'Common', select Preprocessor, and check that _"../../../../../../modules/nrfx/drivers/include"_ is included in "User Include Directories".

    ![User include directories](./images/part2/add_include_path.png)

1. Finally, include the header file in main.c:

    ````c
    #include "nrfx_pwm.h"
    ````

Now we should be ready to use the PWM driver in our project. 

## Initialize the PWM driver
Many of the drivers and libraries in Nordic's SDK are configured and initialized by filling out a configuration structure which is then passed into a driver init() function. In many cases, the configuration structure includes sub-structures and dozens of parameters. Luckily, the parameters usually defaults to 0, so you ususally get away with only configuring the parameters that matters to you. This is how we are going to configure the PWM driver as well. 

1. We start by declaring a [PWM driver instance structure](http://infocenter.nordicsemi.com/topic/com.nordic.infocenter.sdk5.v15.0.0/structnrfx__pwm__t.html?cp=4_0_0_6_9_0_12_1_1). Then we define a function called `init_pwm()` where we configure and initialize the peripheral. Inside the function we fill out a [PWM driver configuration structure](http://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk5.v15.0.0%2Fstructnrfx__pwm__config__t.html). Finally, we pass these two structures into the [PWM driver initialization function](http://infocenter.nordicsemi.com/topic/com.nordic.infocenter.sdk5.v15.0.0/group__nrfx__pwm.html#gaf06bb9053293005bc91217e5a1791261). And of course we check the return code with `APP_ERROR_CHECK(err_code)` afterwards.

    Add this code to main.c: 

    ````c
        // Declare a PWM driver instance structure
        nrfx_pwm_t m_pwm0 = NRFX_PWM_INSTANCE(0);

        // Function for initializing the PWM
        void init_pwm(void)
        {
            uint32_t err_code;

            // Fill out the configuration structure
            nrfx_pwm_config_t const config0 =
            {
                .output_pins =
                {
                    BSP_LED_0, // channel 0
                    NRFX_PWM_PIN_NOT_USED,             // channel 1
                    NRFX_PWM_PIN_NOT_USED,             // channel 2
                    NRFX_PWM_PIN_NOT_USED,             // channel 3
                },
                .irq_priority = APP_IRQ_PRIORITY_LOW,
                .base_clock   = NRF_PWM_CLK_1MHz,
                .count_mode   = NRF_PWM_MODE_UP,
                .top_value    = 1000,
                .load_mode    = NRF_PWM_LOAD_COMMON,
                .step_mode    = NRF_PWM_STEP_AUTO
            };
            
            // Pass configuration and instance structure to initialization function.
            err_code = nrfx_pwm_init(&m_pwm0, &config0, NULL);
            APP_ERROR_CHECK(err_code);
        }
    ````

1. Try to compile. If you have followed the tutorial it should fail with this error:

    ![Compile error](./images/part2/pwm_compile_error.png)

1. This is because we have not yet enabled the PWM driver in _sdk_config.h_. To enable the driver, search for ``NRFX_PWM_ENABLED`` in _sdk_config.h_ and set it to 1. 

1. We also explicitly need to enable instance 0 in _sdk_config.h_. Do this by searching for ``NRFX_PWM0_ENABLED`` and set it to 1.

## Test Servo