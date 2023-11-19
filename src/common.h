#ifndef COMMON_H__
#define COMMON_H__
//  ./ 当前目录    ../上一个   ../../再上一个
#include "../include/raylib.h"
#include "../include/raymath.h"
#include "Ease.h"
#define byte unsigned char
#define string const char *
#define rockcount 10
#define WIDTH 500 // 定义一个常量
#define HEIGHT 500
#define ROCKTEMPLATECOUNT 3
const int HOOK_STATUS_WAVE = 0;
const int HOOK_STATUS_MOVE = 1;
const int HOOK_STATUS_HOOK = 2;
const int HOOK_STATUS_LOST = 3;

Vector2 Vector2New(float x, float y) {

    return (Vector2){.x = x, .y = y};
}

float Absolute(float input) {
    if (input >= 0) {
        return input;
    } else {
        return -input;
    }
}
Vector2 AbsoluteVector2(Vector2 inputvector2) {
    inputvector2.x = Absolute(inputvector2.x);
    inputvector2.y = Absolute(inputvector2.y);
    return inputvector2;
}

Vector2 Vector2Max(Vector2 a, Vector2 b) {
    Vector2 res = a;
    if (a.x < b.x) {
        res.x = b.x;
    } else {
        res.x = a.x;
    }
    if (a.y < b.y) {
        res.y = b.y;
    } else {
        res.y = a.y;
    }
    return res;
}

// [min, max)  随机数在[min,max)的范围里
int get_rand(int min, int max) {
    int a;
    a = min + rand() % max;
    return a;
}

// 两个圆碰到一起

bool IsCirlceInsideCircle(float hookr, float rockr, Vector2 hooky, Vector2 rocky) {
    Vector2 diff = Vector2Subtract(hooky, rocky);
    float lengthsqr = Vector2LengthSqr(diff);
    if (lengthsqr >= (hookr + rockr) * (hookr + rockr)) {
        return false;
    } else {
        return true;
    }
}

bool IsCircleinsideRect(Vector2 rectpos, Vector2 rectsize, Vector2 circlepos, float circleradius) {
    Vector2 recthalf = Vector2Scale(rectsize, 0.5f);
    Vector2 rectCenter = Vector2Add(rectpos, recthalf);
    // rect 基于 Circle 的中心坐标
    rectCenter = Vector2Subtract(rectCenter, circlepos); // x4 y4
    // rect 中心 变到第一象限
    rectCenter = AbsoluteVector2(rectCenter);
    // rect half
    // rect min
    Vector2 rectdown = Vector2Subtract(rectCenter, recthalf); // x2 y2
    rectdown = Vector2Max(rectdown, Vector2Zero());

    // rect min - circle center
    float rectToCircleLenSqr = Vector2LengthSqr(rectdown);
    float radiusSqr = circleradius * circleradius;
    if (rectToCircleLenSqr < radiusSqr) {
        return true;
    } else {
        return false;
    }
}

bool IsRectInsideRect(Vector2 rolepos, Vector2 rectpos, Vector2 rolesize, Vector2 rectsize) {

    if (rolepos.x + rolesize.x >= rectpos.x && rolepos.y + rolesize.x >= rectpos.y &&
        rolepos.x <= rectpos.x + rectsize.x && rolepos.y <= rectpos.y + rectsize.y) {
        return true;
    } else {
        return false;
    }
}

bool IsRectInsideRectR(Rectangle a, Rectangle b) {
    return IsRectInsideRect(Vector2New(a.x, a.y), Vector2New(b.x, b.y), Vector2New(a.width, a.height),
                            Vector2New(b.width, b.height));
}

// 在半圆里移动    //记笔记
Vector2 GetOnCirlce(Vector2 pos, float angle, float radius) {
    angle = angle * DEG2RAD;
    Vector2 result;
    result.x = radius * cosf(angle);
    result.y = radius * sinf(angle);
    return Vector2Add(result, pos);
}

void Text_Float(float b, int x, int y, int size) {
    const char *a = TextFormat("%f", b);
    DrawText(a, x, y, size, YELLOW);
}
void Text_Int(int b, int x, int y, int size, Color color) {
    const char *a = TextFormat("%d", b);
    DrawText(a, x, y, size, color);
}

float GetHeavyRate(float heavy) {
    return -0.175f * heavy + 5.75f;
}

void Line_rotate(float *linetime, float dt) {
    float angle;
    Vector2 startpos;
    startpos.x = 450;
    startpos.y = 200;
    Vector2 endpos;
    Vector2 endposdown;
    Vector2 linesize;
    linesize.x = 115;
    linesize.y = 7;
    *linetime += dt;

    // printf("%f\r\n",*linetime);

    angle = CycleSinAbsSine(*linetime, 1, 0, 360);
    // printf("%f\r\n",angle);
    endpos = GetOnCirlce(startpos, angle, 100);
    endposdown = GetOnCirlce(startpos, angle, 50);
    // printf("%f\r\n",endpos.x);
    DrawLine(startpos.x, startpos.y, endpos.x, endpos.y, RED);
    DrawLine(startpos.x, startpos.y, endpos.x, endpos.y, BLACK);
}

void Line_rect(Vector2 pos, Vector2 size, float angle) {
    float x = pos.x;
    float y = pos.y;
    float w = size.x;
    float h = size.y;

    Vector2 lt = pos;

    pos.x = pos.x + w;
    Vector2 rt = pos;
    rt = GetOnCirlce(lt, angle, w);

    pos.y = pos.y + h;
    Vector2 rb = pos;
    float oldangle = Vector2Angle(lt, rb)*RAD2DEG;
    rb = GetOnCirlce(lt, oldangle+angle, Vector2Distance(lt, rb));

    pos.x = x;
    Vector2 lb = pos;

    lb = GetOnCirlce(lt, 90+angle, h);

    DrawLineV(lt, rt, RED);
    DrawLineV(rt, rb, BLACK);
    DrawLineV(rb, lb, GRAY);
    DrawLineV(lb, lt, GREEN);
}

#endif