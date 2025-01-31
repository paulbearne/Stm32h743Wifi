# Stm32h743Wifi
 weactstudio h743 wifi using esp-hosted

 requires tibyusb https://github.com/hathach/tinyusb
 and esp-hosted-fg https://github.com/espressif/esp-hosted note that the esp-hosted has a few mods 
 to pin names and ports and also for the spi and comms ports used

i am using esp-s3 mini for testing the connections between the spi pins should be as short as possible

the Weact studio stm32h743 board tasks are modified from the orginal Weact SDK
the display task at present excepts a string of text and display on the third line 
the previous text is moved up one line.