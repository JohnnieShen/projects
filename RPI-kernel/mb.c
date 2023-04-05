#include "io.h"
#include "mb.h"
volatile unsigned int __attribute__((aligned(16))) mbox[36];
unsigned int mbox_call(unsigned char ch)
{
    // 28-bit address (MSB) and 4-bit value (LSB)
    unsigned int r = ((unsigned int)((long) &mbox) &~ 0xF) | (ch & 0xF);

    // Wait until we can write
    while (mmio_read(MAIL_STATUS) & MAIL_FULL);
    
    // Write the address of our buffer to the mailbox with the channel appended
    mmio_write(MAIL_WRITE, r);

    while (1) {
        // Is there a reply?
        while (mmio_read(MAIL_STATUS) & MAIL_EMPTY);

        // Is it a reply to our message?
        if (r == mmio_read(MAIL_READ)) return mbox[1]==MAIL_RESPONSE; // Is it successful?
           
    }
    return 0;
}
