#include "profileScreen.h"
#include "../vars.h"

void profileScreen::loadTexts()
{
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

    //Carrega teclado
    int kbdPosX = 14;
    int kbdPosY = 154;
    //letras minusculas
    for (std::vector<std::string> kbd : keyboardLowerCase)
    {
        kbdPosX = 14;
        for (std::string key : kbd)
        {
            keyboardLowerCaseText.push_back(new progTexts(key, SDL_Color {0, 255, 60}, kbdPosX, kbdPosY, gFont, gRenderer));
            kbdPosX += 20;
        }
        kbdPosY += 20;
    }
    //letras maiusculas
    kbdPosY = 154;
    for (std::vector<std::string> kbd : keyboardUpperCase)
    {
        kbdPosX = 14;
        for (std::string key : kbd)
        {
            keyboardUpperCaseText.push_back(new progTexts(key, SDL_Color {0, 255, 60}, kbdPosX, kbdPosY, gFont, gRenderer));
            kbdPosX += 20;
        }
        kbdPosY += 20;
    }
    //Simbolos
    kbdPosY = 154;
    for (std::vector<std::string> kbd : keyboardNumSymbols)
    {
        kbdPosX = 14;
        for (std::string key : kbd)
        {
            keyboardNumSymbolsText.push_back(new progTexts(key, SDL_Color {0, 255, 60}, kbdPosX, kbdPosY, gFont, gRenderer));
            kbdPosX += 20;
        }
        kbdPosY += 20;
    }
}

void profileScreen::render()
{
    for (auto &text : sdlTextList)
    {
        text->renderText();
    }
    selector->renderText();

    //renderiza o teclado
    if (keyboardEnabled)
    {
        if (keyboardMode == 0)
        {
            for (auto &text : keyboardLowerCaseText)
            {
                text->renderText();
            }
        }
        else if (keyboardMode == 1)
        {
            for (auto &text : keyboardUpperCaseText)
            {
                text->renderText();
            }
        }
        else
        {
            for (auto &text : keyboardNumSymbolsText)
            {
                text->renderText();
            }
        }
        drawKeyboardSelector();
    }
}

std::vector<int> profileScreen::keyPressed(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_DOWN:
        {
            if (!keyboardEnabled)
            {
                selection++;
                if (selection > menuItems) selection = 0;
                selector->posY = 54 + 20 * selection;
            }
            else
            {
                kbdSelectorLine++;

                if (kbdSelectorLine > kbdSelectorLineMax) kbdSelectorLine = kbdSelectorLineMax;
                else kbdSelectorPosY += 20;

                if (keyboardMode == 0) kbdSelectorColMax = keyboardLowerCase[kbdSelectorLine].size()-1;
                else if (keyboardMode == 1) kbdSelectorColMax = keyboardUpperCase[kbdSelectorLine].size()-1;
                else if (keyboardMode == 2) kbdSelectorColMax = keyboardNumSymbols[kbdSelectorLine].size()-1;

                if (kbdSelectorCol > kbdSelectorColMax)
                {
                    kbdSelectorPosX = 14 + kbdSelectorColMax * 20;
                    kbdSelectorCol = kbdSelectorColMax;
                } 
                
            }
        }
        break;
    case SDLK_UP:
        {
            if (!keyboardEnabled)
            {
                selection--;
                if (selection < 0) selection = menuItems;
                selector->posY = 54 + 20 * selection;
            }
            else
            {
                kbdSelectorLine--;

                if (kbdSelectorLine < 0) kbdSelectorLine = 0;
                else kbdSelectorPosY -= 20;

                if (keyboardMode == 0) kbdSelectorColMax = keyboardLowerCase[kbdSelectorLine].size()-1;
                else if (keyboardMode == 1) kbdSelectorColMax = keyboardUpperCase[kbdSelectorLine].size()-1;
                else if (keyboardMode == 2) kbdSelectorColMax = keyboardNumSymbols[kbdSelectorLine].size()-1;
                
                if (kbdSelectorCol > kbdSelectorColMax)
                {
                    kbdSelectorPosX = 14 + kbdSelectorColMax * 20;
                    kbdSelectorCol = kbdSelectorColMax;
                } 
                
            }
        }
        break;
    case SDLK_LEFT:
        {
            if (keyboardEnabled)
            {
                kbdSelectorCol--;
                if (kbdSelectorCol < 0) kbdSelectorCol = 0;
                else kbdSelectorPosX -= 20;
            }
        }
        break;
    case SDLK_RIGHT:
        {
            if (keyboardEnabled)
            {
                kbdSelectorCol++;
                if (kbdSelectorCol > kbdSelectorColMax) kbdSelectorCol = kbdSelectorColMax;
                else kbdSelectorPosX += 20;
            }
        }
        break;
    case SDLK_a:
        {
            keyboardMode++;
            if (keyboardMode == 3) keyboardMode = 0;
            
            if (keyboardMode == 0)
            {
                kbdSelectorLineMax = keyboardLowerCase.size()-3;
                if (kbdSelectorLine > kbdSelectorLineMax)
                {
                    kbdSelectorPosY = 154 + kbdSelectorLineMax * 20;
                    kbdSelectorLine = kbdSelectorLineMax;
                }

                kbdSelectorColMax = keyboardLowerCase[kbdSelectorLine].size()-1;
                if (kbdSelectorCol > kbdSelectorColMax)
                {
                    kbdSelectorPosX = 14 + kbdSelectorColMax * 20;
                    kbdSelectorCol = kbdSelectorColMax;
                }
                
            }
            else if (keyboardMode == 1)
            {
                kbdSelectorLineMax = keyboardUpperCase.size()-3;
                if (kbdSelectorLine > kbdSelectorLineMax)
                {
                    kbdSelectorPosY = 154 + kbdSelectorLineMax * 20;
                    kbdSelectorLine = kbdSelectorLineMax;
                }
                
                kbdSelectorColMax = keyboardUpperCase[kbdSelectorLine].size()-1;
                if (kbdSelectorCol > kbdSelectorColMax)
                {
                    kbdSelectorPosX = 14 + kbdSelectorColMax * 20;
                    kbdSelectorCol = kbdSelectorColMax;
                }
            }
            else if (keyboardMode == 2)
            {
                kbdSelectorLineMax = keyboardNumSymbols.size()-3;
                if (kbdSelectorLine > kbdSelectorLineMax)
                {
                    kbdSelectorPosY = 154 + kbdSelectorLineMax * 20;
                    kbdSelectorLine = kbdSelectorLineMax;
                }

                kbdSelectorColMax = keyboardNumSymbols[kbdSelectorLine].size()-1;                
                if (kbdSelectorCol > kbdSelectorColMax)
                {
                    kbdSelectorPosX = 14 + kbdSelectorColMax * 20;
                    kbdSelectorCol = kbdSelectorColMax;
                }
                
            }
        }
        break;
    case SDLK_z:
        {
            if (selection == 1)
            {
                if (username.size() > 0)
                {
                    username.erase(username.size()-1);
                    menuTexts[1] = "Username: " + username;
                    free(sdlTextList[3]);
                    sdlTextList[3] = new progTexts(menuTexts[1], SDL_Color {0, 255, 60}, menuTextPos[1][0], menuTextPos[1][1], gFont, gRenderer);
                }
            }
            else if (selection == 2)
            {
                if (password.size() > 0)
                {
                    password.erase(password.size()-1);
                    menuTexts[2] = "Password: " + password;
                    free(sdlTextList[4]);
                    sdlTextList[4] = new progTexts(menuTexts[2], SDL_Color {0, 255, 60}, menuTextPos[2][0], menuTextPos[2][1], gFont, gRenderer);
                }
            }
            else if (selection == 3)
            {
                if (profileName.size() > 0)
                {
                    profileName.erase(profileName.size()-1);
                    menuTexts[3] = "Profile name: " + profileName;
                    free(sdlTextList[5]);
                    sdlTextList[5] = new progTexts(menuTexts[3], SDL_Color {0, 255, 60}, menuTextPos[3][0], menuTextPos[3][1], gFont, gRenderer);
                }
            }
            break;
        }
        break;
    case SDLK_c:
        keyboardEnabled = false;
        break;
    case SDLK_x:
        {
            if (keyboardEnabled)
            {
                if (selection == 1)
                {
                    if (keyboardMode == 0) username.append(keyboardLowerCase[kbdSelectorLine][kbdSelectorCol]);
                    else if (keyboardMode == 1) username.append(keyboardUpperCase[kbdSelectorLine][kbdSelectorCol]);
                    else if (keyboardMode == 2) username.append(keyboardNumSymbols[kbdSelectorLine][kbdSelectorCol]);

                    menuTexts[1] = "Username: " + username;
                    free(sdlTextList[3]);
                    sdlTextList[3] = new progTexts(menuTexts[1], SDL_Color {0, 255, 60}, menuTextPos[1][0], menuTextPos[1][1], gFont, gRenderer);
                }
                else if (selection == 2)
                {
                    if (keyboardMode == 0) password.append(keyboardLowerCase[kbdSelectorLine][kbdSelectorCol]);
                    else if (keyboardMode == 1) password.append(keyboardUpperCase[kbdSelectorLine][kbdSelectorCol]);
                    else if (keyboardMode == 2) password.append(keyboardNumSymbols[kbdSelectorLine][kbdSelectorCol]);

                    menuTexts[2] = "Password: " + password;
                    free(sdlTextList[4]);
                    sdlTextList[4] = new progTexts(menuTexts[2], SDL_Color {0, 255, 60}, menuTextPos[2][0], menuTextPos[2][1], gFont, gRenderer);
                }
                else if (selection == 3)
                {
                    if (keyboardMode == 0) profileName.append(keyboardLowerCase[kbdSelectorLine][kbdSelectorCol]);
                    else if (keyboardMode == 1) profileName.append(keyboardUpperCase[kbdSelectorLine][kbdSelectorCol]);
                    else if (keyboardMode == 2) profileName.append(keyboardNumSymbols[kbdSelectorLine][kbdSelectorCol]);

                    menuTexts[3] = "Profile name: " + profileName;
                    free(sdlTextList[5]);
                    sdlTextList[5] = new progTexts(menuTexts[3], SDL_Color {0, 255, 60}, menuTextPos[3][0], menuTextPos[3][1], gFont, gRenderer);
                }
            }
            if (menuActions[selection][0] == -3)
            {
                if (menuActions[selection][1] == 0) keyboardEnabled = true;
                else {
                    std::string profileIdStr = "";

                    switch (profileId-1)
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

                    (*userDataPtr)[profileIdStr]["username"] = username;
                    (*userDataPtr)[profileIdStr]["password"] = password;
                    (*userDataPtr)[profileIdStr]["name"] = profileName;
                    
                    std::ofstream o("users.json");
                    o <<  std::setw(4) << (*userDataPtr) << std::endl;

                    return menuActions[0];
                }
                
            } else return menuActions[selection];
        }
        break;
    default:
        break;
    }
    return {-2, 0};
}

void profileScreen::setProfileId(int id)
{
    std::string profileIdStr = "";
    profileId = id;

    switch (profileId-1)
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

    std::cout << profileIdStr << std::endl;

    profileName = (*userDataPtr)[profileIdStr]["name"];
    textList[0] = "RetroArch User Manager - Editing Profile " + profileName;
    sdlTextList.clear();

    username = (*userDataPtr)[profileIdStr]["username"];
    password = (*userDataPtr)[profileIdStr]["password"];
    menuTexts[1] = "Username: "+username;
    menuTexts[2] = "Password: "+password;
    menuTexts[3] = "Profile name: "+profileName;
    loadTexts();
}

void profileScreen::drawKeyboardSelector()
{
    int kbdSelPosX = kbdSelectorPosX - 4;
    int kbdSelPosY = kbdSelectorPosY - 4;

    SDL_Rect rect;
    rect.x = kbdSelPosX;
    rect.y = kbdSelPosY;
    rect.w = 20;
    rect.h = 20;

    SDL_SetRenderDrawColor(gRenderer, 0, 255, 100, 255);
    SDL_RenderDrawRect(gRenderer, &rect);
    SDL_SetRenderDrawColor(gRenderer, 14, 14, 14, 255);
}