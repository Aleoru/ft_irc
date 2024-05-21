/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 22:54:09 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/21 05:32:22 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Bot.hpp"

Bot::Bot(){}

Bot::Bot(std::string ip, int port, std::string pass, std::string nick)
: _ipAdd(ip), _port(port), _pass(pass), _nickname(nick)
{
    _user = "bot";
}

Bot::~Bot()
{

}

void    Bot::connectBot()
{
    struct sockaddr_in ircHints;
	_ircSock = socket(AF_INET, SOCK_STREAM, 0);
	if (_ircSock == -1)
	{
        std::cout << "failed to create socket (ircsock)" << std::endl; 
        return ;
    }

    ircHints.sin_family = AF_INET;
    ircHints.sin_port = htons(_port);
	ircHints.sin_addr.s_addr = inet_addr(_ipAdd.c_str());
	
    if(connect(_ircSock, (struct sockaddr*)&ircHints, sizeof(ircHints)) == -1)
	{
        std::cout << "connect failed" << std::endl; 
        return ;
    }
    sendMessage(_ircSock, "PASS " + _pass + "\r\n");
    sendMessage(_ircSock, "NICK " + _nickname + "\r\n");
    sendMessage(_ircSock,"USER " + _user + "\r\n");
    std::cout<<"connected bot "<<_nickname<<std::endl; 
}

void    Bot::workingBot()
{
    std::string recived;
	size_t recivedBytes;

	char buff[1024];
	while(true)
	{
		memset(buff, 0, sizeof(buff));
		recivedBytes = recv(_ircSock, buff, (sizeof(buff) - 1), 0);
		if(recivedBytes <= 0)
			break ;
		recived = buff;
        std::cout<<buff<<std::endl;
    }
}

int     Bot::sendMessage(int fd, const std::string str)
{
	if (send(fd, str.c_str(), str.length(), 0) == -1)
	{
		std::cout << "error sending message" << std::endl;
		return (1);
	}
	return (0);
}