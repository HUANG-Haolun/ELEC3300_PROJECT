#include <stdio.h>
#include <math.h>
float max(float a, float b, float c)
{
    return ((a > b) ? (a > c ? a : c) : (b > c ? b : c));
}
float min(float a, float b, float c)
{
    return ((a < b) ? (a < c ? a : c) : (b < c ? b : c));
}
int rgb_to_hsv(float r, float g, float b)
{
    // R, G, B values are divided by 255
    // to change the range from 0..255 to 0..1:
    float h, s, v;
    r /= 255.0;
    g /= 255.0;
    b /= 255.0;
    float cmax = max(r, g, b); // maximum of r, g, b
    float cmin = min(r, g, b); // minimum of r, g, b
    float diff = cmax - cmin;  // diff of cmax and cmin.
    if (cmax == cmin)
        h = 0;
    else if (cmax == r)
        h = fmod((60 * ((g - b) / diff) + 360), 360.0);
    else if (cmax == g)
        h = fmod((60 * ((b - r) / diff) + 120), 360.0);
    else if (cmax == b)
        h = fmod((60 * ((r - g) / diff) + 240), 360.0);
    // if cmax equal zero
    if (cmax == 0)
        s = 0;
    else
        s = (diff / cmax) * 100;
    // compute v
    v = cmax * 100;
    printf("h s v=(%f, %f, %f)\n", h, s, v);
    return 0;
}
// main function
int main(int argc, char const *argv[])
{
    int r = 0, g = 255, b = 0;
    rgb_to_hsv(r, g, b);
    return 0;
}