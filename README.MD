# 7-SEGMENT display on TFT (ILI9341) for STM32F411RE (Nucleo).
You can simple create displays one to eight digits wide.
Dimensions of single digit are fixed.
You can change colors of background (body) and segments ON and OFF.
Segments are always visible when Seg_OFF_Color is different of B_Ground_Color.
[video](https://youtu.be/zLBH-P7QVNw)
## Create display.
```
  T7Display LED8;
  DisplayInit(&LED8, 8, 14, 0, 50, ILI9341_BLACK, ILI9341_GREEN, GRAPHITE);
  T7Display LED4;
  DisplayInit(&LED4, 4, 7, 80, 150, ILI9341_NAVY, ILI9341_YELLOW, GRAPHITE);
```

Creates two displays with different colors.
## Using.
### Message.
```
uint8_t i;
uint8_t mesage[] =
	{ 0x75, 0x1c, 0x50, 0x6d, 0x00, 0x6d, 0x31, 0x37 };

for (i = 0; i < 8; i++)
	{
	  uint8_t segments = mesage[i];
	  uint8_t digit = i;
	  SEG7_write_display (&LED8, digit, segments);
	}
SEG7_draw_display (&LED8);
```
You can print a string:
```
      char message[] =
	  {"Kurs STM."};
      SEG7_print_ASCII(&LED8, 0, message);
```	
  
### Print predefined mesages and uint16_t values.
```
for (i = 4; i < 19; i++)
	{
	  DisplaySetColor(&LED8, i);
	  SEG7_print_display(&LED8, i);
	  SEG7_draw_display (&LED8);

	  SEG7_HEX_display(&LED4,DisplayGetColor(&LED8));
    }
DisplaySetColor(&LED8, 14);
```
