#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#define LED	13

#elif defined(__MSP430FR5739__)
#define LED	RED_LED

#elif defined(__AVR_ATtiny85__)
#define LED	0

#else
#error "Unsupported architecture!"

#endif
