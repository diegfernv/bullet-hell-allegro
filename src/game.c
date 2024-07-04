#include "game.h"
#include "bullet.h"
#include "constants.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

#define PATTERN_PARAMS 4
#define MAX_PATTERN 5
#define N_BULLETS 0
#define SPEED 1
#define I_ANGLE 2
#define SPREAD 3

Enemy enemy;
int wait_bullet;
int current_wave;
float arr[MAX_PATTERN][PATTERN_PARAMS] = {
    {30, 5, M_PI_2, 2*M_PI},
    {30, 5, M_PI_2, 2*M_PI},
    {30, 5, M_PI_2, 2*M_PI},
    {30, 5, M_PI_2, 2*M_PI},
    {30, 5, M_PI_2, 2*M_PI},
};
char *debug_parameters[] = {
    "Enemy position x", 
    "Enemy position y",
    "Rotation velocity",
    "Invert rotation",
    "Wave frequency",
    "Wave bullets",
    "Wave angle",
    "Wave spread",
    "Wave velocity"
};
float stats[PARAMETERS];

void gameInit()
{
    wait_bullet = 0, current_wave = 0;

    
    enemy = createEnemy(100);

    setEnemyPosition(&enemy, 400, 300);
    setEnemyShotFrequency(&enemy, 10);
    //setEnemyRotation(&enemy, M_PI/12, true);
    return;
}

void gameUpdate()
    {
    int i;
    if( wait_bullet >= enemy.wave_frequency ) {
        appendWave(&enemy.waves, enemy.x, enemy.y, arr[current_wave][N_BULLETS], arr[current_wave][SPEED], enemy.rotation_offset + arr[current_wave][I_ANGLE], arr[current_wave][SPREAD], MAX_TTS, "flower"); 
        
        wait_bullet = 0;
        current_wave = (current_wave+1)%MAX_PATTERN;

        if ( ! enemy.invert_rotation )
            enemy.rotation_offset = fmod(enemy.rotation_offset + enemy.rotation_velocity, 2*M_PI);
        else 
            enemy.rotation_offset = fmod(enemy.rotation_offset - enemy.rotation_velocity, 2*M_PI);
    }
    else {
        wait_bullet++;
    }

    moveWaves(enemy.waves);

    if ( enemy.waves != NULL && enemy.waves[0].tts == 0) {
        deleteWave(&enemy.waves, enemy.waves);
    }

    return;
}

void gameDraw(bool debug, ALLEGRO_FONT *font, int selection)
{
    drawWaves(enemy.waves);
    if ( debug ) {
        updateStats();
        drawStats(font, selection);
    }
    return;
}

void drawWaves(Wave *w) {
    int i;

    if ( w == NULL ) {
        return;
    }

    for ( i = 0; i < w->num_bullets; i++ ) {
        float color = w->tts/(float)MAX_TTS*255;
        drawBullet(&w->bullets[i], color, color, color);
    }

    drawWaves(w->next);
}

// TODO cambiar
void drawBullet(Bullet *bullet, float r, float g, float b) {
    al_draw_filled_circle(bullet->x, bullet->y, 4, al_map_rgb(r, 0, 0));
    al_draw_filled_circle(bullet->x, bullet->y, 2, al_map_rgb(r, g, b));
}

void changeStats(int selection, float direction) {
    switch ( selection ) {
        case 0:
            enemy.x += direction*10;
            break;
        case 1:
            enemy.y += direction*10;
            break;
        case 2:
            enemy.rotation_velocity += direction*M_PI/12;
            break;
        case 3:
            enemy.invert_rotation = !enemy.invert_rotation;
            break;
        case 4:
            enemy.wave_frequency += direction;
            break;
        case 5:
            editArray(direction,0,0,0);
            break;
        case 6:
            editArray(0,direction,0,0);
            break;
        case 7:
            editArray(0,0,direction,0);
            break;
        case 8:
            editArray(0,0,0,direction);
            break;
    }
    return;
}

void editArray(int num_bullets, float initial_angle, float spread, float speed) {
    int i;

    for ( i = 0; i < MAX_PATTERN; i++ ) {
        arr[i][N_BULLETS] += num_bullets;
        arr[i][I_ANGLE] += initial_angle*(M_PI/6);
        arr[i][SPREAD] += spread*(M_PI/6);
        arr[i][SPEED] += speed;
    }
    return;
}

void updateStats() {
    Wave *w;
    stats[0] = enemy.x;
    stats[1] = enemy.y;
    stats[2] = enemy.rotation_velocity;
    if ( enemy.invert_rotation )
        stats[3] = 1.0;
    else
        stats[3] = 0.0;
    stats[4] = enemy.wave_frequency;

    w = getLastWave(enemy.waves);
    stats[5] = w->num_bullets;
    stats[6] = w->initial_angle;
    stats[7] = w->spread;
    stats[8] = w->speed;
    return;
}

void drawStats(ALLEGRO_FONT *font, int selection) {
    int i, len;
    char *value;
    ALLEGRO_COLOR color;
    
    for (i = 0; i < PARAMETERS; i++ ) {
        len = snprintf(NULL, 0, "%.2f", stats[i]);
        value = malloc(len + 1);
        snprintf(value, len + 1, "%.2f", stats[i]);

        if ( i == selection )
            color = al_map_rgb(255, 255, 0);
        else
            color = al_map_rgb(255, 255, 255);
        al_draw_text(font, color, 20, 20 + i*20, 0, debug_parameters[i]);
        al_draw_text(font, color, 168, 20 + i*20, 0, value);
        free(value);
    }
    al_draw_text(font, color, 20, 20 + i*20, 0, "Type");
    al_draw_text(font, color, 168, 20 + i*20, 0, enemy.waves->type);


    return;
}
