#!/bin/sh
command -v stm8flash >/dev/null 2>&1 || { echo >&2 "stm8flash could not be found, is it installed and in your PATH?"; exit 1; }

cd base
stm8flash -c stlinkv2 -p stm8s003f3 -s flash -S port:3 -w main.ihx