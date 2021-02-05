#!/bin/sh
command -v sdcc >/dev/null 2>&1 || { echo >&2 "SDCC could not be found, is it installed and in your PATH?"; exit 1; }
command -v stm8flash >/dev/null 2>&1 || { echo >&2 "stm8flash could not be found, is it installed and in your PATH?"; exit 1; }
