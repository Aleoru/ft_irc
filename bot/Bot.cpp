/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 22:54:09 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/25 19:39:38 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Bot.hpp"

Bot::Bot(){}

Bot::Bot(std::string ip, int port, std::string pass, std::string nick)
: _ipAdd(ip), _pass(pass), _nickname(nick), _port(port)
{
    _user = "bot";
	_dialogues.reserve(NUMPHRASES);
	_dialogues.resize(NUMPHRASES);
	_dialogues[0] = "Claro que si ";
	_dialogues[1] =	"Me cuesta creerlo ";
	_dialogues[2] =	"Puede ser ";
	_dialogues[3] =	"Parece ser que no ";
	_dialogues[4] =	"No estaba atento, lo siento mucho ";
	_dialogues[5] =	"Es poco original sinceramente ";
	_dialogues[6] =	"Muchos opinan lo mismo ";
	_dialogues[7] =	"Hace un bonito día ";
	_dialogues[8] =	"...siii ";
	_dialogues[9] =	"Me esta doliendo la cabeza ";
	_dialogues[10] = "Me da pereza... ";
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

void    Bot::working()
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
		//recived = (":nick!user@host PRIVMSG #General :message sdfasd adsfasdf sd asdf \r\n");
		parser(recived);
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

static std::vector<std::string> split(const std::string str, char delimiter)
{
	std::vector<std::string> split;
	std::string token;
	std::istringstream tokenStream(str);
	while (std::getline(tokenStream, token, delimiter))
	{
		split.push_back(token);
	}
	return (split);
}

void		Bot::parser(std::string reply)
{
	std::vector<std::string> cmd = split(reply, ' ');
	//for (size_t i = 0; i < cmd.size(); i++)
	//	std::cout<<"str["<<i<<"]: "<<cmd[i]<<std::endl;
	//std::cout<<"----------------------------"<<std::endl;
	//cmd[1] nombre del comando que buscamos
	if (!cmd[1].compare("PRIVMSG"))
	{
		std::cout<<"PRIVMSG"<<std::endl;
		//tartar el mensaje de la sala
		std::string nickname = findNickname(cmd[0]);
		std::cout<<"nick: "<<nickname<<std::endl;
		std::string channel = cmd[2];
		std::cout<<"channel: "<<cmd[2]<<std::endl;
		std::string message = joinMessage(cmd, 3);
		std::cout<<"message: "<<message<<std::endl;
		srand(time(NULL));
    	int random = rand() % _dialogues.size();
		std::string response = _dialogues[random] + nickname;
		std::cout<<message<<std::endl;
		std::string send ="PRIVMSG " + cmd[2] + " :" + response+ "\r\n";
		std::cout<<send<<std::endl;
		sendMessage(_ircSock, "PRIVMSG " + cmd[2] + " :" + response+ "\r\n");
	}
}

// RPL_PRIVMSG(source, target, message) ":" + source + " PRIVMSG " + target + " :" + message + "\r\n"
// source = nickname!username@host
std::string	Bot::findNickname(std::string str)
{
	std::string nickname;
	str.erase(str.begin());
	size_t pos = str.find("!");
	if (pos <= str.size())
		nickname = str.substr(0, pos);
	return (nickname);
}

std::string Bot::joinMessage(std::vector<std::string> cmd, int pos)
{
	std::string message = cmd[pos];
	message.erase(message.begin());
	for (size_t i = pos +1; i < cmd.size(); i++)
	{
		message.append(cmd[i]);
		if (i + 1 < cmd.size())
			message.append(" ");
	}
	return (message);
}