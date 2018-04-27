#ifndef FREETYPEHARFBUZZ_HARFBUZZ_H
#define FREETYPEHARFBUZZ_HARFBUZZ_H

#include <hb.h>
#include <hb-ft.h>


int init_font(const char* font_path,
              int font_size,
              hb_font_t** font);


#endif
