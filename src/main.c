#include "../include/raylib.h"
#include "../include/raymath.h"
#include "stdio.h"
#include "RoleEntity.h"
#include "RoleEntity_Inpupt.h"
#include "RoleEntity_Move.h"
#include "stdlib.h"
#include "time.h"

int Big(int a , int b ){
    if (a>b){
        return a;
    }else{
        return b;
    }
}

bool IsPointInsideRect(Vector2 pos, Vector2 rectanglePoint,Vector2 rectangleSize){
    if (pos.x>rectanglePoint.x && pos.x<rectanglePoint.x+rectangleSize.x && pos.y>rectanglePoint.y && pos.y<rectanglePoint.y+rectangleSize.y){
        return true;
    }else{
        return false;
    }

}

bool ISPointsideCircle(Vector2 pos, Vector2 circlepoint, float circleradius){
   
    if ( (pos.x-circlepoint.x)*(pos.x-circlepoint.x)+(pos.y-circlepoint.y)*(pos.y-circlepoint.y)<=circleradius*circleradius){
        return true;
    }else{
        return false;
    }

}









int GetIndex(int *arr , int arrLines, int arrCountPerLine,int VisitLineIndex, int visitCoulumnIndex ){
    int Index;
    return Index;
}

int main(void) {
    InitWindow(800, 450, "cyh");
        int arr[100000] ={0};
        int i,j;
        arr[500] = 1;
    RoleEntity role = {.moveAxis = (Vector2){0},
                       .pos = {.x = 40, .y = 20},
                       .height = 50,
                       .width = 50,
                       .moveSpeed = 100,
                       .color = GREEN};
    RoleEntity role1 = {.moveAxis = (Vector2){0},
                        .pos = {.x = 40, .y = 320},
                        .height = 50,
                        .width = 50,
                        .moveSpeed = 150,
                        .color = RED};
    RoleEntity role2 = {.moveAxis = {0}, .color = RED, .height = 20, .width = 40, .pos = {.x = 50, .y = 50}};
            srand(time(NULL));
    

    while (!WindowShouldClose()) {
        // BeginDrawing();
        ClearBackground(BLACK);
        float dt = GetFrameTime(); //
        RoleEntity_Draw(&role1);
        RoleEntity_Draw(&role);
        // RoleEntity_DrawB(&Bullet);
        RoleEntity_Input(&role1);
        RoleEntity_InputG(&role);
        // RoleEntity_InputB(&Bullet);
      RoleEntity_Move(&role1, dt);
        RoleEntity_MoveG(&role, dt);
        // RoleEntity_MoveB(&Bullet,dt);
        TextFormat("Delta Time : %f ", dt);
        DrawText("hh",0,0,10,YELLOW);
        DrawRectangle(50, 50, 45, 20, RED);
        DrawText("press", 50, 50, 15, BLACK);

        Vector2 pos = GetMousePosition();
        bool isleftdown = IsMouseButtonPressed( MOUSE_BUTTON_LEFT);
        Vector2 rectangle= {.x=50,.y=50};

        bool isinside = IsPointInsideRect(pos,rectangle,(Vector2){.x=45,.y=20});

        if (isinside && isleftdown) {
           
        }
        DrawCircle(80,80,10,YELLOW);
        DrawText("press",80,80,15,BLACK);
        bool isinsidecircle = ISPointsideCircle(pos, (Vector2){.x=80,.y=80,},10);

        if(isinsidecircle && isleftdown ){
            DrawCircle(80,120,20,RED);
        }
       

        // int Index =GetIndex(arr[500],500,);
        // for(int i=0; i<100000 ; i++ ){
        //     if(arr[i]==0){
        //         continue;
        //     }else{
                
        //         int i = rand ();
        //     }
        
        // };
        

        EndDrawing();
    

        
    }

    CloseWindow();

    return 0;
}

// 按钮   方块加字 然后 鼠标找到