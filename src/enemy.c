#include "enemy.h"

Enemy createEnemy(int life) {
    Enemy e;
    e.x = -1;
    e.y = -1;
    e.speed = 0;
    e.direction = 0;
    e.life = life;
    e.waves = NULL;
    e.wave_frequency = 0;
    e.rotation_velocity = 0;
    e.rotation_offset = 0;
    e.invert_rotation = false;
    return e;
}

void setEnemyPosition(Enemy *e, float x, float y) {
    e->x = x;
    e->y = y;
    return;
}

void setEnemyShotFrequency(Enemy *e, int frequency) {
    e->wave_frequency = frequency;
    return;
}

void setEnemyRotation(Enemy *e, float velocity, bool invert) {
    e->rotation_velocity = velocity;
    e->invert_rotation = invert;
}
