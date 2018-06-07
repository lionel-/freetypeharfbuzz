#ifndef FREETYPEHARFBUZZ_HARFBUZZ_H
#define FREETYPEHARFBUZZ_HARFBUZZ_H

#include <hb.h>
#include <hb-ft.h>


int init_font(const char* font_path,
              double font_size,
              hb_font_t** font_out);

int init_buffer(const char* string,
                hb_font_t* font,
                hb_buffer_t** buffer_out);


#endif
