# Task 1 Getting familiar with Segger Embedded Studio

## Open and build a project
1. Make sure that you have downloaded and extracted SDK 15 to your harddrive. <span style="color:red">Make sure that the path to the SDK folder isn't too long</span>, or your projects might not compile. For example, this

    _"C:\SDK_15\"_

    is better than this:

    _"C:\subfolder1\subfolder2\subfolder3\subfolder4\subfolder5\subfolder6\SDK_15\"_

    
1. Navigate to the folder _"..\your_sdk_15_folder\examples\ble_peripheral\"_ and make a copy of the folder _"ble_app_template"_. Call the new folder _"workshop"_. This folder contains the [BLE Template Application](http://infocenter.nordicsemi.com/topic/com.nordic.infocenter.sdk5.v15.0.0/ble_sdk_app_template.html?cp=4_0_0_4_1_2_23)  which we will use to get started. 

1. Open up the SES project file. You will find it in this path: _"..\your_sdk_15_folder\examples\ble_peripheral\workshop\pca10056\s140\ses\ble_app_template_pca10056_s140.emProject"_
    * pca10056 signifies that the example uses PCA10056 the development kit, also known as nRF52840 DK. 
    * S140 signifies that the example uses Softdevice S140

1. Click 'Build->Build "_name of project_"' (or click F7 on windows).
![Build project](/images/build.png)

1. When the build finishes, notice how SES shows you how much Flash and RAM is being used by your application (the output window says we are using 192 KB of flash, but note that this includes the S140 Softdevice which is 152 kB alone).
![Initial build](/images/initial_build.png)

## Test the example code
1. Now let us test the example code. Click 'Target->Download "_name of project_"'. This will program both the Softdevice and the application code to your nRF52840 DK. 
![Program target](/images/download_application.png)

1. You should now see that LED1 on the nRF52840 DK is blinking periodically. This indicates that the application is running and the device is advertising. 

1. Open up [nRF Connect for Mobile](https://www.nordicsemi.com/eng/Products/Nordic-mobile-Apps/nRF-Connect-for-Mobile) and start scanning. Your device should show up in the device list:
![Device List](/images/device_list.jpg)


1. Now try to set build configuration to 'Debug'. This will provide more useful information to be printed out to serial terminals, and makes it easier to step through code with debugger. 
![Debug Build Configuration](/images/debug_build_config.png)

# Experiment with logger module
4. Initialize [Logger module] (INSERT LINK)
5. Configure logger to use RTT. (WHat happens with FLSH requirements)
1. Configure logger severity level (WHat happens with FLSH requirements)
1. enable debugger 

        static void log_init(void)
        {
            ret_code_t err_code = NRF_LOG_INIT(NULL);
            APP_ERROR_CHECK(err_code);
            NRF_LOG_DEFAULT_BACKENDS_INIT();
        }

    asdf

1. Print debug message
1. Start debugger and look for debug message in SES's Debug Terminal. 

# Experiment with error handler
1. Try out APP_ERROR_CHECK(1)