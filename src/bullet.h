#ifndef BULLET_H
#define BULLET_H

#define MAX_TTS 120

typedef struct Bullet {
    float x;
    float y;
    //Color
    //Sprite
    //delete
    //float speed;
    float direction;
} Bullet;

typedef struct Wave {
    Bullet *bullets;
    char *type;
    float radius;
    float speed;
    float modifier_vx;
    float modifier_vy;
    float spread;
    float initial_angle;
    int tts;
    int num_bullets;
    struct Wave *prev;
    struct Wave *next;
} Wave;

void initBullet(Bullet *b, float x, float y, float direction);
void moveBullet(Bullet *b, float speed, float modified_vx, float modified_vy);

void moveWaves(Wave *w);
void reduceTTS(Wave *w);
void updateModifier(Wave *w, float direction);

Wave *createWave(float center_x, float center_y, int num_bullets, float speed, float initial_angle, float spread, int tts, char *type);
Wave *getWave(Wave *w, int index);
Wave *getLastWave(Wave *w);
void appendWave(Wave **node, float center_x, float center_y, int num_bullets, float speed, float initial_angle, float spread, int tts, char *type);
void deleteWave(Wave **node, Wave* del);

#endif 
