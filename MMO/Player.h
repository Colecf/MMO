//
//  Player.h
//  MMO
//
//  Created by Cole Faust on 1/12/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__Player__
#define __MMO__Player__

#include "SDL2_net.h"
#include <string>

#define SHOOTCOOLDOWNMAX 50

class Player
{
public:
    Player();
    ~Player();
    void update();
    void setSocket(TCPsocket newSocket);
    void move(int dx, int dy);
    bool shootTowards(int sx, int sy);
    void sendNetworkMessage(std::string message);
    std::string connectToServer(std::string server);
    std::string clientNetworkUpdate();
    std::string networkMessage;
    TCPsocket socket;
    static SDLNet_SocketSet PlayerSSet;
    int x, y;
    std::string name;
    int gameClass;
    int shootCooldown;
};

#endif /* defined(__MMO__Player__) */
