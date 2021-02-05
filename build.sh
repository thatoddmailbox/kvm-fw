#!/bin/sh
command -v sdcc >/dev/null 2>&1 || { echo >&2 "SDCC could not be found, is it installed and in your PATH?"; exit 1; }

CFLAGS="--std-c11 -mstm8 -I../"

cd stm8
sdcc -c $CFLAGS uart.c
cd ..

cd keypad
sdcc $CFLAGS main.c ../stm8/uart.rel