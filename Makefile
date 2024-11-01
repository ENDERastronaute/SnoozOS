
KERNEL_DIR := kernel
DRIVERS_DIR := drivers
STDLIBDIR := stdlib

OBJ_DIR := objects

SOURCES = $(wildcard $(KERNEL_DIR)/*.c) $(wildcard $(KERNEL_DIR)/**/*.c)  $(wildcard $(DRIVERS_DIR)/**/*.c) $(wildcard $(STDLIBDIR)/*.c)

OBJ = $(SOURCES:.c=.o)

# Cible par défaut
all: $(OBJ) SnoozOS.iso

# Cible pour exécuter
run: all
		qemu-system-i386 -D out/logs.txt -cdrom SnoozOS.iso -boot d

# Cible pour créer l'image ISO
SnoozOS.iso: out/SnoozOS.img
		genisoimage -quiet -V SnoozOS -input-charset iso8859-1 -o $@ -b SnoozOS.img out/

# Cibles pour la création des fichiers image
out/SnoozOS.img: out/SnoozOS.bin out/SnoozOS.img.placeholder
		dd if=$< of=$@ conv=notrunc

out/SnoozOS.img.placeholder:
		dd if=/dev/zero of=out/SnoozOS.img bs=1024 count=1440

out/SnoozOS.bin: out/bootloader.bin out/kernel.bin
		cat $^ > $@

# Cibles pour les fichiers binaires
out/bootloader.bin: boot/bootloader.asm
		yasm $< -f bin -o $@

# Utiliser les fichiers objets au lieu des fichiers sources
out/kernel.bin: ${OBJ_DIR}/entry.o $(OBJ) ${OBJ_DIR}/idtasm.o
		/usr/local/cross/bin/i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

${OBJ_DIR}/idtasm.o : kernel/idt/idt.asm
		yasm $< -f elf -o $@

${OBJ_DIR}/entry.o : kernel/entry/entry.asm
		yasm $< -f elf -o $@

%.o : %.c
		/usr/local/cross/bin/i386-elf-gcc -ffreestanding -fpermissive -c $< -o $@

# Cible de nettoyage
clean:
		rm -rf out/* $(OBJ_DIR)/* $(OBJ) SnoozOS.iso
