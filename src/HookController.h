#ifndef HOOKCONTROLLER_H__
#define HOOKCONTROLLER_H__
#include "HookEntity.h"
#include "RockEntity.h"
#include "Context.h"
#include "Ease.h"

void ContextInit(Context *context) {
    //////////////////////////////////////////////////////////////////////////////////////////////////赋值都在这里
    for (int i = 0; i < rockcount; i++) {
        context->arrrock[i] = (Rock){0};
    }
    context->lastrockindex = rockcount - 1;

    Rock rockmin = {.color = YELLOW, .heavy = 10, .pos = {.x = 0, .y = 0}, .radius = 10, .gold = 50};
    Rock rockmid = {.color = YELLOW, .heavy = 20, .pos = {.x = 0, .y = 0}, .radius = 20, .gold = 250};
    Rock rockmax = {.color = YELLOW, .heavy = 30, .pos = {.x = 0, .y = 0}, .radius = 30, .gold = 500};
    context->rocktemplates[0] = rockmin;
    context->rocktemplates[1] = rockmid;
    context->rocktemplates[2] = rockmax;

    context->manpos.x = 380;
    context->manpos.y = 81;
    context->mansize = 40;

    Vector2 hookstart;
    hookstart.x = context->manpos.x + (context->mansize / 2);
    hookstart.y = context->manpos.y + context->mansize;
    context->hookstart = hookstart;
    context->hook = (Hook){.color = BROWN, .speed = 30, .radius = 5, .pos = {.x = 360, .y = 122}};
    context->hookdir = 1;
    context->hookradius = 60;
    context->status = 0;
    context->hookspeed = 120;
    context->hookwavetime = 0;
    context->hookwaveduration = 3;
    context->hookcycle = 1;
    context->hookwavesintime = 0;

    context->score = 0;
    context->time = 60;
}

// void Change(int *value) {
//     *value = 5;
// }//////////////////////////

void HookState_Wave(Context *ctx, float dt) {
    int status = ctx->status;
    if (status != HOOK_STATUS_WAVE) {
        return;
    }
    float hookradius = ctx->hookradius;
    Vector2 manpos = ctx->manpos;
    int mansize = ctx->mansize;
    Hook hook = ctx->hook;
    float hookdir = ctx->hookdir;
    float hookspeed = ctx->hookspeed;

    ctx->hookwavesintime += 1 * dt;
    printf("%f", ctx->hookwavesintime);
    hook.angle = CycleSinAbsSine(ctx->hookwavesintime, ctx->hookcycle, 0, 180);
    // printf("%f",hook.angle);

    // if (hookdir == 1) {
    //     hook.angle = CycleSinAbsSine(ctx->hookwavesintime, ctx->hookcycle, 1, -1);

    // } // 角度的变化   int hookdir = 1;

    // if (hookdir == -1) {
    //     hook.angle =180 - CycleSinAbsSine(ctx->hookwavesintime, ctx->hookcycle, 1, -1);
    // } // 角度的变化   int hookdir = 1;

    ctx->hookstart.x = manpos.x + (mansize / 2);
    ctx->hookstart.y = manpos.y + mansize; // 得到老头中心点下面的位置（钩子中的位置）

    // if (ctx->hookwavetime >= ctx->hookwaveduration) {
    //     hookdir =hookdir * -1; // bi表示方向
    //     // ctx->hookwavetime=0;
    //     printf("%f",hookdir);
    // } // 钩子在0-180内左右摆动
    // ctx->hookwavetime += dt;

    ////////////////////////钩子伸长

    // 角度不变 半径变长
    if (IsKeyPressed(KEY_SPACE)) {
        status = 1;
    }

    hook.pos = GetOnCirlce(ctx->hookstart, hook.angle, hookradius);
    ctx->status = status;
    ctx->hookradius = hookradius;
    ctx->hook = hook;
    ctx->hookdir = hookdir;
    ctx->hookspeed = hookspeed;
    ctx->hook = hook;
}

void HookState_Move(Context *ctx, float dt) {
    int status = ctx->status;
    if (status != HOOK_STATUS_MOVE) {
        return;
    }

    float hookradius = ctx->hookradius;
    Hook hook = ctx->hook;

    hookradius += dt * ctx->hookspeed; // hookspeed = 100;
    hook.pos = GetOnCirlce(ctx->hookstart, hook.angle, hookradius);

    // 检测 遍历所有数组
    for (int i = 0; i < rockcount; i++) {
        Rock rock = ctx->arrrock[i];
        bool isintersect = IsCirlceInsideCircle(hook.radius, rock.radius, hook.pos, rock.pos);
        if (isintersect) {
            
            ctx->rockindex = i;        // 存

            status = HOOK_STATUS_HOOK; // 勾到

            break;
        }
    }
    if (hook.pos.x > 800 || hook.pos.x < 0 || hook.pos.y > 450) {
        status = HOOK_STATUS_LOST;
    }
    ctx->status = status;
    ctx->hookradius = hookradius;
    ctx->hook = hook;
}

void HookState_Hook(Context *ctx, float dt) {
    int status = ctx->status;
    if (status != HOOK_STATUS_HOOK) {
        return;
    }

    Rock *arrrock = ctx->arrrock;
    int rockindex = ctx->rockindex;
    float hookradius = ctx->hookradius;
    int lastrockindex = ctx->lastrockindex;
    Hook hook = ctx->hook;

    Rock *rock = &arrrock[rockindex]; // 指针指向地址 *  指  &//////////!!!!/

    /////////////////////////////不同重量金块不同速度
    float rate = GetHeavyRate(rock->heavy);
    hookradius -= dt * ctx->hookspeed * rate;
    // hookradius=Clamp(hookradius,0,hookradius);//取
    hookradius = fmax(0, hookradius); // 0和r的最大值
    hook.pos = GetOnCirlce(ctx->hookstart, hook.angle, hookradius);
    rock->pos = hook.pos; // 1/60 fps
    Rock_Gold(*rock);

    if (hookradius == 0) {
        ctx->score += rock->gold;
        Rock a = arrrock[lastrockindex]; // rockindex是抓到的金块
        arrrock[lastrockindex] = arrrock[rockindex];
        arrrock[rockindex] = a;
        lastrockindex--;
    }

    if (hookradius <= 0) {
        status = HOOK_STATUS_WAVE;
        hookradius = 60;
    }

    ctx->status = status;
    ctx->hookradius = hookradius;
    ctx->hook = hook;
    ctx->lastrockindex = lastrockindex;
    ctx->rockindex = rockindex;
}
void HookState_Lost(Context *ctx, float dt) {

    int status = ctx->status;

    if (status != HOOK_STATUS_LOST) {
        return;
    }

    float hookradius = ctx->hookradius;
    Hook hook = ctx->hook;

    hookradius -= dt * ctx->hookspeed * 3;
    hook.pos = GetOnCirlce(ctx->hookstart, hook.angle, hookradius);

    if (hookradius <= 0) {
        status = HOOK_STATUS_WAVE;
        hookradius = 60;
    }

    ctx->status = status;
    ctx->hookradius = hookradius;
    ctx->hook = hook;
}

#endif