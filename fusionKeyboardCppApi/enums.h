#pragma once

#include <stdint.h>
#include <cstdio>
#include "Status.h"

#pragma pack(push, 1)
typedef struct {
  // Kind of the control transfer
  uint8_t kind;
  // ?? always zeroed
  uint8_t reserved;
  // mode or config slot
  uint8_t mode;
  // Speed or length of usb packets to follow
  uint8_t speedLength;
  // Brightness. 0 to 50
  uint8_t brightness;
  // Predefined color
  uint8_t color;
  uint8_t reserved2;
  uint8_t checksum;
} header_t;
#pragma pack(pop)


#define KIND_PRESET 0x08
#define KIND_READ_CONFIG 0x92
#define KIND_CUSTOM_CONFIG 0x12

#define RESERVED1 0x00

// This is the list of predefined modes.
// For custom config, this byte describes the config slot
#define MODE_STATIC 0x01
#define MODE_BREATHING 0x02
#define MODE_WAVE 0x03
#define MODE_FADE_ON_KEYPRESS 0x04
#define MODE_MARQUEE 0x05
#define MODE_RIPPLE 0x06
#define MODE_FLASH_ON_KEYPRESS 0x07
#define MODE_NEON 0x08
#define MODE_RAINBOW_MARQUEE 0x09
#define MODE_RAINDROP 0x0a
#define MODE_CIRCLE_MARQUEE 0x0b
#define MODE_HEDGE 0x0c
#define MODE_ROTATE 0x0d

#define COLOR_RED 0x01
#define COLOR_GREEN 0x02
#define COLOR_YELLOW 0x03
#define COLOR_BLUE 0x04
#define COLOR_PURPLE 0x05
#define COLOR_AQUA 0x06
#define COLOR_WHITE 0x07


