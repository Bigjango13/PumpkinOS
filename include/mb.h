#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define PERIPHERAL_BASE 0xFE000000

#define MAILBOX_REQUEST 0

#define MAILBOX_CH_POWER 0
#define MAILBOX_CH_FB 1
#define MAILBOX_CH_VUART 2
#define MAILBOX_CH_VCHIQ 3
#define MAILBOX_CH_LEDS 4
#define MAILBOX_CH_BTNS 5
#define MAILBOX_CH_TOUCH 6
#define MAILBOX_CH_COUNT 7
// Request from ARM for response by VideoCore
#define MAILBOX_CH_PROP 8

#define MAILBOX_TAG_SETPOWER 0x28001
#define MAILBOX_TAG_SETCLKRATE 0x38002
#define MAILBOX_TAG_SETPHYWH 0x48003
#define MAILBOX_TAG_SETVIRTWH 0x48004
#define MAILBOX_TAG_SETVIRTOFF 0x48009
#define MAILBOX_TAG_SETDEPTH 0x48005
#define MAILBOX_TAG_SETPXLORDR 0x48006
#define MAILBOX_TAG_GETFB 0x40001
#define MAILBOX_TAG_GETPITCH 0x40008
#define MAILBOX_TAG_LAST 0

#define VIDEOCORE_MBOX (PERIPHERAL_BASE + 0x0000B880)
#define MAILBOX_READ (VIDEOCORE_MBOX + 0x0)
#define MAILBOX_POLL (VIDEOCORE_MBOX + 0x10)
#define MAILBOX_SENDER (VIDEOCORE_MBOX + 0x14)
#define MAILBOX_STATUS (VIDEOCORE_MBOX + 0x18)
#define MAILBOX_CONFIG (VIDEOCORE_MBOX + 0x1C)
#define MAILBOX_WRITE (VIDEOCORE_MBOX + 0x20)
#define MAILBOX_RESPONSE 0x80000000
#define MAILBOX_FULL 0x80000000
#define MAILBOX_EMPTY 0x40000000

void mmio_write(long reg, unsigned int val);
unsigned int mmio_read(long reg);

extern volatile unsigned int mbox[36];
unsigned int mbox_call(unsigned char ch);

#ifdef __cplusplus
}
#endif
