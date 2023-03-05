# tsa5511ctl
Simple CLI program to control TSA5511 chip from Raspberry Pi.

## WORK IN PROGRESS
This piece of code is still a concept. While I can already set the TSA5511 frequency, there is still too much work to do, to make this usable.

I plan to make this a system deamon which after it's start looks after TSA5511 on i2c bus and auto starts it with a correct frequency stored in a configuration file. Features will include udp sockets to send and receive signals between other apps made by users (as an example, a web control panel written in python or php).

## Important notice
As you can see by looking at the code. This program accepts frequencies within 65-108MHz which suggests it is aimed for FM broadcasting, however you can modify this code as you wish to use this chip for 4m or 2m ham radio bands, or for receiving circuits only.

In my case I'm testing this program on a tiny low power transmitter obtained on aliexpress for tests and experiments. All done only when it is connected to a dummy load to be compliant with regulations.

If you wish to use it for FM radio broadcasting, keep in mind pirate radio broadcasting is **illegal**, and I strongly encourage you to obtain a license (for low power broadcasting), or use this program only for unlicensed bands with output power and bandwidth allowed by local regulations.

#### Question: But I still want to broadcast my own FM station in my neighbourhood. What should I do?
Well, there are a few options.

- Dummy load - Dummy load is usually a resistor or group of resistors enclosed within a radiator to dissipate heat. 
Dummy load is not an antenna, but to the transmitter acts like one. RF signal leakage may be strong enough to cover your room with a signal.
I strongly encourage you to buy one if you are working on any transmitter.
- Legal unlicensed broadcasting:
  - In some countries it is legal to use low power FM transmitters, usually to feed your car radio with music from your phone or mp3 player.
  Please check local regulations for maximum allowed radiated power and if DIY setups are tolerable.
  In Europe it is only 50nW, which is horribly low (legally sold FM transmitters in electronics and car parts stores usually radiate at <=100mW - nobody even cares about that, not that you shouldn't care).
  - If you are part of a larger unit, a university for example, you may be interested in injecting (after obtaining an appropriate permit) a signal into local cable network, which provides some signal leakage enough to cover campus buildings (signal leakage is common phenomena and it is tolerable until it is too strong and causes interference).
  - [In some countries](https://recnet.com/unlicensed) it is allowed to run unlicensed FM transmitters with radiated power not exceeding specified power (up to 50mW).
- Legal licensed broadcasting:
  - Numerous countries allow LPFM (Low Power FM) broadcasting with radiated power usually between 1-10W, sometimes even up to 100W.
  Make sure your transmitter is tested or certified to operate within FM band.
  Such licenses are usually short term or assigned to a local community.
  - Temporary or testing licenses are another option if LPFM is not defined by a law in your country.
  Such temporary licenses can be used during various events with radiated power up to 10W.
  This also creates an opportunity to promote your internet radio station. Such events could be sports events, holidays, temporary car cinemas, etc.
- Ham radio - If previous options are not interesting and you have a ham radio license, you may be interested in building a ham radio beacon or some automated station.

If you still have balls to run pirate broadcast and risk being caught by a local authorities. **Please!** Please, make sure your transmitter does not generate **ANY** interferences at all. Any interferences to any other FM broadcasts, any interferences inside airband (108-137MHz), other frequency bands and is not interfering with devices in surrounding area.
