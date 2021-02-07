#!/bin/sh
clean_sdcc() {
	rm *.asm
	rm *.cdb
	rm *.ihx
	rm *.lk
	rm *.lst
	rm *.map
	rm *.rel
	rm *.rst
	rm *.sym
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