cc = arm-none-eabi-gcc
ofiles = $(wildcard *.o)
cfiles = $(wildcard *.c)
CPU = cortex-a7
GCCFLAG = -Wall -O2 -ffreestanding -fpic
all: kernel7.img clean

run: kernel7.img clean
	qemu-system-arm -m 1G -M raspi2b -serial stdio -kernel kernel7.img

kernel7.img: linker.ld boot.o io.o mb.o kernel.o io.h
	$(cc) $(ofiles) -ffreestanding -O2 -nostdlib -T linker.ld -o kernel7.img boot.o io.o mb.o kernel.o

io.o: io.c io.h
	$(cc) $(GCCFLAG) -std=gnu99 -mcpu=$(CPU) -c io.c -o io.o -Wextra

boot.o: boot.S
	$(cc) $(GCCFLAG) -mcpu=$(CPU) -c boot.S -o boot.o

mb.o: mb.c io.h
	$(cc) $(GCCFLAG) -std=gnu99 -mcpu=$(CPU) -c mb.c -o mb.o -Wextra

fb.o: fb.c io.h fb.h
	$(cc) $(GCCFLAG) -std=gnu99 -mcpu=$(CPU) -c fb.c -o fb.o -Wextra

kernel.o: kernel.c io.h
	$(cc) $(GCCFLAG) -std=gnu99 -mcpu=$(CPU) -c kernel.c -o kernel.o -Wextra

clean:
	rm *.o
