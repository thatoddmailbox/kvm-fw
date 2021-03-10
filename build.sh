#!/bin/bash
command -v sdcc >/dev/null 2>&1 || { echo >&2 "SDCC could not be found, is it installed and in your PATH?"; exit 1; }

CFLAGS="--std-c11 -mstm8 -I../"

cd stm8
sdcc -c $CFLAGS i2c_master.c
sdcc -c $CFLAGS i2c_slave.c
sdcc -c $CFLAGS i2cbb.c
sdcc -c $CFLAGS timer.c
sdcc -c $CFLAGS uart.c
cd ..

cd base
sdcc -c $CFLAGS fsusb74.c
sdcc -c $CFLAGS tmds361b.c
sdcc $CFLAGS main.c fsusb74.rel tmds361b.rel ../stm8/i2cbb.rel ../stm8/timer.rel ../stm8/uart.rel
cd ..

cd keypad
sdcc -c $CFLAGS is31fl3218.c
sdcc -c $CFLAGS pcal6416a.c
sdcc $CFLAGS main.c is31fl3218.rel pcal6416a.rel ../stm8/i2c_master.rel ../stm8/timer.rel ../stm8/uart.rel
cd ..