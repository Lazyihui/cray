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
#include "Context.h"
#include "HookController.h"
#include "GUI.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 黄金旷工

void DrawGame(Context *ctx) {

    Rock *arrrock = ctx->arrrock;
    int lastrockindex = ctx->lastrockindex;
    Hook hook = ctx->hook;
    Vector2 manpos = ctx->manpos;
    int mansize = ctx->mansize;
    int score = ctx->score;
    float time = ctx->time;

    DrawLine(ctx->hookstart.x, ctx->hookstart.y, hook.pos.x, hook.pos.y, GRAY); // 钩子的线
    Hook_Draw(&hook);                                                           // 钩子

    for (int i = 0; i <= lastrockindex; i++) {
        Rock rock = arrrock[i];
        Rock_Draw(&rock);
    } // 随机画石头

    // DrawText(gold,10,20,20,YELLOW);
    Text_Int(score, 80, 20, 20, RED);
    Text_Int((int)time, 400, 10, 20, YELLOW);
    DrawLine(0, 122, 800, 122, GREEN);                        // 分界线
    DrawRectangle(manpos.x, manpos.y, mansize, mansize, RED); // 老头
    // DrawFPS(50, 50);  60FPS
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化
int main(void) {
    InitWindow(800, 450, "cyh");
    Context context;
    ContextInit(&context);

    // int a = 3;
    // Change(&a);
    // myRock 这种写法多看几遍
    // int rockindex;
    ////////////////////////生成金块

    for (int i = 0; i < rockcount; i++) {
        int rd = get_rand(0, ROCKTEMPLATECOUNT); // 随机得到0 1 2 这三个数
        Rock myRock = context.rocktemplates[rd]; // myRock 随机得到三种不同的石头
        int rdx = get_rand(0, 800);              // 随机的位置
        int rdy = get_rand(180, 450);            // 随机的位置
        myRock.pos.x = rdx;                      // 把随机的位置给到myRock的位置
        myRock.pos.y = rdy;                      // 把随机的位置给到myRock的位置

        context.arrrock[i] = myRock; // 把随机得到的石头存到arrrock[i]的数组里面
                                     // 然后每个arrrock[rockcount]里面都有不一样的石头 什么东西存下来就想到数组
        // printf("%d\r\n", rd);
    }

    SetTargetFPS(60);
    int gamestatus = 3;
    float linetime = 0;
    float angle = 0;
    while (!WindowShouldClose()) { /// 一针
        float dt = GetFrameTime();

        BeginDrawing();

        if (gamestatus == 0) {
            ClearBackground(WHITE);

            bool button =
                GUI_Button((Vector2){390, 220}, (Vector2){160, 30}, BLACK, "press", (Vector2){390, 220}, 14, YELLOW);
            Vector2 mouse = GetMousePosition();
            printf("(%f,%f)\r\n", mouse.x, mouse.y);
            // DrawText("please press the space bar to start game", 200, 200, 20, BLACK);
            // DrawText("请按下空格键开始游戏", 200, 200, 20, BLACK);

            if (button) {
                gamestatus = 1;
            }
        } else if (gamestatus == 1) {
            ClearBackground(BLACK);
            //////////////////time     dt= 1/fps 一秒内的dt和是一秒
            context.time -= dt;

            ////////////////////////////////////////////////////////黄金矿工第一关
            HookState_Wave(&context, dt);
            HookState_Move(&context, dt);
            HookState_Hook(&context, dt);
            HookState_Lost(&context, dt);
            ////////////////////下一关

            DrawGame(&context);
        } else if (gamestatus == 2) {
            //////////////////////////////////////////////画矩形旋转
            ClearBackground(WHITE);

            angle += dt * 50; ////////////////////////////////////////////////////////////////////////////////////////
            if (angle >= 360) {
                angle -= 360;
            }
            // Line_rotate(&linetime, dt);
            Rotate_LineRect((Vector2){.x = 400, .y = 200}, Vector2New(50, 30), angle, RED);
        } else if (gamestatus == 3) {
                ClearBackground(WHITE);

                angle += dt*200;
                if (angle >= 360) {
                angle -= 360;
            }
                Rotate_point(Vector2New(400,200),5,RED,angle,50);

        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
