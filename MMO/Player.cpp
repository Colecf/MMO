//
//  Player.cpp
//  MMO
//
//  Created by Cole Faust on 1/12/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "Player.h"
#include <iostream>

void Player::sendNetworkMessage(std::string message)
{
    SDLNet_TCP_Send(socket, message.c_str(), (int)strlen(message.c_str()));
}

//std::string Player::networkMessage;
//TCPsocket Player::socket;
SDLNet_SocketSet Player::PlayerSSet;

Player::Player()
{
    networkMessage = "";
    socket = NULL;
    x = y = 0;
}

Player::~Player()
{
    std::cout << "Destroying Player!" << std::endl;
    if (socket != NULL)
    {
        SDLNet_DelSocket(PlayerSSet, (SDLNet_GenericSocket)socket);
        SDLNet_TCP_Close(socket);
    }
}

void Player::setSocket(TCPsocket newSocket)
{
    socket = newSocket;
    SDLNet_AddSocket(PlayerSSet, (SDLNet_GenericSocket)socket);
}

void Player::move(int dx, int dy)
{
    x += dx;
    y += dy;
    
    std::string message = "move:"+std::to_string(x)+","+std::to_string(y)+";";
    sendNetworkMessage(message);
}