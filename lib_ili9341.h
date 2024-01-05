/*
 * File:   my_lib_ili9341.h
 * Author: lcond
 *
 * Created on September 23, 2020, 6:46 PM
 */

#ifndef LIB_ILI9341_H
#define LIB_ILI9341_H

// #include <xc.h>
#include <stdint.h>
#include <stdbool.h>

// #define _XTAL_FREQ  8000000

/*******************************************************************************
 * Pin assignment
 */

#define LCD_DC LATEbits.LE0 /* Data or Command */
#define LCD_CS LATEbits.LE1 /* SPI Chip select */

/*******************************************************************************
 * Usefull Makros for the LCD-Functions
 */

#define LCD_REG 0
#define LCD_DATA 1

#define LCD_WIDTH 320
#define LCD_HEIGHT 240

#define WHITE 0xFFFF
#define SILVER 0xC618
#define BLACK 0x0000
#define GREY 0x8410
#define RED 0xF800
#define MAROON 0x8000
#define FUCHSIA 0xF81F
#define PURPLE 0x8010
#define LIME 0x07E0
#define GREEN 0x0400
#define YELLOW 0xFFE0
#define OLIVE 0x8400
#define BLUE 0x001F
#define NAVY 0x0010
#define AQUA 0x07FF
#define TEAL 0x0410
#define DARK_BLUE 0x0002

#define ILI9341_TFTWIDTH 240  ///< ILI9341 max TFT width
#define ILI9341_TFTHEIGHT 320 ///< ILI9341 max TFT height

#define ILI9341_NOP 0x00     ///< No-op register
#define ILI9341_SWRESET 0x01 ///< Software reset register
#define ILI9341_RDDID 0x04   ///< Read display identification information
#define ILI9341_RDDST 0x09   ///< Read Display Status

#define ILI9341_SLPIN 0x10  ///< Enter Sleep Mode
#define ILI9341_SLPOUT 0x11 ///< Sleep Out
#define ILI9341_PTLON 0x12  ///< Partial Mode ON
#define ILI9341_NORON 0x13  ///< Normal Display Mode ON

#define ILI9341_RDMODE 0x0A     ///< Read Display Power Mode
#define ILI9341_RDMADCTL 0x0B   ///< Read Display MADCTL
#define ILI9341_RDPIXFMT 0x0C   ///< Read Display Pixel Format
#define ILI9341_RDIMGFMT 0x0D   ///< Read Display Image Format
#define ILI9341_RDSELFDIAG 0x0F ///< Read Display Self-Diagnostic Result

#define ILI9341_INVOFF 0x20   ///< Display Inversion OFF
#define ILI9341_INVON 0x21    ///< Display Inversion ON
#define ILI9341_GAMMASET 0x26 ///< Gamma Set
#define ILI9341_DISPOFF 0x28  ///< Display OFF
#define ILI9341_DISPON 0x29   ///< Display ON

#define ILI9341_CASET 0x2A ///< Column Address Set
#define ILI9341_PASET 0x2B ///< Page Address Set
#define ILI9341_RAMWR 0x2C ///< Memory Write
#define ILI9341_RAMRD 0x2E ///< Memory Read

#define ILI9341_PTLAR 0x30    ///< Partial Area
#define ILI9341_VSCRDEF 0x33  ///< Vertical Scrolling Definition
#define ILI9341_MADCTL 0x36   ///< Memory Access Control
#define ILI9341_VSCRSADD 0x37 ///< Vertical Scrolling Start Address
#define ILI9341_PIXFMT 0x3A   ///< COLMOD: Pixel Format Set

#define ILI9341_FRMCTR1 \
  0xB1                       ///< Frame Rate Control (In Normal Mode/Full Colors)
#define ILI9341_FRMCTR2 0xB2 ///< Frame Rate Control (In Idle Mode/8 colors)
#define ILI9341_FRMCTR3 \
  0xB3                       ///< Frame Rate control (In Partial Mode/Full Colors)
#define ILI9341_INVCTR 0xB4  ///< Display Inversion Control
#define ILI9341_DFUNCTR 0xB6 ///< Display Function Control

#define ILI9341_PWCTR1 0xC0 ///< Power Control 1
#define ILI9341_PWCTR2 0xC1 ///< Power Control 2
#define ILI9341_PWCTR3 0xC2 ///< Power Control 3
#define ILI9341_PWCTR4 0xC3 ///< Power Control 4
#define ILI9341_PWCTR5 0xC4 ///< Power Control 5
#define ILI9341_VMCTR1 0xC5 ///< VCOM Control 1
#define ILI9341_VMCTR2 0xC7 ///< VCOM Control 2

#define ILI9341_RDID1 0xDA ///< Read ID 1
#define ILI9341_RDID2 0xDB ///< Read ID 2
#define ILI9341_RDID3 0xDC ///< Read ID 3
#define ILI9341_RDID4 0xDD ///< Read ID 4

#define ILI9341_GMCTRP1 0xE0 ///< Positive Gamma Correction
#define ILI9341_GMCTRN1 0xE1 ///< Negative Gamma Correction
// #define ILI9341_PWCTR6     0xFC

// Color definitions
#define ILI9341_BLACK 0x0000       ///<   0,   0,   0
#define ILI9341_NAVY 0x000F        ///<   0,   0, 123
#define ILI9341_DARKGREEN 0x03E0   ///<   0, 125,   0
#define ILI9341_DARKCYAN 0x03EF    ///<   0, 125, 123
#define ILI9341_MAROON 0x7800      ///< 123,   0,   0
#define ILI9341_PURPLE 0x780F      ///< 123,   0, 123
#define ILI9341_OLIVE 0x7BE0       ///< 123, 125,   0
#define ILI9341_LIGHTGREY 0xC618   ///< 198, 195, 198
#define ILI9341_DARKGREY 0x7BEF    ///< 123, 125, 123
#define ILI9341_BLUE 0x001F        ///<   0,   0, 255
#define ILI9341_GREEN 0x07E0       ///<   0, 255,   0
#define ILI9341_CYAN 0x07FF        ///<   0, 255, 255
#define ILI9341_RED 0xF800         ///< 255,   0,   0
#define ILI9341_MAGENTA 0xF81F     ///< 255,   0, 255
#define ILI9341_YELLOW 0xFFE0      ///< 255, 255,   0
#define ILI9341_WHITE 0xFFFF       ///< 255, 255, 255
#define ILI9341_ORANGE 0xFD20      ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define ILI9341_PINK 0xFC18        ///< 255, 130, 198

#define FONT_HEIGHT 2

const unsigned short font[] =
    {
        0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                                     // Code for char ' '
        0x03, 0x00, 0x00, 0xFE, 0x1B, 0x00, 0x00,                                                                                                                                                 // Code for char !
        0x05, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00,                                                                                                                         // Code for char "
        0x0B, 0x00, 0x00, 0x10, 0x01, 0x10, 0x1D, 0xF0, 0x03, 0x1E, 0x01, 0x10, 0x01, 0x10, 0x1D, 0xF0, 0x03, 0x1E, 0x01, 0x10, 0x01, 0x00, 0x00,                                                 // Code for char #
        0x09, 0x00, 0x04, 0x1C, 0x08, 0x22, 0x10, 0x42, 0x10, 0xFF, 0x7F, 0x42, 0x10, 0x84, 0x10, 0x00, 0x0F, 0x00, 0x00,                                                                         // Code for char $
        0x0C, 0x1C, 0x00, 0x22, 0x10, 0x22, 0x08, 0x22, 0x06, 0x1C, 0x01, 0xC0, 0x00, 0x20, 0x0E, 0x18, 0x11, 0x04, 0x11, 0x02, 0x11, 0x00, 0x0E, 0x00, 0x00,                                     // Code for char %
        0x0B, 0x00, 0x00, 0x00, 0x0E, 0x1C, 0x11, 0xA2, 0x10, 0xC2, 0x10, 0x22, 0x11, 0x1C, 0x0A, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x00,                                                 // Code for char &
        0x03, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00,                                                                                                                                                 // Code for char '
        0x06, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x1F, 0x1C, 0x60, 0x02, 0x80, 0x00, 0x00,                                                                                                             // Code for char (
        0x04, 0x00, 0x00, 0x06, 0xC0, 0xF8, 0x3F, 0x00, 0x00,                                                                                                                                     // Code for char )
        0x06, 0x24, 0x00, 0x18, 0x00, 0x7E, 0x00, 0x18, 0x00, 0x24, 0x00, 0x00, 0x00,                                                                                                             // Code for char *
        0x09, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0xF0, 0x07, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00,                                                                         // Code for char +
        0x04, 0x00, 0x00, 0x00, 0x60, 0x00, 0x18, 0x00, 0x00,                                                                                                                                     // Code for char ,
        0x05, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00,                                                                                                                         // Code for char -
        0x04, 0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0x00, 0x00,                                                                                                                                     // Code for char .
        0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x38, 0x00, 0x07, 0xE0, 0x00, 0x1C, 0x00, 0x02, 0x00, 0x00, 0x00,                                                                                     // Code for char /
        0x09, 0xF8, 0x07, 0x04, 0x08, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x04, 0x08, 0xF8, 0x07, 0x00, 0x00,                                                                         // Code for char 0
        0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0xFE, 0x1F, 0x00, 0x00,                                                                         // Code for char 1
        0x09, 0x18, 0x10, 0x04, 0x18, 0x02, 0x14, 0x02, 0x12, 0x02, 0x11, 0x82, 0x10, 0x44, 0x10, 0x38, 0x10, 0x00, 0x00,                                                                         // Code for char 2
        0x09, 0x08, 0x0C, 0x04, 0x10, 0x02, 0x10, 0x42, 0x10, 0x42, 0x10, 0x44, 0x10, 0xB8, 0x08, 0x00, 0x07, 0x00, 0x00,                                                                         // Code for char 3
        0x09, 0x00, 0x02, 0x00, 0x03, 0x80, 0x02, 0x60, 0x02, 0x10, 0x02, 0x08, 0x02, 0xFE, 0x1F, 0x00, 0x02, 0x00, 0x00,                                                                         // Code for char 4
        0x09, 0x00, 0x04, 0x70, 0x08, 0x2E, 0x10, 0x22, 0x10, 0x22, 0x10, 0x22, 0x10, 0x42, 0x08, 0x82, 0x07, 0x00, 0x00,                                                                         // Code for char 5
        0x09, 0x00, 0x00, 0x00, 0x07, 0xC0, 0x08, 0x60, 0x10, 0x58, 0x10, 0x44, 0x10, 0x82, 0x08, 0x00, 0x07, 0x00, 0x00,                                                                         // Code for char 6
        0x09, 0x00, 0x00, 0x02, 0x10, 0x02, 0x0C, 0x02, 0x03, 0xC2, 0x00, 0x32, 0x00, 0x0E, 0x00, 0x02, 0x00, 0x00, 0x00,                                                                         // Code for char 7
        0x09, 0x00, 0x07, 0x98, 0x08, 0x64, 0x10, 0x42, 0x10, 0x42, 0x10, 0x64, 0x10, 0x98, 0x08, 0x00, 0x07, 0x00, 0x00,                                                                         // Code for char 8
        0x09, 0x00, 0x00, 0x38, 0x00, 0x44, 0x10, 0x82, 0x08, 0x82, 0x04, 0x82, 0x03, 0x84, 0x00, 0x78, 0x00, 0x00, 0x00,                                                                         // Code for char 9
        0x04, 0x00, 0x00, 0x30, 0x18, 0x30, 0x18, 0x00, 0x00,                                                                                                                                     // Code for char :
        0x04, 0x00, 0x00, 0x30, 0x60, 0x30, 0x18, 0x00, 0x00,                                                                                                                                     // Code for char ;
        0x0A, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x40, 0x01, 0x20, 0x02, 0x20, 0x02, 0x10, 0x04, 0x10, 0x04, 0x08, 0x08, 0x00, 0x00,                                                             // Code for char <
        0x0A, 0x00, 0x00, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x00, 0x00,                                                             // Code for char =
        0x0A, 0x00, 0x00, 0x08, 0x08, 0x10, 0x04, 0x10, 0x04, 0x20, 0x02, 0x20, 0x02, 0x40, 0x01, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00,                                                             // Code for char >
        0x08, 0x00, 0x00, 0x0C, 0x00, 0x82, 0x01, 0x42, 0x02, 0x22, 0x1A, 0x22, 0x1A, 0x9C, 0x01, 0x00, 0x00,                                                                                     // Code for char ?
        0x0E, 0x00, 0x00, 0xF0, 0x03, 0x08, 0x04, 0x04, 0x08, 0xC2, 0x11, 0x22, 0x12, 0x12, 0x12, 0x12, 0x12, 0xE2, 0x11, 0x12, 0x12, 0x04, 0x12, 0x08, 0x09, 0xF0, 0x04, 0x00, 0x00,             // Code for char @
        0x0D, 0x00, 0x00, 0x00, 0x10, 0x00, 0x0E, 0x80, 0x01, 0x60, 0x01, 0x1C, 0x01, 0x02, 0x01, 0x1C, 0x01, 0x60, 0x01, 0x80, 0x01, 0x00, 0x0E, 0x00, 0x10, 0x00, 0x00,                         // Code for char A
        0x09, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x42, 0x10, 0x42, 0x10, 0x64, 0x10, 0x98, 0x08, 0x00, 0x07, 0x00, 0x00,                                                                         // Code for char B
        0x0D, 0x00, 0x00, 0xF0, 0x03, 0x08, 0x04, 0x04, 0x08, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x04, 0x08, 0x04, 0x08, 0x08, 0x04, 0x00, 0x00,                         // Code for char C
        0x0C, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x04, 0x08, 0x08, 0x04, 0xF0, 0x03, 0x00, 0x00,                                     // Code for char D
        0x09, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x42, 0x10, 0x42, 0x10, 0x42, 0x10, 0x42, 0x10, 0x42, 0x10, 0x00, 0x00,                                                                         // Code for char E
        0x08, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x42, 0x00, 0x42, 0x00, 0x42, 0x00, 0x42, 0x00, 0x00, 0x00,                                                                                     // Code for char F
        0x0E, 0x00, 0x00, 0xF0, 0x03, 0x08, 0x04, 0x04, 0x08, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x82, 0x10, 0x84, 0x10, 0x84, 0x08, 0x88, 0x04, 0x80, 0x03, 0x00, 0x00,             // Code for char G
        0x0A, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0xFE, 0x1F, 0x00, 0x00,                                                             // Code for char H
        0x04, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x00, 0x00,                                                                                                                                     // Code for char I
        0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x10, 0x00, 0x10, 0x00, 0x08, 0xFE, 0x07, 0x00, 0x00,                                                                                                 // Code for char J
        0x09, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x60, 0x00, 0x90, 0x01, 0x08, 0x02, 0x04, 0x0C, 0x02, 0x10, 0x00, 0x00,                                                                         // Code for char K
        0x08, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00,                                                                                     // Code for char L
        0x0F, 0x00, 0x00, 0x00, 0x1C, 0xF8, 0x03, 0x06, 0x00, 0x38, 0x00, 0xC0, 0x01, 0x00, 0x0E, 0x00, 0x10, 0x00, 0x0E, 0xC0, 0x01, 0x38, 0x00, 0x06, 0x00, 0xF8, 0x03, 0x00, 0x1C, 0x00, 0x00, // Code for char M
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x08, 0x00, 0x30, 0x00, 0x40, 0x00, 0x80, 0x00, 0x00, 0x03, 0x00, 0x04, 0xFE, 0x1F, 0x00, 0x00,                                                 // Code for char N
        0x0E, 0x00, 0x00, 0xF0, 0x03, 0x08, 0x04, 0x04, 0x08, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x04, 0x08, 0x08, 0x04, 0xF0, 0x03, 0x00, 0x00,             // Code for char O
        0x09, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x42, 0x00, 0x42, 0x00, 0x42, 0x00, 0x24, 0x00, 0x18, 0x00, 0x00, 0x00,                                                                         // Code for char P
        0x0E, 0x00, 0x00, 0xF0, 0x03, 0x08, 0x04, 0x04, 0x08, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x11, 0x02, 0x12, 0x02, 0x0C, 0x04, 0x08, 0x08, 0x16, 0xF0, 0x21, 0x00, 0x00,             // Code for char Q
        0x0A, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x42, 0x00, 0xC2, 0x00, 0x42, 0x01, 0x42, 0x06, 0x24, 0x08, 0x18, 0x10, 0x00, 0x00,                                                             // Code for char R
        0x08, 0x00, 0x04, 0x18, 0x08, 0x24, 0x10, 0x42, 0x10, 0x42, 0x10, 0x84, 0x08, 0x08, 0x07, 0x00, 0x00,                                                                                     // Code for char S
        0x08, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0xFE, 0x1F, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00,                                                                                     // Code for char T
        0x0A, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x07, 0x00, 0x08, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x08, 0xFE, 0x07, 0x00, 0x00,                                                             // Code for char U
        0x0C, 0x02, 0x00, 0x1C, 0x00, 0x60, 0x00, 0x80, 0x01, 0x00, 0x0E, 0x00, 0x10, 0x00, 0x0E, 0x80, 0x01, 0x60, 0x00, 0x1C, 0x00, 0x02, 0x00, 0x00, 0x00,                                     // Code for char V
        0x0F, 0x00, 0x00, 0x06, 0x00, 0x78, 0x00, 0x80, 0x07, 0x00, 0x18, 0x80, 0x07, 0x78, 0x00, 0x06, 0x00, 0x78, 0x00, 0x80, 0x07, 0x00, 0x18, 0x80, 0x07, 0x78, 0x00, 0x06, 0x00, 0x00, 0x00, // Code for char W
        0x09, 0x00, 0x00, 0x06, 0x18, 0x08, 0x04, 0x30, 0x03, 0xC0, 0x00, 0x30, 0x03, 0x08, 0x04, 0x06, 0x18, 0x00, 0x00,                                                                         // Code for char X
        0x0B, 0x00, 0x00, 0x02, 0x00, 0x04, 0x00, 0x18, 0x00, 0x60, 0x00, 0x80, 0x1F, 0x60, 0x00, 0x18, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00,                                                 // Code for char Y
        0x08, 0x02, 0x10, 0x02, 0x1C, 0x02, 0x13, 0xC2, 0x10, 0x32, 0x10, 0x0E, 0x10, 0x02, 0x10, 0x00, 0x00,                                                                                     // Code for char Z
        0x06, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x02, 0x80, 0x02, 0x80, 0x00, 0x00,                                                                                                             // Code for char [
        0x0A, 0x02, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x60, 0x00, 0x80, 0x01, 0x00, 0x06, 0x00, 0x08, 0x00, 0x30, 0x00, 0x40, 0x00, 0x00,                                                             // Code for char BackSlash
        0x05, 0x00, 0x00, 0x02, 0x80, 0x02, 0x80, 0xFE, 0xFF, 0x00, 0x00,                                                                                                                         // Code for char ]
        0x0B, 0x00, 0x00, 0x00, 0x02, 0x80, 0x01, 0x70, 0x00, 0x0C, 0x00, 0x02, 0x00, 0x0C, 0x00, 0x70, 0x00, 0x80, 0x01, 0x00, 0x02, 0x00, 0x00,                                                 // Code for char ^
        0x09, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00,                                                                         // Code for char _
        0x05, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00,                                                                                                                         // Code for char `
        0x0B, 0x00, 0x00, 0xC0, 0x07, 0x20, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x08, 0xF0, 0x1F, 0x00, 0x00,                                                 // Code for char a
        0x0B, 0x00, 0x00, 0xFE, 0x1F, 0x20, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x08, 0xC0, 0x07, 0x00, 0x00,                                                 // Code for char b
        0x0A, 0x00, 0x00, 0xC0, 0x07, 0x20, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x08, 0x40, 0x04, 0x00, 0x00,                                                             // Code for char c
        0x0B, 0x00, 0x00, 0xC0, 0x07, 0x20, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x08, 0xFE, 0x1F, 0x00, 0x00,                                                 // Code for char d
        0x0A, 0x00, 0x00, 0xC0, 0x07, 0x20, 0x09, 0x10, 0x11, 0x10, 0x11, 0x10, 0x11, 0x10, 0x11, 0x20, 0x09, 0xC0, 0x05, 0x00, 0x00,                                                             // Code for char e
        0x06, 0x00, 0x00, 0x10, 0x00, 0xFC, 0x1F, 0x12, 0x00, 0x12, 0x00, 0x00, 0x00,                                                                                                             // Code for char f
        0x0B, 0x00, 0x00, 0xC0, 0x27, 0x20, 0x48, 0x10, 0x90, 0x10, 0x90, 0x10, 0x90, 0x10, 0x90, 0x10, 0x90, 0x20, 0x48, 0xF0, 0x3F, 0x00, 0x00,                                                 // Code for char g
        0x0A, 0x00, 0x00, 0xFE, 0x1F, 0x20, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x20, 0x00, 0xC0, 0x1F, 0x00, 0x00,                                                             // Code for char h
        0x03, 0x00, 0x00, 0xF6, 0x1F, 0x00, 0x00,                                                                                                                                                 // Code for char i
        0x03, 0x00, 0x80, 0xF6, 0x7F, 0x00, 0x00,                                                                                                                                                 // Code for char j
        0x08, 0x00, 0x00, 0xFE, 0x1F, 0x00, 0x01, 0x80, 0x02, 0x40, 0x04, 0x20, 0x08, 0x10, 0x10, 0x00, 0x00,                                                                                     // Code for char k
        0x03, 0x00, 0x00, 0xFE, 0x1F, 0x00, 0x00,                                                                                                                                                 // Code for char l
        0x0F, 0x00, 0x00, 0xF0, 0x1F, 0x20, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x20, 0x00, 0xC0, 0x1F, 0x20, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x20, 0x00, 0xC0, 0x1F, 0x00, 0x00, // Code for char m
        0x0A, 0x00, 0x00, 0xF0, 0x1F, 0x20, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x20, 0x00, 0xC0, 0x1F, 0x00, 0x00,                                                             // Code for char n
        0x0A, 0x00, 0x00, 0xC0, 0x07, 0x20, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x08, 0xC0, 0x07, 0x00, 0x00,                                                             // Code for char o
        0x0B, 0x00, 0x00, 0xF0, 0xFF, 0x20, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x08, 0xC0, 0x07, 0x00, 0x00,                                                 // Code for char p
        0x0B, 0x00, 0x00, 0xC0, 0x07, 0x20, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x08, 0xF0, 0xFF, 0x00, 0x00,                                                 // Code for char q
        0x06, 0x00, 0x00, 0xF0, 0x1F, 0x20, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00,                                                                                                             // Code for char r
        0x06, 0x60, 0x08, 0x90, 0x10, 0x10, 0x11, 0x10, 0x11, 0x20, 0x0E, 0x00, 0x00,                                                                                                             // Code for char s
        0x07, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0xFE, 0x1F, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00,                                                                                                 // Code for char t
        0x0A, 0x00, 0x00, 0xF0, 0x07, 0x00, 0x08, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x08, 0xF0, 0x07, 0x00, 0x00,                                                             // Code for char u
        0x0A, 0x10, 0x00, 0x60, 0x00, 0x80, 0x03, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x0C, 0x80, 0x03, 0x60, 0x00, 0x10, 0x00, 0x00, 0x00,                                                             // Code for char v
        0x0E, 0x10, 0x00, 0xE0, 0x00, 0x00, 0x07, 0x00, 0x18, 0x00, 0x07, 0xE0, 0x00, 0x10, 0x00, 0xE0, 0x00, 0x00, 0x07, 0x00, 0x18, 0x00, 0x07, 0xE0, 0x00, 0x10, 0x00, 0x00, 0x00,             // Code for char w
        0x09, 0x10, 0x10, 0x20, 0x08, 0x40, 0x04, 0x80, 0x03, 0x80, 0x03, 0x40, 0x04, 0x20, 0x08, 0x10, 0x10, 0x00, 0x00,                                                                         // Code for char x
        0x09, 0x10, 0x00, 0xE0, 0x00, 0x00, 0x83, 0x00, 0x7C, 0x00, 0x0C, 0x00, 0x03, 0xE0, 0x00, 0x10, 0x00, 0x00, 0x00,                                                                         // Code for char y
        0x08, 0x10, 0x10, 0x10, 0x18, 0x10, 0x16, 0x10, 0x11, 0xD0, 0x10, 0x30, 0x10, 0x10, 0x10, 0x00, 0x00,                                                                                     // Code for char z
        0x07, 0x00, 0x00, 0x00, 0x01, 0x80, 0x02, 0xFC, 0x7E, 0x02, 0x80, 0x02, 0x80, 0x00, 0x00,                                                                                                 // Code for char {
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00,                                                                                                 // Code for char |
        0x06, 0x02, 0x80, 0x02, 0x80, 0xFC, 0x7E, 0x80, 0x02, 0x00, 0x01, 0x00, 0x00,                                                                                                             // Code for char }
        0x0A, 0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x40, 0x00, 0x00, 0x00,                                                             // Code for char ~
        0x05, 0xFF, 0x0F, 0x01, 0x08, 0x01, 0x08, 0xFF, 0x0F, 0x00, 0x00,                                                                                                                         // Code for char 
};

extern uint16_t global_bg_color;

void msDelay(uint8_t ms);
uint8_t sendSPI(uint8_t byte);

/**
 * This function will initialize the controller of the LC-Display
 */
void lcd_init(void);

/**
 * This function send data or register-information via SPI to the LC-Display
 * @param dc    0: Register-Information 1: Data-Information
 * @param value Value to send to the LCD-Controller
 */
void lcd_send(bool dc, uint8_t value);

/**
 * Set the cursor at position (x,y)
 * @param x X-Position [0..320]
 * @param y Y-Position [0..240]
 * @return
 */
uint8_t lcd_set_cursor(uint16_t x, uint16_t y);

/**
 * Set the cursor to the coordinate (x,_)
 * @param x
 * @return
 */
uint8_t lcd_set_cursor_x(uint16_t x);

/**
 * Set the cursor to the coordinate (_,y)
 * @param y
 * @return
 */
uint8_t lcd_set_cursor_y(uint16_t y);

/**
 * Draw a Pixel at the actual position
 * @param color The foreground color of the pixel
 * @return
 */
uint8_t lcd_draw_pixel(uint16_t color);

/**
 * This function fill the hole TFT with a user defined Color.
 * @param bg_color Backgroundcolor
 */
void lcd_fill(uint16_t bg_color);

/**
 * This function will draw a line from (x0,y0) to (x1,y1).
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param color Foreground color of the Pixel
 */
void lcd_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

/**
 * This function will draw a Pixel at (x,y)
 * @param x X-Coordinate
 * @param y Y-Coordinate
 * @param color Foreground color of the Pixel
 */
void lcd_draw_pixel_at(uint16_t x, uint16_t y, uint16_t color);

/**
 * This function will draw a filled rect from (x0,y0) to (x1,y1)
 * @param x0 Start-X-Coordinate
 * @param y0 Start-Y-Coordinate
 * @param x1 End-X-Coordinate
 * @param y1 End-Y-Coordinate
 * @param color Foregroundcolor of the rect
 */
void lcd_fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

/**
 * Draw a circle with the center at (xm,ym) and the radius (r)
 * @param xm
 * @param ym
 * @param r
 * @param color
 */
void lcd_draw_circle(uint16_t xm, uint16_t ym, uint16_t r, uint16_t color);

/**
 * Draw a filled circle with the center at (xm,ym) and the radius (r)
 * @param xm
 * @param ym
 * @param r
 * @param color
 */
void lcd_draw_filled_circle(uint16_t xm, uint16_t ym, uint8_t r, uint16_t color);

/**
 * This function will draw a chatacter at (x,y)
 * @param x X-Coordinate
 * @param y Y-Coordinate
 * @param c Character to draw
 * @param fIndex Index to the character (first entry is the width of the character)
 * @param fg_color Foregroundcolor
 * @param bg_color Backgroundcolor
 */
void lcd_draw_char(uint16_t x, uint16_t y, uint16_t fIndex, uint16_t fg_color, uint16_t bg_color);

/**
 * This function will draw a string at (x,y)
 * @param x X-Coordinate
 * @param y Y-Coordinate
 * @param pS Pointer to string
 * @param fg_color Foregroundcolor
 * @param bg_color Backgroundcolor
 */
void lcd_draw_string(uint16_t x, uint16_t y, const char *pS, uint16_t fg_color, uint16_t bg_color);

void setWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void lcd_draw_image(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t *Imagedata);

#endif /* LIB_ILI9341_H */
