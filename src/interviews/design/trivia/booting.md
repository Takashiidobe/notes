# How does an x86 Computer Boot?

When power starts, the motherboard sends a signal to the power supply. Once it receives a power good signal, it starts the CPU.

The CPU starts running in real mode, which has 1MB of address space, but only 16-bit registers (so it can only address 64KB).

It uses memory segmentation -- there are 16 segments, and an offset (up to 64KB).

It then boots into its BIOS entry point, where it tries to find a bootable device (hard disk or USB).

## Bootloading

Linux then boots into GRUB2, which transfers control to the boot sector code. It executes the grub_main function, which loads the kernel into memory, sets up the Boot loader, and then jumps to the Kernel boot sector and lets it start.

## Kernel Setup

The Kernel then sets up registers, the stack, bss, and then jumps to the main C function.

## Protected Mode

The CPU then changes to Protected Mode, which is 32-bits, which allows for 4GB of memory. This allows for larger memory segments, which are held in the Global Descriptor Table (gdt). This is held in memory. It then disables interrupts, loads the GDT, and then sets the Protection Enable bit in CRT0, and jumps to protected mode.

## Console Initialization

The console is initialized with the `console_init` function, which writes to the VGA Screen, and calls the BIOS with `0x10` which interrupts to bios.

## Heap Initialization

The heap is then initialized to grow to the stack, and corrected if it has grown past the stack.

## CPU validation

Then the Kernel checks the CPU's flags, like SSE or or 1GB pages.

## Memory detection

The kernel checks to see the memory enabled for the kernel.

## Keyboard Initialization

The kernel then starts up the keyboard with `keyboard_init`, and initializes registers, which it then calls the 0x16 interrupt to set it up.

## Querying

It then queries for Speedstep, or Advanced Power Management, or other features.

## Video Mode

The kernel then sets up video mode, and then saves the contents of the screen to the heap, with stuff like the current pointer and the data, and then checks the video cards.

## Interrupt Descriptor Table

The interrupt descriptor table is then set up, which describes interrupt handlers.

## The Global Descriptor Table

The global descriptor table is then set up.

## Setting up Protected Mode

The kernel finally jumps into protected mode.

## Protected Mode

In protected mode, the stack is set up again, and the CPU is verified for newer features, and relocated if required to a 32-bit space.

## Long Mode

Long mode is the 64-bit mode. This requires setup of new registers, a 64-bit instruction pointer, and longer addresses and operands.

## Page Tables

Page tables are then built, which allows access to 64-bits of memory.

## Kernel Decompression

The Kernel is then decompressed, and then loaded to memory. Then a jump to %rax is done to start the kernel.

## Avoiding Reserved Memory Ranges

The kernel then is loaded into a low range (`<` 512MB) and avoids areas where memory is already in use.
