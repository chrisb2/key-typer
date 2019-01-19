# key-typer
Arduino program for rapidly typing characters using a [Pro Micro - 5V/16MHz](https://www.sparkfun.com/products/12640) as a [USB Human Interface Device](https://en.wikipedia.org/wiki/USB_human_interface_device_class) (HID) keyboard. Based on [Turn your Pro Micro into a USB Keyboard/Mouse](https://www.sparkfun.com/tutorials/337).

I built this to aid in debugging a textarea in a web page which was intermittently dropping characters in IE11 due to a Javascript issue.

There are three adjustable parameters available via the buttons:

- Lines - the number of lines of text to output (-1, 1, 4). The default is -1 (unlimited).
- Characters - the number of characters in each line. The default is 52 (a-z twice).
- Rate - the rate of character generation in characters/minute (100, 200, 400, 6000). The default is 200 (average typist).

Character generation is started and stopped with the toggle switch.

![Picture](./docs/key-typer.jpg)

This is the schematic for the project. If the schematic appears to be missing details, download it and view it locally,
or zoom the web page.

![Circuit Schematic](./docs/key-typer-schematic.svg)
