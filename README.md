# key-typer
Arduino program and hardware for rapidly typing characters using a [Pro Micro - 5V/16MHz](https://www.sparkfun.com/products/12640) as a [USB Human Interface Device](https://en.wikipedia.org/wiki/USB_human_interface_device_class) (HID) keyboard. Based on [Turn your Pro Micro into a USB Keyboard/Mouse](https://www.sparkfun.com/tutorials/337). The device has been tested and works on Linux, Mac and Windows.

I built this to aid in debugging a textarea in a web page which was intermittently dropping characters in IE11 due to a Javascript issue.

When manually typing at the keyboard, it's hard to tell if intermittent character loss is due to a bug, or because the keys were not pressed properly. In addition manual typing speed is limited, so its not possible to do 'stress' testing. This device solves both these problems by emulating a USB keyboard and generating characters programmatically.

There are three adjustable parameters available via the buttons:

- Lines - the number of lines of text to output (-1, 1, 2, 4). The default is -1 (unlimited).
- Characters - the number of characters in each line (5, 13, 26, 52, 104). The default is 26 (a-z).
- Rate - the rate of character generation in characters/minute (100, 200, 400, 1000, 6000). The default is 200 (average typist). 100 is a slow typist, 400 is a professional typist and anything higher is not humanly possible!

These parameters may be adjusted while characters are being generated. Character generation is started and stopped with the toggle switch. A video of the device in action is [here](https://s3-us-west-2.amazonaws.com/public.7777/key-typer-in-action.mp4).

![Picture](./docs/key-typer.jpg)

This is the schematic for the project. If the schematic appears to be missing details, download it and view it locally,
or zoom the web page.

![Circuit Schematic](./docs/key-typer-schematic.svg)

The code in repository has the configuration files to allow it to be imported into the PlatformIO development environment, alternatively it may be edited in the Arduino IDE.
