#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "texts.h"

void progTexts::renderText()
{
    gTextTexture.render(posX, posY);
}