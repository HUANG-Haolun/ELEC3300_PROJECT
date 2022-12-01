#include <stdio.h>
#include <math.h>
#include <stdint.h>
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
// main function
int main(int argc, char const *argv[])
{
    float h = 0;
    float s = 0;
    float v = 0;
    rgb2hsv(0x7e0, &h, &s, &v);
    printf("h = %f, s = %f, v = %f", h, s, v);
    return 0;
}