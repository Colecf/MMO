//
//  main.cpp
//  MMO_server
//
//  Created by Cole Faust on 12/28/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2_net/SDL_net.h>
#include "Player.h"

bool run = true;

void handleMessage(Player* p)
{
    std::cout << p->networkMessage << std::endl;
    p->networkMessage = "";
}

int keyboardThread(void* data)
{
    std::string line;
    while (run)
    {
        getline(std::cin, line);
        if (line == "q" || line == "quit" || line == "exit")
        {
            run = false;
        }
    }
    return 0;
}

int main(int argc, const char * argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }
    if(SDLNet_Init() == -1)
    {
        std::cout << "ERROR SDLNet_Init: " << SDLNet_GetError() << std::endl;
        return 1;
    }
    
    IPaddress ip;
    if(SDLNet_ResolveHost(&ip,NULL,9999)==-1) {
        std::cout << "ERROR SDLNet_ResolveHost " << SDLNet_GetError() << std::endl;
        return 1;
    }
    
    TCPsocket serverSocket = SDLNet_TCP_Open(&ip);
    if(!serverSocket) {
        std::cout << "ERROR SDLNet_TCP_Open " << SDLNet_GetError() << std::endl;
        return 1;
    }
    Player::PlayerSSet = SDLNet_AllocSocketSet(100);
    
    SDL_Thread *keythread = SDL_CreateThread(keyboardThread, "keyboardThread", (void *)NULL);
    std::list<Player*> clients;
    
    std::cout << "Start" << std::endl;
    
    int loop = 0;
    
    while (run)
    {
        TCPsocket newClient = SDLNet_TCP_Accept(serverSocket);
        if (newClient)
        {
            Player* p = new Player;
            p->setSocket(newClient);
            clients.push_back(p);
            std::cout << "New Player!" << std::endl;
        }
        while(SDLNet_CheckSockets(Player::PlayerSSet, 0) >= 1)
        {
            std::list<Player*>::iterator it;
            for (it = clients.begin(); it != clients.end(); it++)
            {
                if (SDLNet_SocketReady((*it)->socket))
                {
                    char letter;
                    if(SDLNet_TCP_Recv((*it)->socket, &letter, 1) < 1)
                    {
                        std::cout << "Player disconnecting!" << std::endl;
                        delete *it;
                        clients.erase(it);
                        continue;
                    }
                    (*it)->networkMessage += letter;
                    if (letter == ';')
                        handleMessage((*it));
                }
            }
        }
        //std::cout << "Loop " << loop << std::endl;
        SDL_Delay(50);
        loop++;
    }
    
    std::list<Player*>::iterator it;
    for (it = clients.begin(); it != clients.end(); it++) {
        delete *it;
        *it = NULL;
    }
    
    int ret;
    SDL_WaitThread(keythread, &ret);
    SDLNet_TCP_Close(serverSocket);
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}

