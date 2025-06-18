#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <fstream>

#include "window.h"
#include "vars.h"

std::vector<int> appWindow::screenEvent(SDL_Keycode key)
{
    std::vector<int> returned = {-2, 0};
    switch (currentScreenId)
    {
    case 0:
        returned = gMainScr->keyPressed(key);
        break;
    case 1:
        returned = gProfScr->keyPressed(key);
        break;
    
    default:
        break;
    }
    return returned;
}

void appWindow::appLoop()
{
    winLoop = true;
    currentScreenId = 0;
    numOptions = 2;

    std::ifstream f("./users.json");
    nlohmann::json userData = nlohmann::json::parse(f);

    gMainScr = new mainScreen(gRenderer, gFont, &userData);
    gProfScr = new profileScreen(gRenderer, gFont, &userData);

    while (winLoop)
    {
        while (SDL_PollEvent(&winEvent))
        {
            if (winEvent.type == SDL_QUIT) winLoop = false;
            else if(winEvent.type == SDL_KEYDOWN)
            {
                
                std::vector<int> ret = screenEvent(winEvent.key.keysym.sym);
                if (ret[0] == -1) winLoop = false;
                else if (ret[0] != -2)
                {
                    currentScreenId = ret[0];
                    screenParam = ret[1];
                    if (currentScreenId == 1)
                    {
                        gProfScr->setProfileId(screenParam);
                    }
                    else gMainScr->reloadTexts();
                } 
            }
        }
        SDL_RenderClear(gRenderer);
        
        SDL_SetRenderDrawColor(gRenderer, 14, 14, 14, 255);
        switch (currentScreenId)
        {
        case 0:
            gMainScr->render();
            break;
        case 1:
            gProfScr->render();
            break;
        
        default:
            break;
        }

        SDL_RenderPresent(gRenderer);

        SDL_Delay(1000/60);
    }
}