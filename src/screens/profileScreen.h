#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

#include "../texts.h"

class profileScreen
{
    private:
        SDL_Renderer* gRenderer;
        TTF_Font* gFont;
        nlohmann::json* userDataPtr;

        
        std::vector<std::string> textList = {"RetroAchievements User Manager - Editing Profile ", "Coded by Elbs"};
        std::vector<std::string> menuTexts = {"Back" , "Username: ", "Password: ", "Profile name: ", "Save changes"};
        
        std::vector<std::vector<int>> textPos = {{4, 4}, {4, 460}};
        std::vector<std::vector<int>> menuTextPos = {{14, 54}, {14, 74}, {14, 94}, {14, 114}, {14, 134}};

        std::vector<std::vector<int>> menuActions = {{0, 0}, {-3, 0}, {-3, 0}, {-3, 0}, {-3, 1}};
        std::vector<progTexts*> sdlTextList;
        progTexts* selector;

        //Teclado
        std::vector<std::vector<std::string>> keyboardLowerCase = {{"q", "w", "e", "r", "t", "y", "u", "i", "o", "p"},
                                                                   {"a", "s", "d", "f", "g", "h", "j", "k", "l"},
                                                                   {"z", "x", "c", "v", "b", "n", "m"},
                                                                   {""},
                                                                   {"B - Backspace | X - Ok | Y - Change charset"}};
        std::vector<progTexts*> keyboardLowerCaseText;
        std::vector<std::vector<std::string>> keyboardUpperCase = {{"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"},
                                                                   {"A", "S", "D", "F", "G", "H", "J", "K", "L"},
                                                                   {"Z", "X", "C", "V", "B", "N", "M"},
                                                                   {""},
                                                                   {"B - Backspace | X - Ok | Y - Change charset"}};
        std::vector<progTexts*> keyboardUpperCaseText;
        std::vector<std::vector<std::string>> keyboardNumSymbols = {{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"},
                                                                    {"!", "@", "#", "$", "%", "&", "*", "(", ")", "\""},
                                                                    {"-", "_", "+", "=", "{", "[", "]", "}", ",", "."},
                                                                    {"<", ">", ";", ":", "/", "?", "\\", "'"},
                                                                    {""},
                                                                    {"B - Backspace | X - Ok | Y - Change charset"}};
        std::vector<progTexts*> keyboardNumSymbolsText;

        std::string username = "";
        std::string password = "";
        std::string profileName = "";

        int menuItems = menuTexts.size() - 1;
        int selection = 0;
        int profileId = 0;
        int keyboardMode = 0;
        int kbdSelectorPosX = 14;
        int kbdSelectorPosY = 154;
        int kbdSelectorCol = 0;
        int kbdSelectorColMax = 9;
        int kbdSelectorLine = 0;
        int kbdSelectorLineMax = 2;
        bool keyboardEnabled = false;
    public:
        void loadTexts();
        void render();
        void selectorChange();
        void setProfileId(int id);
        void drawKeyboardSelector();
        std::vector<int> keyPressed(SDL_Keycode key);
        
        profileScreen(SDL_Renderer* r, TTF_Font* f, nlohmann::json* jsonPtr)
        {
            gRenderer = r;
            gFont = f;
            userDataPtr = jsonPtr;
            loadTexts();
        }
};