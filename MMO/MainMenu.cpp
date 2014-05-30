//
//  MainMenu.cpp
//  MMO
//
//  Created by Cole Faust on 1/24/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "MainMenu.h"
#include "ColeTexture.h"
#include "ColeFontManager.h"
#include "NetworkManager.h"
#include "GameScene.h"
#include <memory>

MainMenu::MainMenu()
{
    std::shared_ptr<ColeTexture> title = ColeFontManager::getInstance()->createTextTexture("Cole's MMO Game!");
    title->x = (640/3/2)-(title->getWidth()/2);
    std::cout << title->x << std::endl;
    addChild(title);
    serverIPBox = std::make_shared<ColeTextBox>(100);
    serverIPBox->x = 10;
    serverIPBox->y = 20;
    addChild(serverIPBox);
}

void MainMenu::onEvent(SDL_Event *e)
{
    ColeScene::onEvent(e);
    
    if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN && serverIPBox->containedText.length()>0)
    {
        std::cout << "Enter" << std::endl;
        serverIPBox->enabled = false;
        std::string result = NetworkManager::getInstance()->connect(serverIPBox->containedText);
        serverIPBox->enabled = true;
        std::cout << result << std::endl;
        if (result != "")
        {
            std::shared_ptr<ColeTexture> errormsg = ColeFontManager::getInstance()->createTextTexture(result);
            errormsg->x = serverIPBox->x;
            errormsg->y = serverIPBox->y - 50;
            addChild(errormsg);
        } else {
            ColeScene::currentScene = std::make_shared<GameScene>();
        }
    }
}