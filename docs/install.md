The WatchDuino firmware needs to run on an
[Arduino Pro Mini board](https://www.arduino.cc/en/Main/ArduinoBoardProMini),
or any clonical board with the same specs (8Mhz, 32kb flash memory).

You'll also need to mount all the circuitry to get a functional smartwatch,
check the [building] document to put together a breadboard prototype.

Here's what you need to do to compile the code and load it into your hardware:

1. To install the firmware on a device you'll need the Arduino SDK and IDE.
You can download the latest bundle for your platform
[on the official website](https://www.arduino.cc/en/Main/Software),
for free. Unzip the package to any location of your choice. Remember this
location, because this will be the `Arduino SDK`, everytime we refer to it.
Open the `arduino` executable inside the SDK folder to run the IDE.

2. Copy all the folders inside the `libraries` folder in this repo into the
`libraries` folder of your Arduino SDK. These are dependencies the WatchDuino
code needs to compile.

3. On the Arduino IDE, click on `File->Open`. Navigate to where you cloned
the WatchDuino repository, and pick the `watch/watch.ino` file to open.
All of the WatchDuino files should now have been loaded in the IDE.

4. On the IDE now go to `Tools->Board` and pick `Arduino Pro or Pro Mini`.
Then pick `Processor:ATMega328 (3.3V, 8Mhz)`. This step is needed because the
IDE needs to know the microcontroller that we are using, in order to apply
the correct compilation options.

5. After all this, you should be able to compile the code. On the IDE, click
on the `Verify` button (the first icon in the toolbar, showing a tick). After a
minute it should be done without errors.

6. You are ready now to upload the code into your Arduino Mini. Connect
the Arduino to your PC via USB. Then go to `Tools->Port`, and you should
be able to see something in there (in my case it's '/dev/ttyUSB0', but this
will likely be different depending on your OS. It's essentially an identifier
for your USB port where your Arduino is plugged). If you see `Tools->Port`
greyed out, it's because you are not running the IDE with sufficient
permissions. If you are on Linux try running the program with a superuser
(eg. `sudo` on Ubuntu).

7. After that, click on the `Upload` button (the second icon in the toolbar,
showing a right pointing arrow). The Arduino Mini should now be loaded with
the WatchDuino firmware. If you mount all the circuitry you should be
able to see the interface on the screen, and interact with it using the buttons.
