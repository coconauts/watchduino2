# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

# Reference for variables: https://github.com/sudar/Arduino-Makefile/blob/master/arduino-mk-vars.md#arduino-ide-variables

# Installation dirs
ARDUINO_DIR= /home/marbu/bins/arduino-1.6.5-r5_watchduino2
ARDUINO_PREFERENCES_PATH = /home/marbu/bins/arduino-1.6.5-r5_watchduino2/lib/preferences.txt
ARDMK_DIR = /home/marbu/bins/Arduino-Makefile

# Compilation opts
BOARD_TAG    = pro
BOARD_SUB = 8MHzatmega328
MONITOR_PORT = /dev/ttyUSB0
ARCHITECTURE = avr
ARDUINO_LIBS = Time U8glib SPI SoftwareSerial Wire jeelib_master
OBJDIR = ../build/build-$(BOARD_TAG)

include $(ARDMK_DIR)/Arduino.mk

