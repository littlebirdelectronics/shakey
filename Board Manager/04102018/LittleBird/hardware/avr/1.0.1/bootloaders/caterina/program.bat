@ECHO OFF
IF "%1"=="shakey" avrdude -p m32u4 -P usb -c usbtiny -U flash:w:Caterina.hex -U efuse:w:0xcb:m -U hfuse:w:0xd8:m -U lfuse:w:0xff:m
IF "%1"==""       avrdude -p m32u4 -P usb -c usbtiny -U flash:w:Caterina.hex -U efuse:w:0xcb:m -U hfuse:w:0xd8:m -U lfuse:w:0xff:m