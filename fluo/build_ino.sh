#!/bin/bash
cat arduino_base.c <(echo) lib.c <(echo) scenes.c <(echo) program.c > arduino_program/arduino_program.ino
cp fluo_types.h arduino_program/