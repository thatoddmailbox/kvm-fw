# kvm-fw
The firmware for the [open-source HDMI KVM switch I built](https://github.com/thatoddmailbox/kvm#kvm). Note that this repository has the code for both the [base](https://github.com/thatoddmailbox/kvm-base) and the [keypad](https://github.com/thatoddmailbox/kvm-keypad).

There's also some generic STM8 code in the `stm8/` folder, which is used to set up and access various peripherals. Finally, there are some shared definitions in the `shared/` folder, which are used for the I2C communication between the base and keypad.

## Setup
Download [SDCC](http://sdcc.sourceforge.net/index.php#Download) (tested with version 4.0) and [stm8flash](https://github.com/vdudouyt/stm8flash). Ensure that both commands are in your PATH and working, meaning the `sdcc` and `stm8flash` commands both do something.

You may want to use [my fork of stm8flash](https://github.com/thatoddmailbox/stm8flash), which allows selecting an ST-LINK adapter based on its USB port number. If you don't use it, then you must edit the `upload-base.sh` and `upload-keypad.sh` scripts to remove the port number flags (`-S port:1` and `-S port:3`). See the "fork of stm8flash" section, at the end, for more.

You will also need an ST-LINK adapter supported by `stm8flash`&mdash;either an official one or a clone. To test that the adapter and its connection works, you can try to read data from the STM8S003F3, like so: `stm8flash -c stlinkv2 -p stm8s003f3 -s flash -r test.bin`. If you are not using an `stlinkv2` adapter, then you will probably need to edit the upload scripts to change the adapter type passed to `stm8flash`.

You should connect the ground, nRST, and SWIM pins from the board to your ST-LINK. You can also connect the 3.3V power pin if you want to power the board from your ST-LINK. If you do that, then make sure the board is not otherwise connected to power. Do _not_ connect multiple sources of power at the same time. For the base, this means not plugging in any HDMI cables, as they can backfeed +5V power! The base does have a +5V pin that you can connect to the ST-LINK's +5V rail instead.

If you want to read debug messages, then you should also connect a USB-to-UART adapter to the TX, RX, and GND pins, with the UART set to 8N1 at 57600 baud.

## Building
Run the `./build.sh` script to build the firmware for both the base and keypad. The final output will be two Intel HEX files, `base/main.ihx` and `keypad/main.ihx`. The `./upload-base.sh` and `./upload-keypad.sh` scripts will upload the respective firmware to a connected STM8S003F3.

## Fork of stm8flash
For this project, I [forked stm8flash](https://github.com/thatoddmailbox/stm8flash) to allow selecting an ST-LINK adapter based on its USB port number.

This was done as a slight hack on top of the existing serial number matching code. For example, to select the adapter on port 1, set the serial number `port:1`. You can use a tool like [lsusbtree](https://github.com/thatoddmailbox/lsusbtree#readme) to see the port numbers.

This was done because some clone ST-LINK adapters do not have a reliable serial number field, and so the port number is used as an alternative form of identifier. If you're using the official ST-LINK adapter, you can just use the serial number.

The instructions to set up the fork are the same as the normal program: `./configure`, then `make`, then `sudo make install`.