#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#define LED	13
#define SERIAL 	115200

#elif defined(__MSP430FR5739__) || defined(__MSP430G2553__)
#define LED	RED_LED
#define SERIAL 	9600

#elif defined(__AVR_ATtiny85__)
#define LED	0
#undef SERIAL

#else
#error "Unsupported architecture!"

#endif
