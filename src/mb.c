#include <mb.h>

// MMIO
void mmio_write(long reg, unsigned int val) {
    *(volatile unsigned int *) reg = val;
}
unsigned int mmio_read(long reg) {
    return *(volatile unsigned int *) reg;
}

// The buffer must be 16-byte aligned as only the upper 28 bits of the address can be passed via the mailbox
volatile unsigned int __attribute__((aligned(16))) mbox[36];

unsigned int mbox_call(unsigned char ch) {
    // 28-bit address (MSB) and 4-bit value (LSB)
    unsigned int r = ((unsigned int)((long) &mbox) &~ 0xF) | (ch & 0xF);

    // Wait until we can write
    while (mmio_read(MAILBOX_STATUS) & MAILBOX_FULL);

    // Write the address of our buffer to the mailbox with the channel appended
    mmio_write(MAILBOX_WRITE, r);

    while (1) {
        // Is there a reply?
        while (mmio_read(MAILBOX_STATUS) & MAILBOX_EMPTY);

        // Is it a reply to our message and is it successful?
        if (r == mmio_read(MAILBOX_READ)) return mbox[1]==MAILBOX_RESPONSE;
    }
    return 0;
}
