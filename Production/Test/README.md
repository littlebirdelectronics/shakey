# Production Test

## Prerequisite

1. `avrdude.exe`
2. `avrdude.conf`
3. `<productname>Uploader.exe` (in house developed production software)

## Bootloader

`<productname>.hex`

Example: `Caterina-shakey.hex`

This file should be the first file to be flashed onto the product. Normally, the **bootloader** and **Factory Testing Code** are combined into one HEX file to increase production speed and also reduce USB issues.

*Source code available at github repo.*

## Factory Testing Code

Usually named `<productname>FactoryTest.hex`, example: `ShakeyFactoryTest.hex`.

This is the 2nd file to be flashed onto the product. The code does self test, and send the results to serial port.

*Source code available at github repo.*

Note: Some product like EagLED that requires human visual inspection of the output LED status, does not require Factory Testing Code.

## Factory Firmware

`Factory.hex`

This is the firmware loaded to the product after product passed factory testing. This firmware gives the user out of the box experience, normally a demo to show off the product.

*Source code available at github repo.*
