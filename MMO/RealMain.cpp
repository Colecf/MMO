//
//  RealMain.cpp
//  MMO
//
//  Created by Cole Faust on 12/19/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2_image/SDL_image.h>
#include "ResourcePath.h"
#include "RealMain.h"
#include "RenderManager.h"



int realMain(int argc, char * arg[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init" << std::endl;
        return -1;
    }
    
    std::cout << getResourcePath() << std::endl;
    
    RenderManager *render = RenderManager::getInstance();
    render->init(SDL_CreateWindow("SDL 2 window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           640, 480,SDL_WINDOW_SHOWN));
    SDL_Surface *tileset = render->loadSurface("tileset.png");
    std::cout << SDL_BlitSurface(tileset, NULL, render->screen, NULL) << std::endl;
    render->updateScreen();
    
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }
    
    render->cleanup();
    SDL_Quit();
    return 0;
}
