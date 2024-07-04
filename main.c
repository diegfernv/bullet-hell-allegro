#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <allegro5/timer.h>
#include <stdbool.h>
#include "src/constants.h"
#include "src/game.h"

int main()
{
    al_init();
    al_install_keyboard();

    ALLEGRO_TIMER* fps_timer = al_create_timer(1.0 / FPS_TIMER);
    ALLEGRO_TIMER* logic_timer = al_create_timer(1.0 / LOGIC_TIMER);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(fps_timer));
    al_register_event_source(queue, al_get_timer_event_source(logic_timer));

    bool redraw = true;
    bool logic = true;
    bool running = true;
    bool debug = false;
    int selection = 0;
    ALLEGRO_EVENT event;

    al_start_timer(fps_timer);
    al_start_timer(logic_timer);

    gameInit();
    while(running)
    {
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER && event.timer.source == fps_timer)
            redraw = true;
        else if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
            running = false;
        else if( event.type == ALLEGRO_EVENT_TIMER && event.timer.source == logic_timer )
            logic = true;

        if( event.type == ALLEGRO_EVENT_KEY_DOWN ) {
            switch( event.keyboard.keycode ) {
                case ALLEGRO_KEY_ESCAPE:
                    running = false; break;
                case ALLEGRO_KEY_F1:
                    debug = !debug; 
                    break;
                case ALLEGRO_KEY_UP:
                    selection = (selection - 1)%PARAMETERS;
                    break;
                case ALLEGRO_KEY_DOWN:
                    selection = (selection + 1)%PARAMETERS;
                    break;
                case ALLEGRO_KEY_LEFT:
                    changeStats(selection, -1);
                    break;
                case ALLEGRO_KEY_RIGHT:
                    changeStats(selection, 1);
                    break;
            }
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            //al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
            gameDraw(debug, font, selection);
            al_flip_display();

            redraw = false;
        }
        if(logic && al_is_event_queue_empty(queue))
        {
            gameUpdate();
            logic = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(fps_timer);
    al_destroy_event_queue(queue);

    return 0;
}
