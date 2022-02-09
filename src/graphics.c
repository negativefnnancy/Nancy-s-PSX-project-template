#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "graphics.h"

void graphics_context_init (graphics_context_t *context) {

    /* set the current ordering table and primitive buffers to the first ones */
    context->i_ordering_table   = 0;
    context->i_primitive_buffer = 0;

    /* set the current primitive buffer tail pointer to the beginning of the
     * current one */
    context->primitive_buffer_tail
        = context->primitive_buffers[context->i_primitive_buffer];

    /* set the pointer to the current ordering table */
    context->ordering_table = context->ordering_tables[context->i_ordering_table];

    /* clear the current ordering table so its ready for sorting new packets ! */
    ClearOTagR (context->ordering_table, ORDERING_TABLE_LENGTH);
}

void graphics_context_switch (graphics_context_t *context) {

    /* initialize the gte */
    InitGeom (); /* this resets the gte */
    SetGeomOffset (CENTER_X, CENTER_Y); /* this gets added to the output of
                                           screen projection functions
                                           and contributes to our setup for
                                           properly converting from normalized
                                           device coordinates to screen
                                           coordinates */
    SetGeomScreen (SCREEN_Z); /* this sets the value that is used by the gte
                                 perspective projection functions */

    /* TODO: any particular values here that might change between contexts
     * should be stored instead as fields in context */
}

void graphics_context_flip (graphics_context_t *context) {
    
    /* send the current ordering table to the gpu for processing */
    DrawOTag (&context->ordering_tables[context->i_ordering_table][ORDERING_TABLE_LENGTH - 1]);

    /* swap ordering tables and primitive buffers */
    context->i_ordering_table
        = (context->i_ordering_table + 1) % N_ORDERING_TABLES;
    context->i_primitive_buffer
        = (context->i_primitive_buffer + 1) % N_PRIMITIVE_BUFFERS;

    /* TODO: dont duplicate this code with the end of init??? */
    /* set the current primitive buffer tail pointer to the beginning of the
     * current one */
    context->primitive_buffer_tail
        = context->primitive_buffers[context->i_primitive_buffer];

    /* set the pointer to the current ordering table */
    context->ordering_table = context->ordering_tables[context->i_ordering_table];

    /* clear the current ordering table so its ready for sorting new packets ! */
    ClearOTagR (context->ordering_table, ORDERING_TABLE_LENGTH);
}

u_char *graphics_context_allocate_primitive (graphics_context_t *context,
                                             size_t size) {

    u_char *primitive = context->primitive_buffer_tail;
    context->primitive_buffer_tail += size;
    return primitive;
}
