#ifndef EASE_H__
#define EASE_H__
#include "math.h"
#define PI 3.14159265358979323846f



float InSine(float t) {
    return sinf((t*PI)/2);
}

float EaseInSine(float time, float duration, float startValue, float endValue) {
    float t = time / duration;
    float percent = InSine(t);
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


float CycleSinAbs(float time,float cycle){
    return fabs(sinf(cycle*time*(PI/2)));
}

float CycleSinAbsSine(float time ,float cycle, float startValue, float endValue){

    float percent = CycleSinAbs(time,cycle);/// 0   --  100%

    return percent *(endValue-startValue);
}



#endif