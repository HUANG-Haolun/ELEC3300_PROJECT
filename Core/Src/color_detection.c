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

// rgb to hsv
void rgb2hsv(uint16_t rgb, float *h, float *s, float *v)
{
	uint16_t r = (rgb >> 11) & 0x1f;
	uint16_t g = (rgb >> 5) & 0x3f;
	uint16_t b = rgb & 0x1f;
	float max = r > g ? r : g;
	max = max > b ? max : b;
	float min = r < g ? r : g;
	min = min < b ? min : b;
	*v = max;
	if (max == 0)
	{
		*s = 0;
		*h = 0;
		return;
	}
	*s = 255 * (max - min) / max;
	if (r == max)
	{
		*h = 0 + 43 * (g - b) / (max - min);
	}
	else if (g == max)
	{
		*h = 85 + 43 * (b - r) / (max - min);
	}
	else
	{
		*h = 171 + 43 * (r - g) / (max - min);
	}
}

void KNearest_match(uint16_t square_colors[9], uint16_t real_colors[9], uint8_t times, char *face, uint8_t bt_flags)
{
	float h = 0;
	float s = 0;
	float v = 0;
	for (int i = 0; i < 9; i++)
	{
		uint16_t temp = square_colors[i];
		rgb2hsv(square_colors[i], &h, &s, &v);
		uint8_t index = 0;
		// red
		if (s < 185 && h > 80)
			index = 4;
		else if (h < 25 || h > 336)
			index = 1;
		else if (h < 55)
			index = 2;
		else if (h < 85)
			index = 3;
		else if (h < 110)
			index = 0;
		else if (h < 200)
			index = 5;

		real_colors[i] = true_colors[index];
		if (bt_flags == 1)
		{
			if (times > 3 && i > 2)
				break;
			face[detection_order[times * 9 + i]] = face_colors[index];
		}
	}
}

// KNN match
// void KNearest_match(uint16_t square_colors[9], uint16_t real_colors[9], uint8_t times, char *face, uint8_t bt_flags)
// {

// 	for (int i = 0; i < 9; i++)
// 	{
// 		int8_t temp[3];
// 		float h = 0;
// 		float s = 0;
// 		float v = 0;
// 		temp[0] = square_colors[i] & 0x1F;
// 		temp[1] = (square_colors[i] >> 5) & 0x3F;
// 		temp[2] = (square_colors[i] >> 11) & 0x1F;
// 		//CHANGE RGB to HSV

// 		uint16_t min_dist = 0xFFFF;
// 		int min_index = -1;
// 		for (size_t i = 0; i < 6; i++)
// 		{
// 			int8_t temp2[3];
// 			temp2[0] = true_colors[i] & 0x1F;
// 			temp2[1] = (true_colors[i] >> 5) & 0x3F;
// 			temp2[2] = (true_colors[i] >> 11) & 0x1F;
// 			uint16_t dist = sqrt(pow(temp[0] - temp2[0], 2) + pow(temp[1] - temp2[1], 2) + pow(temp[2] - temp2[2], 2));
// 			if (dist < min_dist)
// 			{
// 				min_dist = dist;
// 				min_index = i;
// 			}
// 		}
// 		real_colors[i] = true_colors[min_index];
// 		if (bt_flags == 1)
// 		{
// 			if (times > 3 && i > 2)
// 				break;
// 			face[detection_order[times * 9 + i]] = face_colors[min_index];
// 		}
// 	}
// }
