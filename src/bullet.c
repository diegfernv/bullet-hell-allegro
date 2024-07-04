#include "bullet.h"
#include "constants.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initBullet(Bullet *b, float x, float y, float direction) {
    b->x = x;
    b->y = y;
    b->direction = direction;
}

void moveBullet(Bullet *b, float speed, float modified_vx, float modified_vy) {
    b->x += speed * modified_vx * cos(b->direction);
    b->y += speed * modified_vy * sin(b->direction);
}

void moveWaves(Wave *w) {
    int i;

    if ( w == NULL ){
        return;
    }
    
    for ( i = 0; i < w->num_bullets; i++ ) {
        updateModifier(w, w->bullets[i].direction);
        moveBullet(&(w->bullets[i]), w->speed, w->modifier_vx, w->modifier_vy);
    }

    reduceTTS(w);
    moveWaves(w->next);
}


void reduceTTS(Wave *w) {
    if ( w->tts > 0 ) {
        w->tts--;
    }
    return;
}

Wave *createWave(float center_x, float center_y, int num_bullets, float speed, float initial_angle, float spread, int tts, char *type) {
    int i;
    Wave * newWave = (Wave *)malloc(sizeof(Wave));
    if (newWave == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newWave->bullets = (Bullet *)malloc(sizeof(Bullet)*num_bullets);
    for (i = 0; i < num_bullets; i++) {
        float direction; 
        if ( num_bullets == 1 ) {
            direction = initial_angle;
        } else {
            direction = initial_angle - spread/2 + i*(spread/num_bullets);
        }
        initBullet(&newWave->bullets[i], center_x, center_y, direction);
    }
    newWave->type = (char *)malloc(sizeof(char) * (strlen(type) + 1));
    strcpy(newWave->type, type);
    newWave->radius = 0.0;
    newWave->speed = speed;
    newWave->spread = spread;
    newWave->initial_angle = initial_angle;
    newWave->tts = tts;
    newWave->num_bullets = num_bullets;
    newWave->prev = NULL;
    newWave->next = NULL;
    return newWave;
}

//Editar esto y Create
void appendWave(Wave **node, float center_x, float center_y, int num_bullets, float speed, float initial_angle, float spread, int tts, char *type) {
    Wave * newWave = createWave(center_x, center_y, num_bullets, speed, initial_angle, spread, tts, type);
    if ( *node == NULL ) {
        *node = newWave;
        return;
    }
    Wave *temp = *node;
    while ( temp->next != NULL ) {
        temp = temp->next;
    }
    temp->next = newWave;
    newWave->prev = temp;
}

void deleteWave(Wave **node, Wave* del) {
    if ( *node == NULL || del == NULL ) {
        return;
    }
    if ( *node == del ) {
        *node = del->next;
    }
    if ( del->next != NULL ) {
        del->next->prev = del->prev;
    }
    if ( del->prev != NULL ) {
        del->prev->next = del->next;
    }
    free(del);
}

Wave *getWave(Wave *w, int index){
    if ( index == 0 )
        return w;
    if ( w == NULL )
        return NULL;
    
    return getWave(w->next, index - 1 );
}

Wave *getLastWave(Wave *w){
    if ( w->next == NULL ){
        return w;
    }
    return getLastWave(w->next);
}

void updateModifier(Wave *w, float direction) {
    float v;
    if ( strcmp(w->type, "constant") == 0 ) {
        w->modifier_vx = 1;
        w->modifier_vy = 1;
    }
    else if ( strcmp(w->type, "linear") == 0 ) {
        w->modifier_vx = (MAX_TTS - w->tts)/(float)MAX_TTS + 1;
        w->modifier_vy = w->modifier_vx;
    }
    else if ( strcmp(w->type, "flower") == 0 ) {
        v = fabs(sin(3*direction));
        w->modifier_vx = 0.3 * v + 1;
        w->modifier_vy = 0.3 * v + 1;
    }

    return;
}
