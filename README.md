# kvm-fw
The firmware for the KVM switch I built. Note that this repository has the code for both the [base](https://github.com/thatoddmailbox/kvm-base) and the [keypad](https://github.com/thatoddmailbox/kvm-keypad).

## Setup
Download [SDCC](http://sdcc.sourceforge.net/index.php#Download) (tested with version 4.0) and [stm8flash](https://github.com/vdudouyt/stm8flash). Ensure that both commands are in your PATH and working (so the `sdcc` and `stm8flash` commands both do something)

You will also need an ST-LINK adapter supported by `stm8flash`. (either the official one or a clone will do) To test that the adapter and its connection works, you can try to read data from the STM8S003F3, like so: `stm8flash -c stlinkv2 -p stm8s003f3 -s flash -r test.bin`.

You should connect the ground, nRST, and SWIM pins from the board to your ST-LINK. You can also connect the 3.3V power pin if you want to power the board from your ST-LINK. If you do that, then make sure the board is not otherwise connected to power. Do _not_ connect multiple sources of power at the same time.

## Building
Run the `./build.sh` script to build the base and keypad firmwares. The final outputs will be two Intel Hex files, `base/main.ihx` and `keypad/main.ihx`. The `./upload-base.sh` and `./upload-keypad.sh` scripts will upload the respective firmware to a connected STM8S003F3.