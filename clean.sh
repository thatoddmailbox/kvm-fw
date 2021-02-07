#!/bin/sh
clean_sdcc() {
	rm *.asm 2> /dev/null
	rm *.cdb 2> /dev/null
	rm *.ihx 2> /dev/null
	rm *.lk 2> /dev/null
	rm *.lst 2> /dev/null
	rm *.map 2> /dev/null
	rm *.rel 2> /dev/null
	rm *.rst 2> /dev/null
	rm *.sym 2> /dev/null
}

cd stm8
clean_sdcc
cd ..

cd base
clean_sdcc
cd ..

cd keypad
clean_sdcc
cd ..