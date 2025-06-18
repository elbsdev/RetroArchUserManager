#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "window.h"
#include "vars.h"

void writeLog(std::string logText)
{
    std::ofstream logFile;
    
    logFile.open("./errlog.txt");
    logFile << logText << std::endl;
    logFile.close();
}


int main()
{
    appWindow* mainWnd = new appWindow();

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        writeLog("Erro SDL_INIT_VIDEO");
        return 1;
    }
    mainWnd->window = SDL_CreateWindow("RAUserManager", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP);
    if (mainWnd->window == NULL) 
    {
        writeLog("Erro mainWindow == NULL");
        return 2;
    }
        
    mainWnd->gRenderer = SDL_CreateRenderer(mainWnd->window, -1, SDL_RENDERER_ACCELERATED);
    if (mainWnd->gRenderer == NULL) 
    {
        writeLog("Erro mainWindow gRenderer == NULL");
        return 3;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        writeLog("Erro IMG_INIT");
        return 4;
    }    

    if (TTF_Init() < 0)
    {
        writeLog("Erro TTF_INIT");
        return 5;
    }

    mainWnd->gFont = TTF_OpenFont(GUI_FONT, 16);

    if (!mainWnd->gFont)
    {
        writeLog("Erro carregando fonte");
        return 6;
    }

    
    SDL_SetRenderDrawColor(mainWnd->gRenderer, 14, 14, 14, 255);
    
    //vai pro loop principal
    mainWnd->appLoop();

    TTF_CloseFont(mainWnd->gFont);
    free(mainWnd);

    SDL_DestroyRenderer(mainWnd->gRenderer);
    SDL_DestroyWindow(mainWnd->window);
    SDL_Quit();
    return 0;
}