#ifndef CONTEXT_H
#define CONTEXT_H

#include "display.h"

/* we will use this structure to encapsulate the hardware state of our
 * running program, this way we can stay more organized than we would using
 * global variables, and it means we can switch between multiple contexts */
typedef struct context_t {

    /* the current state of the display will be managed by this object */
    display_context_t display;

} context_t;

/* switch program context
 * this sets the hardware state to whats described by the state of the context */
void context_switch (context_t *context);

/* initialize a context */
void context_init (context_t *context);

#endif /* CONTEXT_H */
