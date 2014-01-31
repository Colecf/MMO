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
    
    RenderManager *render = RenderManager::getInstance();
    render->init(SDL_CreateWindow("SDL 2 window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           640, 480,SDL_WINDOW_SHOWN));
    ColeTileset tileset(getResourcePath()+"tileset");
    SDL_RenderSetScale(render->renderer, 3, 3);
    
    if(SDLNet_Init() == -1)
    {
        std::cout << "ERROR SDLNet_Init: " << SDLNet_GetError() << std::endl;
        return 1;
    }
    
    IPaddress ip;
    if(SDLNet_ResolveHost(&ip,"127.0.0.1",9999)==-1) {
        std::cout << "ERROR SDLNet_ResolveHost " << SDLNet_GetError() << std::endl;
        return 1;
    }
    Player::PlayerSSet = SDLNet_AllocSocketSet(1);
    Player p;
    p.setSocket(SDLNet_TCP_Open(&ip));
    if(!p.socket) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(2);
    }
    
    MainMenu *menu = new MainMenu();
    
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_0)
            {
                
                std::string message = "hello;";
                char *msg = (char*)message.c_str();
                std::cout << "Sending " << msg << std::endl;
                //For some reason an extra 2 garbage characters
                //are attached if you don't do the -2
                SDLNet_TCP_Send(p.socket, msg, sizeof(msg)-2);
            }
        }
        
        while(SDLNet_CheckSockets(Player::PlayerSSet, 0) >= 1)
        {
            if (SDLNet_SocketReady(p.socket))
            {
                char letter;
                if(SDLNet_TCP_Recv(p.socket, &letter, 1) < 1)
                {
                    std::cout << "Lost Connection to server!" << std::endl;
                    quit = true;
                    break;
                }
                p.networkMessage += letter;
                if (letter == ';')
                    std::cout << p.networkMessage;
            }
        }
        
        render->clearScreen();
        for(int x=0; x<100; x++)
        {
            tileset.renderTile((x%10)*16, (x/10)*16, "grass2");
        }
        
        menu->render();
        render->updateScreen();
    }
    
    render->cleanup();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
