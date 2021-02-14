#!/bin/bash
command -v sdcc >/dev/null 2>&1 || { echo >&2 "SDCC could not be found, is it installed and in your PATH?"; exit 1; }

CFLAGS="--std-c11 -mstm8 -I../"

cd stm8
sdcc -c $CFLAGS i2c.c
sdcc -c $CFLAGS i2cbb.c
sdcc -c $CFLAGS timer.c
sdcc -c $CFLAGS uart.c
cd ..

cd base
sdcc $CFLAGS main.c ../stm8/i2cbb.rel ../stm8/timer.rel ../stm8/uart.rel
cd ..

cd keypad
sdcc -c $CFLAGS is31fl3218.c
sdcc -c $CFLAGS pcal6416a.c
sdcc $CFLAGS main.c is31fl3218.rel pcal6416a.rel ../stm8/i2c.rel ../stm8/uart.rel
cd ..