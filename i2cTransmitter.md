# A note about specific transmitter

Pins on a socket in turkish TSA5511 PLL based transmitter which can be found on aliexpress. I won't give you a link to this offer for obvious reasons, but you can find it easily on aliexpress.

    +-------   -------+
    |                 |
    |  1  2  3  4  5  |
    |                 |
    |  6  7  8  9  10 |
    |                 |
    +-----------------+

1,6 - GND  
2,7 - VCC  
3,8 - NC ?

socket pins vs TSA5511 pins:

4 - pin 4 - SCL  
5 - pin 5 - SDA  
9 - pin 9 - P4  
10 - pin 8 - P5

If you remove default 5V voltage regulator, you can still power up lower voltage part of this transmitter by using 5V and GND pins of GPIO.

-----

# Notice! This is my "sketchbook", whatever info you find here could be invalid

Good resources:
* [An extensive topic about controlling TSA5511 over I2C](https://community.particle.io/t/solved-interface-with-i2c-bus-controlled-synthesizer-tsa5511/28758/9)
* [Charge-pump phase-locked loop](https://en.wikipedia.org/wiki/Charge-pump_phase-locked_loop)
* [TSA5511 datasheet](https://www.alldatasheet.com/view.jsp?Searchword=Tsa5511&gclid=Cj0KCQjwuuKXBhCRARIsAC-gM0hPR67Z6SkxgDTyoDk8LCdsMDjsFwTYhfbmwI7LMT_KTnSdbhyZxxYaApUlEALw_wcB)

We should send five bytes when we want to send controls  
1. Address
2. Programmable divider
3. Programmable divider
4. Charge-pump and test bits
5. Output ports control bits

All of them one after another. Theoretically we can cut them to just two bytes, but for this documentation we will keep five bytes.

This is how first byte should look like:  

    1,1,0,0,0,MA1,MA0,0

Allowed combinations:

    1100 0000	C0
    1100 0010	C2
    1100 0100	C4
    1100 0110	C6
    
Second and third bytes look like this:

      0, N14, N13, N12, N11, N10,  N9,  N8
     N7,  N6,  N5,  N4,  N3,  N2,  N1,  N0

TSA5511 usually uses an external crystal oscillator at 3.2 or 4MHz. It's frequency is divided by 512 and therefore you get either 50kHz or 62.5kHz step. Please take a note which crystal oscillator is used in your circuit and if it is 3.2MHz you are ready to use my little control program.

If we want to generate signal at 92MHz we have to divide this frequency by 0.05 (or multiply by 20) and we will get a 1840 value. This value we have to split into two bytes.

    long frequency = 1840;
    char data[5];

    ...
    data[1] = (frequency & 0xFF00) >> 8;
    data[2] = frequency & 0x00FF;
    ...

Byte four (TODO: what is it exactly used for?)

    1, CP, T1, T0,  1,  1,  1, OS

* CP - "charge-pump current", 0 means 50 μA, 1 means 220 μA
* T0 - "3-state charge-pump"
* T1 - TODO
* OS - TODO

TODO - finish this document