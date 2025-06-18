#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

#include "texture.h"

SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface != NULL)
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

LTexture::LTexture()
{
    mTexture = NULL;
    gFont = NULL;
    gRenderer = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

    if (newTexture != NULL)
    {
        mWidth = loadedSurface->w;
        mHeight = loadedSurface->h;
    }

    SDL_FreeSurface(loadedSurface);
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        gFont = NULL;
        mTexture = NULL;
        gRenderer = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

void LTexture::setFont(TTF_Font* fnt)
{
    gFont = fnt;
}

void LTexture::setRenderer(SDL_Renderer* renderer)
{
    gRenderer = renderer;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    
    if (textSurface != NULL)
    {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture != NULL)
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    } else std::cout << SDL_GetError() << std::endl;
    return mTexture != NULL;
}