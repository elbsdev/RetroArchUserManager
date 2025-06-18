#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class LTexture
{
    public:
        LTexture();
        ~LTexture();
        bool loadFromFile(std::string path, SDL_Renderer* gRenderer);
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
        void free();
        void setColor(Uint8 red, Uint8 g, Uint8 b);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);
        void setFont(TTF_Font*);
        void setRenderer(SDL_Renderer*);
        void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        int getWidth();
        int getHeight();
    private:
        SDL_Texture* mTexture;
        SDL_Renderer* gRenderer;
        TTF_Font* gFont;

        int mWidth;
        int mHeight;
};