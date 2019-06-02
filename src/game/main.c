#include <game/wm/window.h>
#include <game/wm/events.h>
#include <game/macros.h>
#include <game/wm/wm.h>

#include <game/threads.h>
#include <game/texture.h>
#include <game/shader.h>
#include <game/draw.h>
#include <game/file/bmp.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>

display_t *display = NULL;
char started = 0;
GLXContext glx_context;
window_t window;
unsigned shader_id;
texture_t texture;
texture_t texture2;

int key_pressed = 0;
char *keys;
int key_index = 0;
int tick = 0;

void check_keys(void) {
    int i;
    char ch;

    for (i = 0; i < key_index; i++) {
        ch = keys[i];
        if (ch == 'w')
            texture.y += 1;
        else if (ch == 'a' && texture.x != 0)
            texture.x -= 1;
        else if (ch == 's')
            texture.y -= 1;
        else if (ch == 'd' && texture.y != 600)
            texture.x += 1;
    }


    // char ch = wm_get_key(event);
    // switch (wm_get_key(event)) {
    //     case 'w':
    //         break;
    //     case 'a':
    //         break;
    //     case 's':
    //         break;        
    //     case 'd':
    //         break;
    // }
}

void draw(void) {
    draw_all(display, &window, shader_id);

    if (tick < 1000)
        tick++;
    else {
        check_keys();
        tick = 0;
    }
}

void on_event(event_t event) {
    draw_event_t draw_event;
    switch (event.type) {
        case EVENT_CLIENTMESSAGE:
            wm_events_kill();
            break;
        case EVENT_KEYRELEASE:
            keys = wm_get_pressed_keys(&key_index);
            key_pressed = 0;
            printf("releasing key\n");
            break;
        case EVENT_KEYPRESS:
            key_pressed = 1;
            // texture.x += 1;
            draw_event.type = 0;
            draw_event.value = 0;
            // memcpy(&draw_event.texture, &texture, sizeof(texture_t));
            draw_event.texture = texture;
            draw_push_event(&draw_event);
            draw_event.texture = texture2;
            draw_push_event(&draw_event);

            break;
        case EVENT_EXPOSE:
            draw_event.type = DRAW_EVENT_SINGLE_DRAW;
            draw_event.value = 0;
            draw_event.texture = texture;
            draw_push_event(&draw_event);
            draw_event.texture = texture2;
            draw_push_event(&draw_event);
            draw_all(display, &window, shader_id);
            switch (event.subtype) {
                case SUBTYPE_WINDOW_RESIZE:
                    break;
                default:
                    break;
            }
            break;
    }
}

void *window_thread(void *arg) {
#ifdef IS_UNIX
    XInitThreads();
#endif
    display = wm_start();
    wm_events_init(display);
    window = window_new("fut", WINDOW_FLAG_ROOT, &glx_context);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
        printf("glew failed\n");
        wm_events_kill();
        wm_exit(display);
        return NULL;
    }

    shader_id = shader_load("../shaders/tex.vert", "../shaders/tex.frag");
    glClearColor(0.4, 0.0, 0.6, 1.0);
    texture = texture_load("../test.bmp");
    texture.draw_width = 100;
    texture.draw_height = 100;

    texture2 = texture_load("../frick.bmp");
    texture2.draw_width = 100;
    texture2.draw_height = 100;

    draw_event_t draw_event;
    draw_event.type = DRAW_EVENT_SINGLE_DRAW;
    draw_event.value = 0;
    draw_event.texture = texture;
    // memcpy(&draw_event.texture, &texture, sizeof(texture_t));
    draw_push_event(&draw_event);
    draw_event.texture = texture2;
    texture2.y = 200;
    draw_push_event(&draw_event);
    started = 1;
    
    wm_events_loop(&on_event, &draw);
    
    texture_delete(&texture);
    glDeleteProgram(shader_id);

    wm_exit(display);
    return NULL;
}

int main() {
    thread_t event_thread;
    thread_create(&event_thread, &window_thread, NULL);
    
    while (!started);
    keys = wm_get_pressed_keys(&key_index);
    key_pressed = 0;
    
    // unsigned char img[] = {
    //     0, 0, 0,     1, 1, 1,
    //     0, 0, 0,     1, 1, 1
    // };
    // while (wm_events_is_running());
    thread_join(event_thread, NULL);

    return 0;
}