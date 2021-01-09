#ifndef __FONT_H__
#define __FONT_H__

#include "Defs.h"
#include "Module.h"

#include "SDL/include/SDL.h"
#include "Textures.h"

class Font : public Module
{
public:

    Font(const char* rtpFontFile, Textures* tex);

    ~Font();

    SDL_Texture* GetTextureAtlas();
    SDL_Rect GetCharRec(int value);

private:

    bool fontLoaded;

    SDL_Texture* texture;

    int baseSize;
    int charsCount;
    SDL_Rect charsRecs[128];
};

#endif //__FONT_H__