// The linker *must* put .text.boot at the start of the kernal image
.section ".text.boot"

.global _start
_start:
    mrs  x0, mpidr_el1
    and  x0, x0, #0xFF
    cbz  x0, master
    b    null_loop
    // If core number != 0, do this loop

null_loop:
    wfe
    b    null_loop
    // else continue

master:
    // Set stack to start below our code
    ldr  x1, =_start
    mov  sp, x1
    // Clean the BSS section
    ldr  x1, =__bss_start
    ldr  w2, =__bss_size

3:
    // Quit loop if zero
    cbz  w2, 4f
    str  xzr, [x1], #8
    sub  w2, w2, #1
    cbnz w2, 3b
4:
    // Call main
    bl   main
    // Put main to sleep like the other cores
    b    null_loop
