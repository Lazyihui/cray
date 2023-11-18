#ifndef EASE_H__
#define EASE_H__
#include "math.h"
#define PI 3.14159265358979323846f



float EaseOutSine(float t) {
    return sinf((t*PI)/2);
}

float EaseInSine(float time, float duration, float startValue, float endValue) {
    float t = time / duration;
    float percent = EaseOutSine(t);
    return percent * (endValue - startValue);
}


float EaseOutQuart(float t) {
    return 1 - powf(1 - t, 4);
}

float Ease(float time, float duration, float startValue, float endValue) {
    float t = time / duration;
    float percent = EaseOutQuart(t);
    return percent * (endValue - startValue);
}







#endif