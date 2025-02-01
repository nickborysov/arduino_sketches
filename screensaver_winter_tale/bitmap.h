// Conditional macro for PROGMEM
#if defined(__AVR__) || defined(ARDUINO)
  #include <avr/pgmspace.h>
  #define PROGMEM_ATTR PROGMEM
#else
  #define PROGMEM_ATTR
#endif


#define DEER_WIDTH 32
#define DEER_HEIGHT 32

const uint16_t deerBitmap[DEER_HEIGHT][DEER_WIDTH] PROGMEM_ATTR = {
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x7B4B, 0x0000, 0x7B4B, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x7B4B, 0x0000, 0x7B4B, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x7B4B, 0x0000, 0xFFFF, 0x0000, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x7B4B, 0x0000, 0x7B4B, 0x7B4B, 0x7B4B, 0x0000, 0x0000, 0x7B4B, 0x0000, 0xFFFF, 0x0000, 0x7B4B, 0x7B4B, 0x0000, 0x7B4B, 0x0000 },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x7B4B, 0x7B4B, 0x7B4B, 0x0000, 0x7B4B, 0x7B4B, 0x7B4B, 0x7B4B, 0x0000, 0xFFFF, 0x0000, 0x7B4B, 0x0000, 0x7B4B, 0x7B4B, 0x0000 },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x7B4B, 0x7B4B, 0x0000, 0xFFFF, 0x0000, 0x7B4B, 0x0000, 0x7B4B, 0x0000, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x7B4B, 0x0000, 0x0000, 0x0000, 0x7B4B, 0x0000, 0x7B4B, 0x0000, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0x7B4B, 0x7B4B, 0x0000, 0x7B4B, 0x7B4B, 0x0000 },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCB, 0xABCC, 0xABCC, 0xE674, 0xE674, 0xE674, 0xABCC, 0x0000, 0xFFFF, 0x0000, 0x0000, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCB, 0xABCB, 0xE674, 0xE674, 0x0000, 0xE674, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xABCB, 0xEE73, 0xE674, 0xE674, 0xE674, 0xE674, 0xABCB, 0x0000, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xE674, 0xE674, 0xE674, 0xE674, 0xE674, 0xABCB, 0x0000, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0x0000, 0xE674, 0xE674, 0xEE74, 0xE674, 0xE674, 0xABCC, 0x0000, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCB, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCB, 0xABCC, 0xABCC, 0xE674, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCB, 0xABCC, 0xABCC, 0xABCC, 0xABCB, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xE674, 0xEE74, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0x0000, 0xEE73, 0x0000, 0xABCB, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCB, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCB, 0xE674, 0xE673, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCB, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xE674, 0xE674, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCB, 0xABCC, 0xABCB, 0xABCC, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xABCB, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xE674, 0xE674, 0xE674, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0x0000, 0xABCB, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0xE674, 0xE674, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCB, 0xABCB, 0xABCC, 0x0000, 0xE674, 0xE674, 0xE674, 0xE674, 0xE674, 0xE674, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0x0000, 0xEE74, 0xEE74, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0x0000, 0x0000, 0x0000, 0xE674, 0xE674, 0xE674, 0xE674, 0xE674, 0xE674, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0xABCC, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCB, 0xABCC, 0xABCB, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xABCC, 0xABCB, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0x0000, 0xABCC, 0xABCC, 0xABCB, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0x0000, 0x0000, 0xABCC, 0xABCC, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0x0000, 0xABCB, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0x0000, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCB, 0xABCB, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0x0000, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0x0000, 0xABCB, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCB, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xABCC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0x0000, 0x83AC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x7B4B, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x7B4B, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x8BAC, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
};

#define SANTA_WIDTH 36 
#define SANTA_HEIGHT 32 

const uint16_t santaBitmap[SANTA_HEIGHT][SANTA_WIDTH] PROGMEM_ATTR = {
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xA923, 0xA923, 0xA923, 0xB123, 0xB123, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xB123, 0xB123, 0xB143, 0xB123, 0xB123, 0xB123, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xB123, 0xB143, 0xB123, 0xB123, 0xB143, 0xB143, 0x9CD3, 0xCE79, 0x9CF3, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDD, 0xFF76, 0xFFDD, 0xEE79, 0xB123, 0xA942, 0xA2A8, 0xA943, 0xA942, 0xA943, 0xB595, 0xC638, 0xBD95, 0xCCED, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFF76, 0xFF76, 0xFF77, 0x8942, 0x8942, 0xFFFF, 0xFFFF, 0xFFFF, 0x8942, 0x8942, 0xB5B6, 0x9CD3, 0xED8E, 0xF58E, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xB596, 0xB596, 0xB5B6, 0xB5B6, 0xA514, 0xCE59, 0xA514, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xB596, 0x9CD3, 0xB596, 0xB596, 0xB5B6, 0xB596, 0xCE79, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xEE79, 0xB143, 0xB575, 0x9CD3, 0xB596, 0x9CF3, 0x9CD3, 0x9CD3, 0xB5B6, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xB123, 0xB143, 0xB143, 0xB123, 0xB123, 0xB143, 0xB123, 0x9CD3, 0x9CD3, 0x9CD3, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xF7BE, 0xF7BE, 0xF7BE, 0xF7BE },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xB143, 0xA943, 0xB123, 0xB123, 0xB143, 0xB143, 0xB123, 0xB123, 0xB143, 0xB123, 0xB123, 0xB123, 0xB143, 0xB143, 0xB143, 0xFF76, 0x3941, 0xF7BE, 0xF7BE, 0xF7BE, 0xF7BE, 0xF7BE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDE, 0xB123, 0xB123, 0xB143, 0xB123, 0xB123, 0xB143, 0xB143, 0xB123, 0xB123, 0xB143, 0xA923, 0xB143, 0xB123, 0xB123, 0xB143, 0xFF76, 0x9A65, 0x8942, 0xF7BE, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xF6EB, 0xF70B, 0xF6EB, 0xF70B, 0xF6EB, 0xF70B, 0xF6EB, 0xF70B, 0xC447, 0x8942, 0x8942, 0x9162, 0xB143, 0xB123, 0xB143, 0xB143, 0xB123, 0xA923, 0x91A3, 0xFFFF, 0x8942, 0x8942, 0x8942, 0xFF77, 0x8942, 0x8962, 0xFF96, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xDE32, 0xEE31, 0xA56F, 0xA56F, 0xA56F, 0xA56F, 0xA56F, 0xA56F, 0xF68B, 0xFF77, 0xFF76, 0xFF77, 0xBBCA, 0xA143, 0xA143, 0xB143, 0xB143, 0xB3ED, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFF96, 0xFF96, 0xFF96, 0xFF96, 0xFF75, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0x65D7, 0x6DF8, 0x65F8, 0x65F8, 0x65F8, 0x65F8, 0x9570, 0xF6EB, 0x8942, 0xFF76, 0xFF76, 0xFF76, 0xFF76, 0x8962, 0x8942, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF6EB, 0xCCE9, 0xD509, 0xD509, 0xD509, 0xCD09, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0x4371, 0x190B, 0x6DF8, 0x192C, 0x192C, 0x4391, 0x65D8, 0xFEEB, 0x8942, 0x8942, 0xB123, 0xB143, 0xB123, 0xA923, 0xFFFF, 0xFFFF, 0xFFFF, 0xD509, 0x6DD6, 0x65D7, 0x65F8, 0x65F8, 0x65F7, 0x65F8, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0x7BF4, 0x192C, 0x192C, 0x212C, 0x192C, 0x192C, 0x192C, 0xD508, 0xF70A, 0x8942, 0x9942, 0xB143, 0xB143, 0xB123, 0xFFFF, 0xFFFF, 0xF6EB, 0x6DD8, 0x210B, 0x210B, 0x6597, 0x210C, 0x5D36, 0x192C, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x214B, 0x192C, 0xFF76, 0x192B, 0x8430, 0x192B, 0x192B, 0x65F8, 0xF6EB, 0xF70B, 0xF70B, 0xF70B, 0xF70B, 0xF70B, 0xF6EB, 0x65F8, 0x192C, 0x192B, 0x192B, 0x318C, 0x192C, 0x192C, 0xFF77, 0x192C, 0x210C, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x212C, 0x212C, 0x190B, 0x190C, 0x9471, 0x190B, 0x192B, 0x190B, 0x212C, 0x212C, 0x65D8, 0x214C, 0x212B, 0x192B, 0x216C, 0x65D8, 0x192B, 0x192B, 0x192C, 0x192B, 0xFF76, 0xCE95, 0x212C, 0x212C, 0x192B, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x192C, 0x192C, 0x192B, 0x192C, 0x9471, 0x192C, 0xF776, 0x192C, 0x192C, 0x192C, 0x212C, 0xF756, 0x212C, 0x192C, 0x214C, 0x192C, 0xFF76, 0x192C, 0x192C, 0x192C, 0xFF76, 0xD675, 0x192C, 0x192C, 0x192C, 0xFFFF, 0xFFFF, 0xFFFF, 0xF6EB, 0xFEEB, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x192C, 0x192C, 0xAD32, 0x7390, 0x5B0F, 0x212C, 0x738F, 0xA511, 0x192C, 0x39EC, 0x212C, 0x6B90, 0xACF2, 0x192B, 0x294C, 0x192C, 0x736F, 0xA4F2, 0x210C, 0x294C, 0x192C, 0x298E, 0xAD12, 0x192C, 0x212C, 0xFFFF, 0xFF99, 0xE62A, 0xE611, 0xE611, 0xFF96, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x192C, 0x192C, 0x194B, 0x192C, 0x192C, 0x190B, 0x210C, 0x192C, 0x192C, 0x192C, 0x212B, 0x192B, 0x192C, 0x216C, 0x192C, 0x192C, 0x192B, 0x190B, 0x192C, 0x192C, 0x212B, 0x192C, 0x192C, 0xFFFF, 0xFFFF, 0xDDEF, 0xFFFF, 0xFFFF, 0xFFFF, 0xD509, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xE73D, 0x212C, 0x212C, 0x212C, 0x212C, 0x212C, 0x212C, 0x212C, 0x212C, 0x212C, 0x214C, 0x212C, 0x212C, 0x216D, 0x212C, 0x212C, 0x212C, 0x212C, 0x212C, 0x212C, 0x214C, 0xE75D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFBE, 0xD54B, 0xFFBD, 0xFFFF, 0xD509, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xC488, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xBC07, 0xFF9D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCD09, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xC488, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xBC07, 0xFF9D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF6EB, 0xD509, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xC488, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xBC07, 0xFF9D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xD509, 0xCD09, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xD4E9, 0xD4E9, 0xD509, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD509, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xD4E9, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
};


#define TREE_WIDTH  44
#define TREE_HEIGHT 50

const uint16_t treeBitmap[TREE_HEIGHT][TREE_WIDTH] PROGMEM_ATTR = {
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x10C2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1082, 0xE267, 0x18E3, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0080, 0xF72C, 0x1102, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1083, 0x9790, 0x662B, 0x9F51, 0xEF5D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1082, 0x9790, 0x662C, 0x76CE, 0x10A2, 0xAD55, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0881, 0x9790, 0x9F90, 0x772D, 0x76CC, 0x2223, 0x94B3, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xB5B6, 0xB5B6, 0x2A84, 0x9791, 0x97AF, 0x772E, 0x770D, 0x5E0B, 0x662C, 0x5549, 0xB5B4, 0xB5B6, 0xF7DF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0020, 0x9FB2, 0x9FB1, 0x97B0, 0x766E, 0x97D0, 0x772D, 0x772D, 0x7F2E, 0x656C, 0x3C08, 0x6E6D, 0x6ECD, 0x0921, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x8430, 0x5509, 0x660C, 0x65EB, 0x5DAB, 0x8F2F, 0x4CAA, 0x978F, 0x4448, 0x662D, 0x5D6C, 0x3BE8, 0x3308, 0x2AC8, 0x5DCB, 0x8470, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0021, 0x0862, 0x0842, 0x9FB0, 0x3386, 0x9791, 0x33A6, 0x33A8, 0x4448, 0x3C28, 0x5529, 0x0900, 0x9492, 0x0881, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0861, 0x9FB0, 0x9FB0, 0x9F91, 0x33A6, 0x33A8, 0x772E, 0x3BC7, 0x7E8F, 0x6E2D, 0x6EAD, 0x0060, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x18C3, 0x18E4, 0x9790, 0x9790, 0x772D, 0x2246, 0x9FD0, 0x9FD0, 0x770D, 0x770D, 0x33A7, 0x4CEA, 0x4488, 0x6EAC, 0x0920, 0x10A2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x39C7, 0x1082, 0x97AF, 0x9FB0, 0x6ECC, 0x662C, 0x2226, 0x9790, 0x772D, 0x3BC8, 0x772D, 0x3C27, 0x662B, 0x3BA8, 0x4449, 0x4468, 0x6ECC, 0x6EAC, 0x18C4, 0x10A3, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0x9750, 0x6ECC, 0x6EAC, 0x2AC7, 0x2AC8, 0x2AC7, 0x97B0, 0x97B0, 0x3BC7, 0x3BC8, 0x772D, 0x3BC8, 0x554A, 0x664B, 0x0902, 0x2AC8, 0x2AC8, 0x2AC7, 0x3BC8, 0x770D, 0x10A2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x4208, 0x10A2, 0x10A2, 0xFFFF, 0x2AC7, 0x2AC7, 0x556A, 0x2246, 0x2AC8, 0x97B0, 0x772D, 0x65CC, 0x2AC8, 0x2AC6, 0x11E4, 0x08A2, 0xEF9D, 0x5ACB, 0x10A2, 0x10A2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x2AC5, 0x558A, 0x4468, 0x4468, 0x2AC7, 0x2AC7, 0x10A2, 0x774D, 0x08E2, 0x2AC7, 0x2AC7, 0x2AC7, 0x660C, 0x0941, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1144, 0x1924, 0x976F, 0x9790, 0x6ECC, 0x6ECC, 0x556A, 0x2AC7, 0x2AC7, 0x10A2, 0x2AC7, 0x2B07, 0x3BC7, 0x554A, 0x662B, 0x662B, 0x0921, 0x08A2, 0x08A2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x10A2, 0x1083, 0x6EAC, 0x6EAC, 0x10A2, 0x9790, 0x9790, 0x9FD0, 0x556A, 0x4468, 0x4468, 0x556A, 0x3BC8, 0x3BC8, 0x44A9, 0x662B, 0x662B, 0x4469, 0x4468, 0x6EAC, 0x6ECC, 0x10A3, 0x2125, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x10C3, 0x10A3, 0x9FD0, 0x662B, 0x2B45, 0x1124, 0x9791, 0x6ECB, 0x4D29, 0x556A, 0x1145, 0x9FD0, 0x9FD0, 0x554A, 0x9F90, 0x8E70, 0x19E5, 0x33C7, 0x662B, 0x4469, 0x2B26, 0x3346, 0x2B46, 0x6ECC, 0x6ECC, 0x10A3, 0x0861, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x18C3, 0x97B0, 0x664B, 0x2226, 0x10C3, 0x2AC8, 0x2AC7, 0x9F52, 0x4CCB, 0x554B, 0x1181, 0x97B0, 0x6EAD, 0x11A2, 0x9790, 0x1A43, 0x65EC, 0x660D, 0x3348, 0x3BA8, 0x556B, 0x00E1, 0x10A2, 0x10A2, 0x10A3, 0x3BC7, 0x3BC8, 0x772D, 0x10C2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x52AA, 0x630C, 0x630C, 0xFFFF, 0x2AA7, 0x2AE8, 0x2AE7, 0x2AC7, 0x10A3, 0x8EEF, 0x5D8C, 0x2AE7, 0x8ED0, 0x9790, 0x6CED, 0x3327, 0x4449, 0x22C6, 0x2225, 0x1A06, 0x2246, 0x10C2, 0xEF7E, 0xFFFF, 0x18E3, 0x18E3, 0x1082, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0081, 0x9F91, 0x9FD0, 0x662C, 0x2AC7, 0x2AC7, 0x2AE8, 0x2AC8, 0x2AA7, 0x2A87, 0x18E4, 0x2226, 0x2226, 0x2226, 0x2226, 0x2226, 0x2AC7, 0x5DAB, 0x660B, 0x1984, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1904, 0x2B26, 0x9FB0, 0x6E8B, 0x6ECC, 0x2AE8, 0x97B0, 0x772D, 0x6EAC, 0x6EAC, 0x4488, 0x2AC7, 0x2AC7, 0x2B06, 0x4468, 0x4468, 0x558A, 0x662B, 0x5DCC, 0x3C28, 0x6ECC, 0x6EAC, 0x4448, 0x2AC8, 0x1082, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x10A2, 0x10A2, 0x9FD0, 0x97B0, 0x556A, 0x556A, 0x2226, 0x97B0, 0x6ECC, 0x9F90, 0x1926, 0x9FB1, 0x10A3, 0x3BC8, 0x664B, 0x3347, 0x662C, 0x664C, 0x22C5, 0x662C, 0x662B, 0x5D6B, 0x4468, 0x4468, 0x4468, 0x6ECC, 0x6E8C, 0x1082, 0x08C2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x10A2, 0x662B, 0x664B, 0x4468, 0x3327, 0x3327, 0x2AE6, 0x9FD0, 0x556A, 0x556A, 0x21E5, 0x9790, 0x6EAC, 0x6ECC, 0x6EAB, 0x6ECC, 0x6EAC, 0x556B, 0x558A, 0x54AB, 0x3BC8, 0x3BE7, 0x4CE8, 0x0862, 0x2AC7, 0x2AC7, 0x2AC7, 0x2AC7, 0x2B07, 0x6ECB, 0x1082, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x10A2, 0x10A2, 0xFFFF, 0xFFFF, 0x0080, 0x3BE7, 0x2AC7, 0x2AC7, 0x2AC7, 0x97D0, 0x6ECC, 0x6ECC, 0x00C0, 0x874E, 0x6ECC, 0x6EAB, 0x2225, 0x558A, 0x558A, 0x10E2, 0x2246, 0x2226, 0x2AC7, 0x2AC7, 0x10A2, 0xFFFF, 0x10A2, 0x10A2, 0x10A2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1943, 0x10C2, 0x9790, 0x660B, 0x2AC7, 0x2AE7, 0x2AA7, 0x2246, 0x2225, 0x2225, 0x2225, 0x65EC, 0x6ECC, 0x2226, 0x2226, 0x2225, 0x2225, 0x2225, 0x2226, 0x2285, 0x3BA8, 0x3BE7, 0x4468, 0x1082, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE79, 0x2165, 0x2125, 0x97D0, 0x9790, 0x6ECD, 0x9FB1, 0x9790, 0x556B, 0x55AA, 0x8F0F, 0x44A9, 0x2225, 0x2225, 0x1A25, 0x1A25, 0x2226, 0x2226, 0x2226, 0x2AC7, 0x2205, 0x2226, 0x3BE6, 0x662B, 0x10C5, 0x664B, 0x5E2A, 0x662B, 0x18A2, 0x18C3, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE59, 0x97B0, 0x556B, 0x556A, 0x2AC8, 0x2AA7, 0x0900, 0x9FB0, 0x556A, 0x558A, 0x10A4, 0x9790, 0x552A, 0x4D2A, 0x552A, 0x4D2A, 0x4D2A, 0x33C7, 0x3BC8, 0x3BE7, 0x6E8D, 0x18C2, 0x1A25, 0x3347, 0x664B, 0x662B, 0x10A3, 0x2AC7, 0x2AC7, 0x6EEB, 0x6EAC, 0x6ECC, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x4347, 0x558B, 0x556A, 0x00C0, 0x10C2, 0x10A2, 0x9FB1, 0x556A, 0x556A, 0x10C3, 0x9F90, 0x554A, 0x556A, 0x5529, 0x00C0, 0x770D, 0x772D, 0x3B89, 0x558A, 0x1105, 0x554B, 0x774D, 0x776D, 0x1162, 0x3326, 0x3326, 0x556A, 0x10A2, 0x0881, 0x0881, 0x2AC7, 0x4467, 0x0080, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xD69A, 0x0861, 0x0861, 0xFFFF, 0x2103, 0x22A7, 0x1082, 0x1062, 0x1061, 0x9790, 0x55AA, 0x2A65, 0x7E6D, 0x9790, 0x00C0, 0x770D, 0x772D, 0x4428, 0x2245, 0x558A, 0x19A4, 0x4CE9, 0x4CA9, 0x6E4D, 0x1963, 0x1963, 0x1944, 0x10A2, 0xFFFF, 0xFFFF, 0x18E3, 0x1904, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0020, 0x3BC8, 0x2AC7, 0x2B27, 0x3347, 0x3347, 0x10A3, 0x10A3, 0x10A2, 0x664C, 0x9790, 0x10A2, 0x772D, 0x772D, 0x1103, 0x1082, 0x558A, 0x08A2, 0x10A2, 0x10A2, 0x08A2, 0x19A5, 0x19A5, 0x19A5, 0x19A5, 0x10A3, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x18E4, 0x9FB1, 0x9750, 0x4427, 0x3C48, 0x3C48, 0x2B05, 0x2AC7, 0x3387, 0x2225, 0x2226, 0x10A2, 0x2245, 0x2225, 0x2225, 0x2226, 0x19A4, 0x10A2, 0x19A5, 0x19A4, 0x19A4, 0x19C4, 0x19A5, 0x22A7, 0x5DEC, 0x660C, 0x664B, 0x4CC9, 0x552A, 0xDEDB, 0xE73C, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x18E3, 0x9F71, 0x97AF, 0x97F0, 0x97B1, 0x0061, 0x8F70, 0x556A, 0x65EB, 0x9F90, 0x556A, 0x4468, 0x4468, 0x2AC7, 0x2AC7, 0x2AC7, 0x2AC7, 0x2AC7, 0x1082, 0x33AA, 0x1985, 0x19A5, 0x19A5, 0x19A5, 0x2AC7, 0x22E5, 0x662B, 0x662B, 0x2266, 0x4468, 0x662B, 0x0061, 0x4448, 0x6EEC, 0x6EEC, 0x0841, 0x0841, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0x2124, 0x2124, 0x9FD0, 0x9FB0, 0x4468, 0x4488, 0x3BE8, 0x97CF, 0x556A, 0x558A, 0x19E2, 0x556A, 0x556A, 0x4468, 0x1A43, 0x2AC7, 0x2AC7, 0x10A2, 0x2AC8, 0x2AC7, 0x1082, 0x2AC7, 0x446C, 0x10A2, 0x1984, 0x558A, 0x1082, 0x2AC7, 0x556A, 0x664B, 0x2AE5, 0x3346, 0x3347, 0x448D, 0x1883, 0x3346, 0x6ECD, 0x6ECB, 0x6ECB, 0x2104, 0xF7BF, 0xFFFF },
    { 0xFFFF, 0x0841, 0x664B, 0x662B, 0x4468, 0x4468, 0x3BC9, 0x4409, 0x8ECF, 0x2285, 0x2226, 0x8EAF, 0x86D2, 0x2AC7, 0x2AC7, 0x10C2, 0x4409, 0x2AC7, 0x2AA7, 0x446D, 0x2AC8, 0x2AC7, 0x1082, 0x2AC7, 0x446D, 0x448D, 0x2AC7, 0x2AC7, 0x558B, 0x00A1, 0x2226, 0x3326, 0x2B26, 0x3307, 0x3327, 0x3326, 0x3388, 0x3307, 0x3326, 0x4468, 0x4468, 0x3347, 0x0041, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0x18A3, 0x1883, 0x18A3, 0x18A3, 0xFFFF, 0xFFFF, 0x08A1, 0x08A1, 0x19A4, 0x08C0, 0x00A1, 0x08A1, 0x08A1, 0x558A, 0x22A7, 0x0080, 0x2AA7, 0x448D, 0x2AC7, 0x08A2, 0x10A2, 0x2A47, 0x22A7, 0x446D, 0x0081, 0x2AC7, 0x2AC7, 0x2AC7, 0x0881, 0x0060, 0x1144, 0x08A2, 0x10A2, 0x0881, 0x10A2, 0xFFFF, 0x0860, 0x0881, 0x0881, 0x0881, 0xF7BE, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x10A2, 0x1185, 0x19A4, 0x19A4, 0x19A4, 0x0881, 0x0881, 0x0881, 0x2AA8, 0x444C, 0x2AE8, 0x5183, 0x5183, 0x3A46, 0x2AC7, 0x446C, 0x08A2, 0x0882, 0x0882, 0x10A2, 0x1184, 0x19A4, 0x2AA7, 0x0040, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0020, 0x662B, 0x326A, 0x19A4, 0x19A4, 0x0881, 0x08A1, 0x2207, 0x19A4, 0x08A1, 0x0081, 0x3922, 0x3923, 0x3923, 0x3922, 0x0881, 0x08A1, 0x08A2, 0x19A4, 0x19A4, 0x10A2, 0x2246, 0x2AC7, 0x2AC7, 0x448D, 0x1082, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xEFBE, 0x664C, 0x2AC7, 0x3269, 0x19A4, 0x0881, 0xFFFF, 0x08A1, 0x2207, 0x19A4, 0x10A2, 0x3923, 0x3923, 0x6A05, 0x6A05, 0x59C4, 0x3923, 0x3103, 0x19A4, 0x19A5, 0x19A4, 0x1082, 0x738E, 0x1103, 0x2AC7, 0x2AC7, 0x5569, 0x10A2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0922, 0x22A5, 0x2AC8, 0x0041, 0x0041, 0xFFFF, 0xFFFF, 0x08A1, 0x29C6, 0xDEBA, 0x10C3, 0x6A05, 0x6A05, 0x6A05, 0x6A05, 0x51A4, 0x2902, 0x3943, 0xDEFB, 0x1123, 0x1123, 0x0882, 0xFFFF, 0xF7BE, 0x1904, 0x2AC8, 0x2AA8, 0x554B, 0x10A2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xDEFB, 0xDEFB, 0xDF1B, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0881, 0xFFFF, 0xFFFF, 0x10C3, 0x6A05, 0x3943, 0x6205, 0x6A05, 0x6A05, 0x6A05, 0x3944, 0xFFFF, 0xFFFF, 0xFFFF, 0x0861, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x10C3, 0xA2A7, 0xAB88, 0xAB68, 0x6A05, 0x6A05, 0x6A05, 0x3944, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x10C3, 0x9AA6, 0xAB88, 0xAB68, 0x7225, 0x61E5, 0x6205, 0x3964, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0861, 0x10A2, 0xF74C, 0xF74C, 0xAB68, 0xAB68, 0x9307, 0x6A05, 0x3943, 0x0861, 0x0861, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x10A2, 0x10A2, 0x10A2, 0xF72C, 0xF72C, 0xAB88, 0xAB69, 0xAB68, 0x7B27, 0xD5CD, 0x6A05, 0x5183, 0x5183, 0x4983, 0x18A3, 0x18A3, 0x18A3, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1082, 0x1082, 0x0841, 0xF72C, 0xF72C, 0xF72C, 0xA387, 0xAB87, 0xEF2C, 0xB388, 0x92E7, 0x51E5, 0xAB88, 0xAB67, 0x9B48, 0x08A1, 0x4164, 0x7205, 0x6A05, 0x7205, 0x10A2, 0x10A2, 0x10A2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0020, 0x10A2, 0xAB67, 0xAB68, 0xAB68, 0xAB68, 0xAB68, 0xAB68, 0xAB68, 0xAB68, 0xAB68, 0xAB68, 0x92E6, 0x6A05, 0x6205, 0x5183, 0x5183, 0x5183, 0x5183, 0x5183, 0x5183, 0x5183, 0x5183, 0x5183, 0x3922, 0x10A2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
    { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2125, 0x2125, 0x2125, 0x2125, 0x2125, 0x2125, 0x2125, 0x2125, 0x2124, 0x2124, 0x2124, 0x2124, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF },
};


#define SNOWFLAKE_WIDTH  7
#define SNOWFLAKE_HEIGHT 7

const uint16_t snowflakeBitmap[SNOWFLAKE_HEIGHT][SNOWFLAKE_WIDTH] PROGMEM_ATTR = {
    { 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000 },
    { 0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000 },
    { 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF },
    { 0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000 },
    { 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000 },
    { 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000 },
};

