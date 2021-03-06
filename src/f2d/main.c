// #include <f2d/wm/window.h>
// #include <f2d/wm/events.h>
// #include <f2d/macros.h>
// #include <f2d/wm/wm.h>

// #include <f2d/frutti2d.h>
// #include <f2d/threads.h>
// #include <f2d/texture.h>
// #include <f2d/shader.h>
// #include <f2d/draw.h>
// #include <f2d/file/bmp.h>

// #include <GL/glew.h>
// #include <GL/gl.h>

// #include <signal.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>

// #include <unistd.h>

// #define PLR_SPEED 0.1

// display_t *display = NULL;
// char started = 0;
// window_t window;
// unsigned shader_id;
// texture_t texture;
// texture_t texture2;

// // int key_pressed = 0;
// char *keys;
// int key_index = 0;
// int tick = 0;

// void check_keys(void) {
//     int i;
//     char ch;

//     for (i = 0; i < key_index; i++) {
//         ch = keys[i];
//         if (ch == 'w')
//             texture.y += PLR_SPEED;
//         else if (ch == 'a')
//             texture.x -= PLR_SPEED;
//         else if (ch == 's')
//             texture.y -= PLR_SPEED;
//         else if (ch == 'd')
//             texture.x += PLR_SPEED;
//     }
// }

// void draw(void) {
//     check_keys();
//     draw_all(display, &window, shader_id);
// }

// void on_event(event_t event) {
//     draw_event_t draw_event;
//     switch (event.type) {
//         case EVENT_CLIENTMESSAGE:
//             wm_events_kill();
//             break;
//         case EVENT_KEYRELEASE:
//             break;
//         case EVENT_KEYPRESS:
//             keys = wm_get_pressed_keys(&key_index);
//             break;
//         case EVENT_BUTTONPRESS:
//             break;
//         case EVENT_BUTTONRELEASE:
//             break;
//         // case EVENT_EXPOSE:
//         //     switch (event.subtype) {
//         //         case SUBTYPE_WINDOW_RESIZE:
//         //             break;
//         //         default:
//         //             break;
//         //     }
//         //     break;
//     }
// }

// void window_function_setup() {
//     window = window_new("Interesting Title", WINDOW_FLAG_ROOT);

// }

// void window_function(void) {

//     shader_id = shader_load("../shaders/tex.vert", "../shaders/tex.frag");
//     glClearColor(0.4, 0.0, 0.6, 1.0);
//     texture = texture_load("../test.bmp");
//     texture.draw_width = 100;
//     texture.draw_height = 100;

//     texture2 = texture_dupe(&texture);
//     texture2.draw_width = 100;
//     texture2.draw_height = 100;

//     draw_event_t draw_event;
//     draw_event.type = DRAW_EVENT_SINGLE_DRAW;
//     draw_event.value = 0;
//     draw_event.texture = texture;
    
//     draw_push_event(&draw_event);
//     draw_event.texture = texture2;
//     texture2.y = 200;
//     draw_push_event(&draw_event);
//     started = 1;
    
    
//     // 
// }

// int main() {
//     game_parameters_t game_params;
//     game_params.wm_start_setup_func = &window_function_setup;
//     game_params.wm_start_func       = &window_function;
//     game_params.draw_func           = &draw;
//     game_params.on_event_func       = &on_event;
//     game_start(game_params);

//     draw_event_t draw_event;    
//     while (!started);
    
//     keys = wm_get_pressed_keys(&key_index);
//     // key_pressed = 0;

//     //main thread
//     while (wm_events_is_running()) {
//         check_keys();

//         draw_event.type = 0;
//         draw_event.value = 0;

//         draw_event.texture = texture;
//         draw_push_event(&draw_event);
//         draw_event.texture = texture2;
//         draw_push_event(&draw_event);
//         // while (1);
//         usleep(700);
//     }

    
//     // unsigned char img[] = {
//     //     0, 0, 0,     1, 1, 1,
//     //     0, 0, 0,     1, 1, 1
//     // };
//     // while (wm_events_is_running());

//     game_cleanup();

//     texture_delete(&texture);
//     texture_delete(&texture2);
//     shader_delete(shader_id);

//     return 0;
// }