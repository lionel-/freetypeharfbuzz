#ifndef FREETYPEHARFBUZZ_FREETYPE_H
#define FREETYPEHARFBUZZ_FREETYPE_H


#include <ft2build.h>
#include FT_FREETYPE_H

// Explicit semantics
#define ft_library FT_LibraryRec_
#define ft_face FT_FaceRec_

extern struct ft_library* library;


#endif
