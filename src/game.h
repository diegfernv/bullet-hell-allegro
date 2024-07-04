#ifndef GAME_H
#define GAME_H
#include <stdio.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "bullet.h"
#include "constants.h"
#include "enemy.h"

void gameInit();
void gameUpdate();
void gameDraw(bool debug, ALLEGRO_FONT *font, int selection);

void drawWaves(Wave *w);
void drawBullet(Bullet *bullet, float r, float g, float b);

void changeStats(int selection, float direction);
void updateStats();
void drawStats(ALLEGRO_FONT *font, int selection);
void editArray(int num_bullets, float initial_angle, float spread, float speed);
#endif 
