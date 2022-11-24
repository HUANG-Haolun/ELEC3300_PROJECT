#include "bsp_ov7725.h"
#include "bsp_sccb.h"
#include "lcd.h"
#include "stdarg.h"
#include "math.h"
void KNearest_match(uint16_t square_colors[9],uint16_t real_colors[9], uint8_t times, char *face);