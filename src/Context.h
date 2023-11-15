#ifndef CONTEXT_H__
#define CONTEXT_H__
#include "RockEntity.h"
#include "HookEntity.h"
#include "common.h"

typedef struct Context {

    Rock arrrock[rockcount]; // 数组存rockcount个的圆
    Rock rocktemplates[3];   // 数组 存三种类型的圆
    int rockindex;
    int lastrockindex;

    Hook hook;
    Vector2 hookstart;
    float hookspeed; // 速度
    float hookradius;
    int status;  // 状态   //状态这样使不同的状态可以转变
    int hookdir; ///////////////////////????????????

    Vector2 manpos;
    int mansize; // 因为是一个正方形

    float time;
    int score;
} Context;

#endif