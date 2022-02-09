#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <sys/types.h>

#include "config.h"

typedef struct graphics_context_t {

    /* the ordering tables used to sort primitive packets */
    u_long ordering_tables[N_ORDERING_TABLES][ORDERING_TABLE_LENGTH];

    /* the currently active ordering table */
    size_t i_ordering_table;

    /* the current ordering table */
    u_long *ordering_table;

    /* the buffers used to allocate primitive packets */
    u_char primitive_buffers[N_PRIMITIVE_BUFFERS][PRIMITIVE_BUFFER_SIZE];

    /* the currently active primitive buffer */
    size_t i_primitive_buffer;

    /* the pointer to the end of the current primitive buffer where newly
     * allocated primitives will be stored */
    u_char *primitive_buffer_tail;

} graphics_context_t;

/* initialize the graphics context
 * this only initializes the struct, it doesnt configure hardware state */
void graphics_context_init (graphics_context_t *context);

/* configure hardware state to reflect the given graphics context */
void graphics_context_switch (graphics_context_t *context);

/* swap ordering tables and primitive buffers and send the previously prepared
 * ordering table one to the gpu for processing */
void graphics_context_flip (graphics_context_t *context);

/* allocate space from the current primitive buffer */
u_char *graphics_context_allocate_primitive (graphics_context_t *context,
                                             size_t size);

#endif /* GRAPHICS_H */
