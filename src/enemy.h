#ifndef ENEMY_H
#define ENEMY_H
#include <stdbool.h>
#include <stdio.h>
#include "constants.h"
#include "bullet.h"

typedef struct {
    char name[MAX_STR_SIZE];
    float x;
    float y;
    float speed;
    float direction;
    int life;
    Wave *waves;
    int wave_frequency;
    float rotation_offset;
    float rotation_velocity;
    bool invert_rotation;
} Enemy;

Enemy createEnemy(int life);
void setEnemyPosition(Enemy *e, float x, float y);
void setEnemyShotFrequency(Enemy *e, int frequency);
void setEnemyRotation(Enemy *e, float velocity, bool invert);

//void wipe_bullets(Bullet *bullets);
//void check_active_bullets(Enemy *e);
//void add_bullet(Enemy *e, float speed, float direction, int tts);

#endif
