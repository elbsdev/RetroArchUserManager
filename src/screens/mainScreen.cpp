#include "mainScreen.h"
#include "../vars.h"


void mainScreen::loadTexts()
{
    std::string activeProfileId;
    std::string activeProfileName;
    std::string p1Name;
    std::string p2Name;
    std::string p3Name;
    
    activeProfileId = (*userDataPtr)["active"];
    activeProfileName = (*userDataPtr)[activeProfileId]["name"];
    p1Name = (*userDataPtr)["P1"]["name"];
    p2Name = (*userDataPtr)["P2"]["name"];
    p3Name = (*userDataPtr)["P3"]["name"];
    


    textList[1] = "Active profile: " + activeProfileName;
    menuTexts[0] = "Profile 1 ("+p1Name+")";
    menuTexts[1] = "Profile 2 ("+p2Name+")";
    menuTexts[2] = "Profile 3 ("+p3Name+")";

    int i=0;
    for (std::string &text : textList)
    {
        sdlTextList.push_back(new progTexts(text, SDL_Color {0, 255, 60}, textPos[i][0], textPos[i][1], gFont, gRenderer));
        i++;
    }
    //Texto do menu
    i = 0;
    for (std::string &text : menuTexts)
    {
        sdlTextList.push_back(new progTexts(text, SDL_Color {0, 255, 60}, menuTextPos[i][0], menuTextPos[i][1], gFont, gRenderer));
        i++;
    }
    selector = new progTexts(">", SDL_Color {0, 255, 60}, 4, 54, gFont, gRenderer);

    selector->posY = 54 + 20 * selection;
}

void mainScreen::reloadTexts()
{
    sdlTextList.clear();
    loadTexts();
}

void mainScreen::render()
{
    for (auto &text : sdlTextList)
    {
        text->renderText();
    }
    selector->renderText();
}

std::vector<int> mainScreen::keyPressed(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_DOWN:
        {
            selection++;
            if (selection > menuItems) selection = 0;
            selector->posY = 54 + 20 * selection;
        }
        break;
    case SDLK_UP:
        {
            selection--;
            if (selection < 0) selection = menuItems;
            selector->posY = 54 + 20 * selection;
        }
        break;
    case SDLK_x:
        {
            return menuActions[selection];
        }
        break;
    case SDLK_a:
        {
            std::string profileIdStr = "";

            switch (selection)
            {
            case 0:
                profileIdStr = "P1";
                break;
            case 1:
                profileIdStr = "P2";
                break;
            case 2:
                profileIdStr = "P3";
                break;
            default:
                break;
            }
            if (profileIdStr != "")
            {
                (*userDataPtr)["active"] = profileIdStr;
                if (profileIdStr != "")
                {
                    std::string username = (*userDataPtr)[profileIdStr]["username"];
                    std::string password = (*userDataPtr)[profileIdStr]["password"];
                    std::ofstream o("users.json");
                    o <<  std::setw(4) << (*userDataPtr) << std::endl;

                    //grava os dados nos arquivos do retroarch
                    std::ifstream cfg(RETROARCH_CFG);
                    std::vector<std::string> raCfgFileText;
                    std::string line;

                    while(std::getline(cfg, line))
                    {
                        if (!line.compare(0, 16, "cheevos_username")) line = "cheevos_username = \""+username+"\"";
                        else if (!line.compare(0, 16, "cheevos_password")) line = "cheevos_password = \""+password+"\"";
                        else if (!line.compare(0, 13, "cheevos_token")) line = "cheevos_token = \"\"";
                        raCfgFileText.push_back(line);
                    }

                    cfg.close();
                    
                    std::ofstream cfgO(RETROARCH_CFG);

                    for (std::string l : raCfgFileText)
                    {
                        cfgO << l << std::endl;
                    }

                    cfgO.close();

                    reloadTexts();
                }
            }
        }
        break;
    default:
        break;
    }
    return {-2, 0};
}