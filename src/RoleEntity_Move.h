#ifndef RoleEntity_Move_H
#define RoleEntity_Move_H
#include "../include/raylib.h"
#include "../include/raymath.h"
#include "RoleEntity.h"
#include "RoleEntity_Move.h"
#include "stdio.h"


void RoleEntity_Move(RoleEntity *role, float dt) {
    Vector2 dir = Vector2Scale(role->moveAxis, role->moveSpeed * dt);
    role->pos = Vector2Add(dir, role->pos);
}

void RoleEntity_MoveG(RoleEntity *role, float dt) {
    Vector2 dir = Vector2Scale(role->moveAxis, role->moveSpeed * dt);
    role->pos = Vector2Add(dir, role->pos);
}

void RoleEntity_MoveB(Bullet *Bullet, float dt) {
    Vector2 dir = Vector2Scale(Bullet->moveAxis, Bullet->moveSpeed * dt);
    Bullet->pos = Vector2Add(dir, Bullet->pos);
}

#endif 