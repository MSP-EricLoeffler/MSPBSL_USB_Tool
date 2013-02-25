MSPBSL_USB_Tool
===============

This firmware is designed to allow USB to UART communication for the purpose of programming an MSP430 BootStrapLoader.  It requires special hardware, described below.

This firmware is based on the MSP430 CDC UART Bridge, which can be found in the USB developer package: http://www.ti.com/tool/msp430usbdevpack

Hardware to run this firmware can be found here: https://www.olimex.com/Products/MSP430/BSL/MSP430-BSL/

Schematics are available here: https://www.olimex.com/Products/MSP430/BSL/MSP430-BSL/resources/MSP430-BSL_Rev_B.pdf

Note: When downloading the firmware via ZIP, the linebreaks in the text files might be incompatible with your OS.  This is particularly important if you plan to use the text file output image with a tool to write the firmware onto the Rocket.  Some TI provided tools require windows-format linebreaks, whereas the Zip web download comes in UNIX-style.  This can be worked around in two ways:

- Fetch the source code using GIT running on your host OS, having it automatically change the formatting
- Manually change the linebreaks in the downloaded TXT  file.
