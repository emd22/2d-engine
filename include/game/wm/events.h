#ifndef EVENTS_H
#define EVENTS_H

#include <game/macros.h>
#include <game/wm/wm.h>

#define MAX_KEYS_PRESSED 5

#ifdef IS_UNIX

#define EVENT_EXPOSE Expose
#define EVENT_KEYPRESS KeyPress
#define EVENT_KEYRELEASE KeyRelease
#define EVENT_CLIENTMESSAGE ClientMessage

#define SUBTYPE_WINDOW_RESIZE 1
#define SUBTYPE_WINDOW_MOVED  2
#endif

typedef struct {
#ifdef IS_UNIX
    XEvent event;
#endif
    int type;
    int subtype;
} event_t;

void wm_events_init(display_t *_display);
char wm_get_key(event_t *event);
char *wm_get_pressed_keys(int *length);
void wm_events_loop(void (*on_event)(event_t), void (*draw)(void));
int wm_events_is_running(void);
void wm_events_kill(void);

#endif