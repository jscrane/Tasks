#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#define SERIAL 	115200

#elif defined(__MSP430FR5739__)
#define SERIAL 	9600

#else
#error "Unsupported architecture!"

#endif
