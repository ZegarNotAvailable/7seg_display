/*
 * SEGMENTS.H
 *
 *  Created on: Nov 6, 2022
 *      Author: Zegar
 */

#ifndef SEGMENTS_H_
#define SEGMENTS_H_

//#define SEG7_DIGITS 8
//#define SEG7_X 0
//#define SEG7_Y 50
#define SEG7_DIGIT_WIDTH 40
#define SEG7_DIGIT_HIGH 50
#define SEG7_HIGH_SP 10
//#define SEG7_B_GROUND_COLOR ILI9341_NAVY
//#define SEG7_COLOR_OFF ILI9341_DARKGREY
//#define SEG7_COLOR_ON ILI9341_GREENYELLOW

// Struct for display
typedef struct
{
	uint8_t 	N_Digits; // Display size
	uint16_t	X_position; //
	uint16_t	Y_position; //
	uint16_t	B_Ground_Color; //
	uint16_t	Seg_ON_Color; //
	uint16_t	Seg_OFF_Color; //
	uint8_t 	SEG7_buf[8];

} T7Display; // Display_t

void DisplayInit(T7Display* Display, uint8_t N_Digits, uint16_t X_position, uint16_t Y_position,
		 uint16_t B_Ground_Color, uint16_t Seg_ON_Color, uint16_t Seg_OFF_Color);

void DisplaySetColor(T7Display* Display,  uint8_t Seg_ON_Color);

uint16_t DisplayGetColor(T7Display* Display);

void SEG7_write_display(T7Display* Display, uint8_t digit, uint8_t segments); //Write to buffer

void SEG7_draw_display(T7Display* Display);	//Send buffer to display

void SEG7_clr_display(T7Display* Display);	//

void SEG7_draw_digit (T7Display* Display, uint8_t digit);

void SEG7_draw_segment(T7Display* Display, uint8_t digit, uint8_t segment, uint16_t Color);

void SEG7_make_display (T7Display* Display);

void SEG7_print_display (T7Display* Display, uint8_t mesage);

void SEG7_HEX_display (T7Display* Display, uint16_t value);

#endif /* SEGMENTS_H_ */