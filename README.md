# WatchDuino2

WatchDuino2 is an open hardware project, and an attempt to build a smartwatch
at the reach of everyone: inexpensive and open. So that anyone can afford one,
or even build it from scratch. And at the same time,
so that anyone can built their custom applications for it.

This project is currently a work in progress in a very alpha state,
so expect drastic changes without warning!

See official project page for more info and updates on development:
https://www.coconauts.net/projects/watchduino2/


## Compile without the Arduino IDE

Watchduino is making use of [https://github.com/marbru/Arduino-Makefile], so you can compile and upload it from the command line.

Copy `Makefile.sample` into `Makefile`, and edit the paths to your Arduino and Arduino Makefile installation dirs. 

Then you can do:

./make.sh  # To compile
sudo ./make.sh upload  # To upload to your Arduino


## Tutorials

- [How to make](docs/how_to_make.md), how to build your own WatchDuino.
