<p align="center">
  <img src="https://raw.githubusercontent.com/Bigjango13/PumpkinOS/master/images/logo.png" />
</p>

# PumpkinOS

A blazingly fast, hyper efficient, and seriously secure ARM64 OS for pumpkins and jack-o-lanterns. Built with security in mind, it is on the cutting edge of pumpkin technology.

No configuring or reading user manuals, just flash, boot, and go.

It may work on squash, calabaza, kabocha, and giraumon with small modifications, but they are not officially supported.

**WARNING**: Making pumpkin pie with PumkinOS is dangerous, however PumpkinOS works well with Raspberry Pi 4.

## What this is

- Blazingly fast, PumpkinOS is fast even on the slowest pumpkins.
- Configure less, saving you valuable time.
- Bloat free, you will never find bloat in PumpkinOS file system.
- Simple, doesn't ever over complicate things for the user.
- Secure, PumpkinOS is one of the most secure OSes.
- Free, PumpkinOS will never charge you a dime.
- Open source, all the code is stored on the github repo.
- No learning curve, PumpkinOS can be understood by anyone without any practice.

## What this isn't

- A PalmOS port by pmig96, that can be found [here](https://pmig96.wordpress.com/2021/09/08/pumpkin-os/).
- Pumpkin O's cereal, those can be found [here](https://www.amazon.com/gp/aw/d/B01LX8U50P) or maybe not, as they are currently out of stock.
- Pumpkin-OS by KingUndeadCodes, that can be found [here](https://github.com/KingUndeadCodes/Pumpkin-OS).
- Useful.


## Features

- Two entirely different colors, for smooth and fast visuals.
- Only one out of four cores used for maximum efficiency.
- No file system, great for stopping bloat.
- No keyboard/joystick/mouse support, this is a critical security feature that many OSes don't provide.
- No networking, to prevent most types of cyber attacks.
- No data collection, PumpkinOS will never collect your data.


## Security


PumpkinOS is one of, if not the safest OS, it is nearly impossible for hackers to get into a pumpkin running PumpkinOS, and even if they do they will receive no useful data.

## Installing

You can grab the latest version from the Releases tab on github

## Compiling

To compile all you need to do is run `make && make prep` which will compile it and then download the firmware, you will need a GCC compiler for aarch64-none-elf, and you may need to change the `GCCPREFIX` and `GCCPATH` variables.

You may also want to change the `REDRAW` variable to a time (in seconds) that it will refresh after, else it will only draw once.

### Changing the colors

The colors can be found in [`include/common.h`](include/common.h) and are `PUMPKIN_SKIN` and `PUMPKIN_INTERIOR` which default to `0xCC6315` and `0xE99A10` respectively.

## FAQ

Q: Why did you make this? <br>
A: I wanted to learn more about how OSes worked, and thought a Raspberry Pi powered pumpkin would be a cool project.

Q: What resources did you use? <br>
A: Mostly [rpi4os.com](https://www.rpi4os.com) and [rockytriton/LLD](https://github.com/rockytriton/LLD), but [this](https://wiki.osdev.org/GCC_Cross-Compiler) [osdev](https://wiki.osdev.org/Main_Page) page was very helpful as well.

Q: What is the PumpkinOS logo based on?<br>
A: The Twitter pumpkin emoji.<br>
![pumpkin twemoji](https://raw.githubusercontent.com/twitter/twemoji/master/assets/72x72/1f383.png)

Q: What is the PumpkinOS image based on? <br>
A: This one: <br>![pumpkin with triangle eyes and nose and a half circle mouth and teeth](https://i.pinimg.com/originals/c0/9c/6a/c09c6a54c35bd9d29820a64a33110b9d.jpg)
