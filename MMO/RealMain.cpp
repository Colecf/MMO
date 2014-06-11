//
//  RealMain.cpp
//  MMO
//
//  Created by Cole Faust on 12/19/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "ResourcePath.h"
#include "RealMain.h"
#include "RenderManager.h"
#include "ColeTexture.h"
#include "ColeTileset.h"
#include "Player.h"
#include "ColeFontManager.h"
#include "MainMenu.h"
#include "ColeScene.h"
#include "FPSCounter.h"
#include "NetworkManager.h"


int realMain(int argc, char * arg[])
{
    ColeScene::penX = 0;
    ColeScene::penY = 0;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init" << std::endl;
        return 1;
    }
    if (TTF_Init()==-1)
    {
        std::cout << "ERROR TTF_Init()" << TTF_GetError() << std::endl;
        return 1;
    }
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if((initted&flags) != flags)
    {
        std::cout << "Error initing SDL_Image! " << IMG_GetError() << std::endl;
        return 2;
    }
    if(SDLNet_Init() == -1)
    {
        std::cout << "ERROR SDLNet_Init: " << SDLNet_GetError() << std::endl;
        return 1;
    }
    
    RenderManager *render = RenderManager::getInstance();
    render->init(SDL_CreateWindow("SDL 2 window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           640, 480,SDL_WINDOW_SHOWN));
    ColeTileset::loadedSet = std::make_shared<ColeTileset>(getResourcePath()+"tileset");
    render->scaleRenderer(3, 3);

    Player::PlayerSSet = SDLNet_AllocSocketSet(1);
    
    ColeScene::currentScene = std::make_shared<MainMenu>();
    
    FPSCounter fps;
    SDL_Delay(50);
    fps.nextFrame();
    
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        fps.limitTo(60);
        fps.nextFrame();
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                e.button.x /= render->getScaleX();
                e.button.y /= render->getScaleY();
            }
            if (e.type == SDL_QUIT)
            {
                quit = true;
            } else {
                ColeScene::currentScene->onEvent(&e);
            }
        }
        
        render->clearScreen();
        for(int x=0; x<100; x++)
        {
            ColeTileset::loadedSet->renderTile((x%10)*16, (x/10)*16, "grass2");
        }
        
        ColeScene::currentScene->render();
        render->updateScreen();
    }
    
    render->cleanup();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
