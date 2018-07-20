# seven-segment-single-pin
## Module to control 7 segment display using single pin (through UART interface)

I bought few seven segment display to make a temperature monitor. Using those would take lot of pins, so I planned to have a driver chip. 
However, I couldn't find one offline (shop) and shipping charges (online) would be expensive for single chip.
Thus, I planned to make one.

## Recipe:
1. Burn MicroChip Attiny 2313 /A with /sevenSeg/Debug/sevenSeg.hex.
2. Solder Attiny2313 and seven segment display as given in schematics.
3. Check commandSet.md for commands and how to use them.

Also, check given example (counter) with atmega 328 and arduino.

For any bugs, feel free to raise an issue.
Below is schematics, you can add upto 4 seven segment display (what I tested with):

![title](https://raw.githubusercontent.com/jeffysonar/seven-segment-single-pin/master/schematics.png)
