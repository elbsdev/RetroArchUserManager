#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

#include "../texts.h"


class mainScreen
{
    private:
        SDL_Renderer* gRenderer;
        TTF_Font* gFont;
        nlohmann::json* userDataPtr;
        
        std::vector<std::string> textList = {"RetroAchievements User Manager", "Active profile: ", "Coded by Elbs", "A - Edit profile | Y - Apply profile"};
        std::vector<std::string> menuTexts = {"Profile 1" , "Profile 2", "Profile 3", "Exit program"};
        
        std::vector<std::vector<int>> textPos = {{4, 4}, {4, 154}, {4, 460}, {350, 460}};
        std::vector<std::vector<int>> menuTextPos = {{14, 54}, {14, 74}, {14, 94}, {14, 114}};

        std::vector<std::vector<int>> menuActions = {{1, 1}, {1, 2}, {1, 3}, {-1, 0}};
        std::vector<progTexts*> sdlTextList;
        progTexts* selector;

        int menuItems = menuTexts.size() - 1;
        int selection = 0;
    public:
        void loadTexts();
        void reloadTexts();
        void render();
        void selectorChange();
        std::vector<int> keyPressed(SDL_Keycode key);
        
        mainScreen(SDL_Renderer* r, TTF_Font* f, nlohmann::json* jsonPtr)
        {
            gRenderer = r;
            gFont = f;
            userDataPtr = jsonPtr;
            loadTexts();
        }
};
