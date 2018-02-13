#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)

#define SERIAL 115200
#define STACK	100
#define MAX	5
#define LED1	9
#define LED2	10
#define LED3	11
#define LED4	12
#define LED5	13

#elif defined(__MSP430FR5739__)

//#define SERIAL 9600
#define STACK	100
#define MAX	4

#else

#error "Unsupported architecture!"

#endif
