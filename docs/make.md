## Bill of materials

You'll need the following in order to build a WatchDuino 2:

- 1 × Arduino mini pro 2 8Mhz 3.3v
- 1 × LIPO battery 240mah
- 1 × 0.96” I2C 128X64 OLED
- 4 × 3 x 6 x 4.3mm Push Button 2 Pin
- 1 × 0.06A Micro Vibrator Motor
- 1 × Micro USB LIPO charger External charger
- 1 × Bluetooth 4.0 BLE module HM-10

## Mounting a prototype on a breadboard

Before you go and build the real thing, it's advisable that you build a
prototype version on a breadboard. This way you can test that the code
is correctly loaded into the Arduino board, and that you understood
all the connections in the schematic right.

The schematic can be found in the `schema` folder, you should see an `.fzz`
file in there. You can use the Fritzing software to open this file, and
it'll show you a detailed view of the components connected together, which
you can zoom and hightlight the connections in.

Before you start, it is advisable to load the WatchDuino firmware into the
Arduino Mini. You can also do this at the end, but if you do it now you'll
be able to try the components as you go along.

To load the WatchDuino firmware, connect your Arduino Mini to your PC via USB,
and then follow the instructions in the [install document](install).

After you've successfully flashed the Arduino with the software, leave it
connected to the USB, and place it on the breadboard. Then:

- Place the buzzer. You should hear a "beep" if you reset the Arduino.
- Place the screen. You should see the WatchDuino interface if you reset
the Arduino.
- Place the buttons. You should be able to use them to navigate through
the menus.
- Place the bluetooth module. You shoud see an intermitent led flashing.
This is because it hasn't been paired yet. If you pair to the companion phone
app it should become fixed.
