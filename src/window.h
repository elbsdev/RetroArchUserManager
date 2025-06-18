#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

#include "screens/mainScreen.h"
#include "screens/profileScreen.h"

class appWindow
{
    private:
        SDL_Event winEvent;
        bool winLoop;
        int currentScreenId;
        int numOptions;
        int selectedOption;
        int screenParam;
    public:
        SDL_Renderer* gRenderer;
        SDL_Window* window;
        TTF_Font* gFont;        
        mainScreen* gMainScr;
        profileScreen* gProfScr;
        //LTexture gTextTexture;

        appWindow()
        {
            
        }
        void appLoop();
        std::vector<int> screenEvent(SDL_Keycode key);
};