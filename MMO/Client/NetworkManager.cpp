//
//  NetworkManager.cpp
//  MMO
//
//  Created by Cole Faust on 2/11/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "NetworkManager.h"

std::string NetworkManager::connect(std::string server)
{
    if(SDLNet_ResolveHost(&serverIP, server.c_str(), 9999)==-1) {
        std::cout << "ERROR SDLNet_ResolveHost " << SDLNet_GetError() << std::endl;
        return SDLNet_GetError();
    }
    
    p->setSocket(SDLNet_TCP_Open(&serverIP));
    if(!p->socket) {
        std::cout << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
        return SDLNet_GetError();
    }
    
    return "";
}

void NetworkManager::setPlayer(std::shared_ptr<Player> newP) { p = newP; }

bool NetworkManager::update()
{
    if (!p->socket)
        return true;
    
    while(SDLNet_CheckSockets(Player::PlayerSSet, 0) >= 1)
    {
        if (SDLNet_SocketReady(p->socket))
        {
            char letter;
            if(SDLNet_TCP_Recv(p->socket, &letter, 1) < 1)
            {
                std::cout << "Lost Connection to server!" << std::endl;
                return false;
            }
            p->networkMessage += letter;
            if (letter == ';')
                std::cout << p->networkMessage << std::endl;
        }
    }
    return true;
}