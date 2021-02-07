# kvm-fw
## Setup
Download [SDCC](http://sdcc.sourceforge.net/index.php#Download) (tested with version 4.0) and [stm8flash](https://github.com/vdudouyt/stm8flash). Ensure that both commands are in your PATH and working (so the `sdcc` and `stm8flash` commands both do something)

You will also need an ST-LINK adapter supported by `stm8flash`. (either the official one or a clone will do) To test that the adapter and its connection works, you can try to read data from the STM8S003F3, like so: `stm8flash -c stlinkv2 -p stm8s003f3 -s flash -r test.bin`.

## Building
Run the `./build.sh` script to build the keypad firmware. The final output will be an Intel Hex file in `keypad/main.ihx`. The `./upload.sh` script will upload the firmware to a connected STM8S003F3.