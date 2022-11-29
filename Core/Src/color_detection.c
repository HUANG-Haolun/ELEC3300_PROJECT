/**
 * @file color_detection.c
 * @author HUANG Haolun (mihawkhhuang@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "color_detection.h"

uint16_t temp_index[9];
// uint16_t detection_colors[6] = {0x31be, 0xdA03, 0x2d63, 0xdc63, 0xfdee, 0x0000};
uint16_t detection_colors[6] = {GREEN, RED, ORANGE, YELLOW, WHITE, BLUE};
uint16_t true_colors[6] = {GREEN, RED, ORANGE, YELLOW, WHITE, BLUE};
char face_colors[6] = {'F', 'L', 'R', 'U', 'D', 'B'};
uint8_t face_order[6] = {2, 0, 5, 3, 1, 4};
uint8_t detection_order[] = {18, 19, 20, 21, 22, 23, 24, 25, 26,
							   27, 28, 29, 30, 31, 32, 33, 34, 35,
							   53, 52, 51, 50, 49, 48, 47, 46, 45,
							   0, 1, 2, 3, 4, 5, 6, 7, 8,
							   11, 14, 17, 0, 0, 0, 0, 0, 0,
							   9, 10, 11, 0, 0, 0, 0, 0, 0,
							   15, 12, 9, 0, 0, 0, 0, 0, 0,
							   17, 16, 15, 0, 0, 0, 0, 0, 0,
							   42, 39, 36, 0, 0, 0, 0, 0, 0,
							   36, 37, 38, 0, 0, 0, 0, 0, 0,
							   38, 41, 44, 0, 0, 0, 0, 0, 0,
							   44, 43, 42, 0, 0, 0, 0, 0, 0};
uint16_t midterm_order[12] = {BLUE, RED, GREEN, ORANGE, WHITE, BLACK, BLUE, RED, GREEN, ORANGE, WHITE, BLACK};

float max(float a, float b, float c)
{
	return ((a > b) ? (a > c ? a : c) : (b > c ? b : c));
}
float min(float a, float b, float c)
{
	return ((a < b) ? (a < c ? a : c) : (b < c ? b : c));
}
int rgb_to_hsv(float r, float g, float b, float *h, float *s, float *v)
{
	// R, G, B values are divided by 255
	// to change the range from 0..255 to 0..1:
	r /= 31;
	g /= 63;
	b /= 31;
	float cmax = max(r, g, b); // maximum of r, g, b
	float cmin = min(r, g, b); // minimum of r, g, b
	float diff = cmax - cmin;  // diff of cmax and cmin.
	if (cmax == cmin)
		*h = 0;
	else if (cmax == r)
		*h = fmod((60 * ((g - b) / diff) + 360), 360.0);
	else if (cmax == g)
		*h = fmod((60 * ((b - r) / diff) + 120), 360.0);
	else if (cmax == b)
		*h = fmod((60 * ((r - g) / diff) + 240), 360.0);
	// if cmax equal zero
	if (cmax == 0)
		*s = 0;
	else
		*s = (diff / cmax) * 100;
	// compute v
	*v = cmax * 100;
	return 0;
}

// KNN match
void KNearest_match(uint16_t square_colors[9], uint16_t real_colors[9], uint8_t times, char *face, uint8_t bt_flags)
{
	// int8_t midColor[3];
	// midColor[0] = midterm_order[0] & 0x1F;
	// midColor[1] = (midterm_order[0] >> 5) & 0x3F;
	// midColor[2] = (midterm_order[0] >> 11) & 0x1F;
	// int8_t midCube[3];
	// midCube[0] = square_colors[4] & 0x1F;
	// midCube[1] = (square_colors[4] >> 5) & 0x3F;
	// midCube[2] = (square_colors[4] >> 11) & 0x1F;
	// int8_t diffR = midCube[0] - midColor[0];
	// int8_t diffG = midCube[1] - midColor[1];
	// int8_t diffB = midCube[2] - midColor[2];
	for (int i = 0; i < 9; i++)
	{
		int8_t temp[3];
		float h = 0;
		float s = 0;
		float v = 0;
		temp[0] = square_colors[i] & 0x1F;
		temp[1] = (square_colors[i] >> 5) & 0x3F;
		temp[2] = (square_colors[i] >> 11) & 0x1F;
		// rgb_to_hsv(temp[0], temp[1], temp[2], &h, &s, &v);
		uint16_t min_dist = 0xFFFF;
		int min_index = -1;
		for (size_t i = 0; i < 6; i++)
		{
			int8_t temp2[3];
			temp2[0] = true_colors[i] & 0x1F;
			temp2[1] = (true_colors[i] >> 5) & 0x3F;
			temp2[2] = (true_colors[i] >> 11) & 0x1F;
			uint16_t dist = sqrt(pow(temp[0] - temp2[0], 2) + pow(temp[1] - temp2[1], 2) + pow(temp[2] - temp2[2], 2));
			if (dist < min_dist)
			{
				min_dist = dist;
				min_index = i;
			}
		}
		real_colors[i] = true_colors[min_index];
		if (bt_flags == 1)
		{
			if (times > 3 && i > 2)
				break;
			face[detection_order[times * 9 + i]] = face_colors[min_index];
		}
	}
}
