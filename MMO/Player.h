//
//  Player.h
//  MMO
//
//  Created by Cole Faust on 1/12/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__Player__
#define __MMO__Player__

#include <SDL2_net/SDL_net.h>
#include <string>

class Player
{
public:
    Player();
    ~Player();
    void setSocket(TCPsocket newSocket);
    std::string networkMessage;
    TCPsocket socket;
    static SDLNet_SocketSet PlayerSSet;
};

#endif /* defined(__MMO__Player__) */
