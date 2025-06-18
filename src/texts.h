#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>
#include <vector>

#include "texture.h"

class progTexts
{
    public:
        LTexture gTextTexture;
        int posX;
        int posY;

        progTexts(std::string t, SDL_Color c, int x, int y, TTF_Font* gFont, SDL_Renderer* gRenderer)
        {
            gTextTexture.setFont(gFont);
            gTextTexture.setRenderer(gRenderer);
            gTextTexture.loadFromRenderedText(t, c);
            posX = x;
            posY = y;
        };
        void renderText();
};