## The nRF52840 DK suddenly isn't recognized by the computer.
1. Try a different USB cable. Faulty USB cables are surprisingly often a problem.
1. It appears that the 5 V rail on the nRF52840 DK struggles to handle the current drawn, or the noise produced, by the servo motor. This seems to cause the Segger MCU to malfunction. 
    - Try to disconnect the servo if you have it connected. 
    - Try to connect the servo to VDD instead of 5V. This will feed the servo with ~3 V instead of 5 V. It will still work, but move slower.
    
    In my experience the problem seems worse when I use USB ports on my laptop or cheap USB hubs. High-end USB hubs with a dedicated power supply seems to work fine. 