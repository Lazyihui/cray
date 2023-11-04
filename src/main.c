#include "../include/raylib.h"
#include "../include/raymath.h"
#include "stdio.h"
#include "RoleEntity.h"
#include "RoleEntity_Inpupt.h"
#include "RoleEntity_Move.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "RockEntity.h"
#include "common.h"
#include "HookEntity.h"
#define WIDTH 500 // 定义一个常量
#define HEIGHT 500
#define rockcount 10




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 黄金旷工



// 初始化
int main(void) {
    InitWindow(800, 450, "cyh");

    Rock rockmin = {.color = YELLOW, .heavy = 10, .pos = {.x = 0, .y = 0}, .radius = 10, .gold = 50};
    Rock rockmid = {.color = YELLOW, .heavy = 20, .pos = {.x = 0, .y = 0}, .radius = 20, .gold = 250};
    Rock rockmax = {.color = YELLOW, .heavy = 30, .pos = {.x = 0, .y = 0}, .radius = 30, .gold = 500};

    Rock arrrock[rockcount] = {0}; // 数组存rockcount个的圆

    Rock rocktemplates[3] = {rockmin, rockmid, rockmax}; // 数组 存三种类型的圆

    // myRock 这种写法多看几遍
    int temindex; // 1111
                  // int rockindex;
    ////////////////////////生成金块

    for (int i = 0; i < rockcount; i++) {
        int rd = get_rand(0, 3);         // 随机得到0 1 2 这三个数
        Rock myRock = rocktemplates[rd]; // myRock 随机得到三种不同的石头
        int rdx = get_rand(0, 800);      // 随机的位置
        int rdy = get_rand(180, 450);    // 随机的位置
        myRock.pos.x = rdx;              // 把随机的位置给到myRock的位置
        myRock.pos.y = rdy;              // 把随机的位置给到myRock的位置

        arrrock[i] = myRock; // 把随机得到的石头存到arrrock[i]的数组里面 然后每个arrrock[rockcount]里面都有不一样的石头
                             // 什么东西存下来就想到数组
        // printf("%d\r\n", rd);
    }

    ///////////////////生成钩子
    Hook hook = {.color = BROWN, .speed = 30, .radius = 5, .pos = {.x = 360, .y = 122}};
    ////////////////////////
    int rockindex;
    Vector2 manpos;
    manpos.x = 380; // 老头的位置
    manpos.y = 81;
    int hookdir = 1;  ///////////////////////????????????
    int mansize = 40; // 因为是一个正方形

    // shoot
    float r = 60;
    int status = 0;        // 状态   //状态这样使不同的状态可以转变
    float hookspeed = 120; // 速度

    int lastrockindex = rockcount - 1;
    int score=0;
    SetTargetFPS(60);

    float time = 60;
       

    while (!WindowShouldClose()) {/// 一针
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);

        //////////////////time     dt= 1/fps 一秒内的dt和是一秒
        time-=dt;

        // 0 摆动 1 发出 2 勾到收回 3 没勾到
        Vector2 hookstart;
        hookstart.x = manpos.x + (mansize / 2);
        hookstart.y = manpos.y + mansize;
        if (status == 0) {
            hook.angle += hook.speed * dt * hookdir; // 角度的变化   int hookdir = 1;

            hookstart.x = manpos.x + (mansize / 2);
            hookstart.y = manpos.y + mansize; // 得到老头中心点下面的位置（钩子中的位置）
            if (hook.angle >= 180) {
                hookdir = -1;
            } else if (hook.angle <= 0) {
                hookdir = 1;
            } // 钩子在0-180内左右摆动

            ////////////////////////钩子伸长
            // 角度不变 半径变长
            if (IsKeyPressed(KEY_SPACE)) {
                status = 1;
            }

            //////////////////////// 钩子左右摆动
            hook.pos = GetOnCirlce(hookstart, hook.angle, r);
        }

        else if (status == 1) {
            r += dt * hookspeed; // hookspeed = 100;
            hook.pos = GetOnCirlce(hookstart, hook.angle, r);

            // 检测 遍历所有数组
            for (int i = 0; i < rockcount; i++) {
                Rock rock = arrrock[i];
                bool isintersect = IsCirlceInsideCircle(hook.radius, rock.radius, hook.pos, rock.pos);
                if (isintersect) {
                    rockindex = i; // 存
                    status = 2;    // 勾到
                    break;
                }
            }
            if (hook.pos.x > 800 || hook.pos.x < 0 || hook.pos.y > 450) {
                status = 3;
            }

        }

        // 勾到2
        else if (status == 2) {

            Rock *rock = &arrrock[rockindex]; // 指针指向地址 *  指  &//////////!!!!/

            /////////////////////////////不同重量金块不同速度
            float rate = GetHeavyRate(rock->heavy);
            r -= dt * hookspeed * rate;
            // r=Clamp(r,0,r);//取
            r = fmax(0, r); // 0和r的最大值
            hook.pos = GetOnCirlce(hookstart, hook.angle, r);
            rock->pos = hook.pos;//1/60 fps
            Rock_Gold(*rock);

            if (r == 0) {
                score+=rock->gold;
                Rock a = arrrock[lastrockindex]; // rockindex是抓到的金块
                arrrock[lastrockindex] = arrrock[rockindex];
                arrrock[rockindex] = a;
                lastrockindex--;
            }

            if (r <= 0) {
                status = 0;
                r = 60;
            }

        }

        // 没勾到3
        else if (status == 3) {
            r -= dt * hookspeed * 3;
            hook.pos = GetOnCirlce(hookstart, hook.angle, r);

            if (r <= 0) {
                status = 0;
                r = 60;
            }
        }

        for (int i = 0; i <= lastrockindex; i++) {
            Rock rock = arrrock[i];
            Rock_Draw(&rock);
        } // 随机画石头
        
       ////////////////////下一关


//    controller


        ///////画分数


        Text_Int(score,20,20,20,RED);
        Text_Int((int)time,400,10,20,YELLOW);

        DrawLine(0, 122, 800, 122, GREEN);                                // 分界线
        DrawRectangle(manpos.x, manpos.y, mansize, mansize, RED);         // 老头
        Hook_Draw(&hook);                                                 // 钩子
        DrawLine(hookstart.x, hookstart.y, hook.pos.x, hook.pos.y, GRAY); // 钩子的线
        DrawFPS(50,50);
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
