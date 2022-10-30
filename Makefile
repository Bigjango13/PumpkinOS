RPI_VERSION ?= 4

REDRAW = -1

CFILES = $(wildcard src/*.c)
OFILES =  $(patsubst src/%.c,build/%.o,${CFILES})
CPPFILES = $(wildcard src/*.cpp)
OPPFILES =  $(patsubst src/%.cpp,build/%.opp,${CPPFILES})

GCCFLAGS = -Wall -Wextra -O6 -ffreestanding -nostdinc -nostdlib \
	-nostartfiles -Wno-sign-compare -Iinclude \
	-DRPI_VERSION=$(RPI_VERSION) -DREDRAW=$(REDRAW)

GCCPREFIX = aarch64-none-elf
GCCPATH = /usr/local/${GCCPREFIX}/bin

all: build

build/boot: src/boot.S
	mkdir -p build
	@echo "### Making boot.o ###"
	$(GCCPATH)/${GCCPREFIX}-gcc $(GCCFLAGS) -c src/boot.S -o build/boot

build/%.o: src/%.c
	mkdir -p build
	@echo "### Making $@ ###"
	$(GCCPATH)/${GCCPREFIX}-gcc $(GCCFLAGS) -c $< -o $@

build/%.opp: src/%.cpp
	mkdir -p build
	@echo "### Making $@ ###"
	$(GCCPATH)/${GCCPREFIX}-g++ $(GCCFLAGS) -c $< -o $@

build: build/boot $(OFILES) $(OPPFILES)
	@echo "### Building PumpkinOS image ###"
	$(GCCPATH)/${GCCPREFIX}-ld -nostdlib build/boot $(OFILES) $(OPPFILES) -T src/link.ld -o build/pumpkin_kernel.elf
	$(GCCPATH)/${GCCPREFIX}-objcopy -O binary build/pumpkin_kernel.elf build/pumpkin_kernel.img
	@echo "### Done! ###"

prep:
	mkdir -p out
	wget https://github.com/raspberrypi/firmware/blob/master/boot/fixup4.dat?raw=true -O out/fixup4.dat
	wget https://github.com/raspberrypi/firmware/blob/master/boot/start4.elf?raw=true -O out/start4.elf
	cp build/pumpkin_kernel.img out/kernel8.img
	cp config.txt out/config.txt

clean:
	rm -rf build out
