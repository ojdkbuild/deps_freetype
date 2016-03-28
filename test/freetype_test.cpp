/* 
 * File:   freetype_test.cpp
 * Author: alex
 *
 * Created on January 5, 2016, 7:18 PM
 */

#include <memory>
#include <cstdio>

#include "ft2build.h"
#include FT_FREETYPE_H

int main() {
    FT_Library library;
    auto err_init = FT_Init_FreeType(std::addressof(library));
    if(err_init) { puts("FT_Init_FreeType error"); return 1; }
    FT_Face face;
    auto err_load = FT_New_Face(library, "../test/font/DejaVuSans.ttf", 0, std::addressof(face));
    if(err_load) { puts("FT_New_Face error"); return 1; }
    
    FT_Done_FreeType(library);
    
    puts("Test passed.");
    return 0;
}

