#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
 || defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__)
#define ARCH atmega
#elif defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny45__)
 ||   defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny44__)
#define ARCH attiny
#elif defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny44__)
#define ARCH attiny84
#elif defined(__MSP430FR5739__) || defined(__MSP430G2553__)
#define ARCH msp430
#else
#error "Unknown arch!"
#endif
#define PROC_ARCH(f) <../ARCH/f>

