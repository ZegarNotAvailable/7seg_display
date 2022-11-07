/*
 * SEGMENTS.C
 *
 *  Created on: Nov 6, 2022
 *      Author: Zegar
 */

#include "main.h"
#include "TFT_ILI9341.h"
#include "GFX_Color.h"
#include <SEGMENTS.h>

//uint8_t SEG7_buf[] =
//  { 0, 0, 0, 0, 0, 0, 0, 0 };

const uint16_t Colors[] =
  {
  ILI9341_BLACK,
  ILI9341_LIGHTGREY,
  ILI9341_DARKGREY,
  ILI9341_NAVY,
  ILI9341_DARKGREEN,
  ILI9341_DARKCYAN,
  ILI9341_MAROON,
  ILI9341_PURPLE,
  ILI9341_OLIVE,
  ILI9341_BLUE,
  ILI9341_GREEN,
  ILI9341_CYAN,
  ILI9341_RED,
  ILI9341_MAGENTA,
  ILI9341_YELLOW,
  ILI9341_WHITE,
  ILI9341_ORANGE,
  ILI9341_GREENYELLOW,
  ILI9341_PINK };

const char ColorsNames[][9] =
  { "BLACK   ", "LGHTGREY", "DARKGREY", "NAVY    ", "DRKGREEN", "DARKCYAN", "MAROON  ",
    "PURPLE  ", "OLIVE   ", "BLUE    ", "GREEN   ", "CYAN    ", "RED     ", "MAGENTA ",
    "YELLOW  ", "WHITE   ", "ORANGE  ", "GRYELLOW", "PINK    " };

const uint8_t HEX7SEG[]=
    {
	0x3F,0x06,0x5B,0x4F, //0,1,2,3
	0x66,0x6D,0x7D,0x07, //4,5,6,7
	0x7F,0x6F,0x77,0x7C, //8,9,A,B
	0x39,0x5E,0x79,0x71, //C,D,E,F
    };

const uint8_t CHR7SEG[]=
    {
	0x77,0x7C,0x39,0x5E, //A,B,C,D
	0x79,0x71,0x3D,0x76, //E,F,G,H
	0x04,0x1F,0x75,0x38, //I,J,K,L
	0x37,0x54,0x5C,0x73, //M,N,O,P
	0x67,0x50,0x6D,0x31, //Q,R,S,T
	0x1C,0x3E,0x7E,0x6B, //U,V,W,X
	0x72,0x3B	     //Y,Z
    };


// Display Init
void DisplayInit(T7Display* Display, uint8_t N_Digits, uint16_t X_position, uint16_t Y_position,
		 uint16_t B_Ground_Color, uint16_t Seg_ON_Color, uint16_t Seg_OFF_Color)

{
	Display->N_Digits = N_Digits; // Set initial size of display
	Display->X_position = X_position;
	Display->Y_position = Y_position;
	Display->B_Ground_Color = B_Ground_Color; //
	Display->Seg_ON_Color = Seg_ON_Color; //
	Display->Seg_OFF_Color = Seg_OFF_Color; //
	//Display->SEG7_buf[N_Digits];	// =	{ 0, 0, 0, 0, 0, 0, 0, 0 }; //Buffer
	SEG7_make_display(Display);
}

void DisplaySetColor(T7Display* Display,  uint8_t Seg_ON_Color)
{
  Display->Seg_ON_Color = Colors[Seg_ON_Color]; //
}

uint16_t DisplayGetColor(T7Display* Display)
{
  return Display->Seg_ON_Color;
}

const uint8_t SEG7_segments[8][25] =
      {
	    { 0x7f, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xff,
		0x00, 0x3f, 0xff, 0xfe, 0x00 },	//segment A
	    { 0x08, 0x1c, 0x3c, 0x3c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x78,
		0x78, 0x78, 0x78, 0x78, 0x78, 0xf8, 0xf8, 0xf8, 0x78, 0x38, 0x10 },//segment B
	    { 0x0c, 0x1c, 0x3c, 0x3c, 0x7c, 0x7c, 0x7c, 0x7c, 0x78, 0x78, 0x78,
		0x78, 0x78, 0xf8, 0xf8, 0xf8, 0x78, 0x30 },	//segment C
	    { 0x3f, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff,
		0x80, 0x7f, 0xff, 0xff, 0x00 },	//segment D
	    { 0x20, 0x30, 0x38, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x78, 0x78, 0x78,
		0x78, 0x78, 0x78, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0, 0x40 },//segment E
	    { 0x30, 0x78, 0x7c, 0x7c, 0x7c, 0x7c, 0x78, 0x78, 0x78, 0x78, 0x78,
		0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0, 0x80 },//segment F
	    { 0x3f, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff,
		0xfe },				//segment G
	    { 0x70, 0xf8, 0xfc, 0xfc, 0xf8, 0x78 }		//segment DOT
      };

const uint8_t SEG7_param[8][5] =
  {	//dx, dy, seg_w, seg_h
	  { 6, 0, 25, 4 },	//segment A
	  { 27, 2, 6, 22 },	//segment B
	  { 25, 25, 6, 20 },	//segment C
	  { 2, 44, 25, 4 },	//segment D
	  { 0, 24, 6, 22 },	//segment E
	  { 2, 3, 6, 21 },	//segment F
	  { 4, 22, 24, 4 },	//segment G
	  { 32, 42, 6, 6 }	//segment DOT
    };

void SEG7_print_display (T7Display* Display, uint8_t mesage)
{
  uint8_t i;
  uint8_t segments;
  char CHR;
    for (i = 0; i < Display->N_Digits; i++)
      {
        CHR = ColorsNames[mesage][i];
	if (CHR > 'Z')
          {
            CHR -= 0x20;
          }
	if (CHR > '/' && CHR < ':')
          {
            segments = HEX7SEG[CHR-'0'];
          }
	else if (CHR > '@' && CHR < '[')
	  {
	    segments = CHR7SEG[CHR-'A'];
	  }
	else segments = 0;
	Display->SEG7_buf[i] = segments;
      }

}

void SEG7_HEX_display (T7Display* Display, uint16_t value)
{
  uint8_t i;
  uint8_t segments;
  uint8_t HEX;
  for (i = 0; i < Display->N_Digits; i++)
    {
      HEX = (value >> 4 * i) & 0x0f;
      segments = HEX7SEG[HEX];
      Display->SEG7_buf[Display->N_Digits -1 - i] = segments;
    }
  SEG7_draw_display (Display);
}

void SEG7_write_display(T7Display* Display, uint8_t digit, uint8_t segments)
{
  Display->SEG7_buf[digit] = segments;	//DOT,G,F,E,D,C,B,A
}

void SEG7_draw_display (T7Display* Display)
{
  uint8_t digit;
  for (digit = 0; digit < Display->N_Digits; digit++)
    {
      SEG7_draw_digit(Display, digit);
    }
}

void SEG7_make_display (T7Display* Display)
{
  GFX_DrawFillRectangle (Display->Y_position, Display->X_position, (SEG7_DIGIT_HIGH + 2 * SEG7_HIGH_SP),
			 (Display->N_Digits * SEG7_DIGIT_WIDTH), Display->B_Ground_Color);
  uint8_t i, j;
  for (i = 0; i < Display->N_Digits; i++)
    {
      for (j = 0; j < 8; j++)		// All segments on all digits
	{
	  SEG7_draw_segment (Display, i, j, Display->Seg_OFF_Color);
	}
    }

}

void SEG7_clr_display(T7Display* Display)
{
  uint8_t i;
  for (i = 0; i < Display->N_Digits; i++)
    {
      Display->SEG7_buf[i] = 0;
    }
  SEG7_draw_display(Display);
}

void SEG7_draw_digit (T7Display* Display, uint8_t digit)
{
  uint8_t digit_to_draw = Display->SEG7_buf[digit];
//  uint8_t segment_to_draw;
  uint8_t i;
  for (i = 0; i < 8; i++)
    {
      if (digit_to_draw & 1 << i)
	{
	  SEG7_draw_segment (Display, digit, i, Display->Seg_ON_Color);
	}
      else
	{
	  SEG7_draw_segment (Display, digit, i, Display->Seg_OFF_Color);
	}
    }
}

void SEG7_draw_segment (T7Display* Display, uint8_t digit, uint8_t segment, uint16_t Color)
{
  if ((digit >= Display->N_Digits) || (segment >= 8))
    {
      return;
    }
  HAL_Delay(20);		// For tests only !!!!!!!!!!!!!!!!!!!!!!!
  uint16_t PixelHeight;
  uint8_t WidthLoops, CharBits, CharBitsLeft;

  uint8_t CharPointer = 0;

  // 1st iteration - for each Row by Height
  for (PixelHeight = 0; PixelHeight < SEG7_param[segment][3]; PixelHeight++)
    {
      // Check how many bits left to draw in current Row
      CharBitsLeft = SEG7_param[segment][2];

      // 2nd Iterator - For each byte in that Row
      for (WidthLoops = 0; WidthLoops <= (SEG7_param[segment][2] -1) / 8;
	  WidthLoops++)
	{
	  // Take one line
	  uint8_t line = SEG7_segments[segment][CharPointer];
	  // Define how many bit to draw - full byte or less
	  if (CharBitsLeft >= 8)
	    {
	      CharBits = 8; // Full byte
	      CharBitsLeft -= 8; // Decrease bits left counter
	    }
	  else
	    {
	      // If less than byte - only few bits
	      CharBits = CharBitsLeft;
	    }

	  // 3rd Iterator - for each bit in current byte in current row ;)
	  for (uint8_t i = 0; i < CharBits; i++, line <<= 1)
	    {
	      // Check bit first from left
	      if (line & 0x80)
		{
		  // If pixel exists - draw it
		  GFX_DrawPixel(
		      Display->Y_position + SEG7_HIGH_SP + SEG7_param[segment][1] + PixelHeight,
		      (319 - (Display->X_position + (SEG7_DIGIT_WIDTH * digit) + SEG7_param[segment][0] + (WidthLoops*8) + i)),
		      Color);
		}
	    }

	  // Take next byte in current char bitmap
	  CharPointer++;
	}
    }
  // Return char width for String function
//  return CurrentFont->CharDescription[CharNumber].CharWidth;

}

