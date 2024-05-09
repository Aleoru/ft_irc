/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:55:18 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/09 19:39:18 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/Channel.hpp"
#include "../inc/replies.hpp"
#include "../inc/Server.hpp"
#include <algorithm>

/*
El topic es simple, tenemos que verificar varias cositas:
1-Que el string que viene por parametro no está vacío, sino, devolvemos el topic actual del canal
2-Que esté la flag o no activada
*/

//poner sendMsgUsersList(std::vector<User> users, std::string str); para todos los usuarios
void Server::changeTopic(std::vector<std::string> cmd, int fd)
{
	std::string channel_name = cmd[1];
	std::string newTopic;

	Channel *canal = searchChannel(channel_name);

	if (!channelExists(cmd[1]))
	{
		return ;
	}
	for (size_t i = 2; i < cmd.size(); ++i)
	{
		//std::cout << cmd.size();
		newTopic.append(cmd[i]);
		if (i < cmd.size())
			newTopic.append(" ");
	}
	if (newTopic.length() < 1 || cmd.size() < 2) //Aquí completamos la primera comprobación y actuamos en base al resultado
	{
		std::cout << "Topic guardado:" << canal->getTopic();
		if (canal->getHasTopic()) //si no hay topic, imprimimos solo un salto de línea
			sendMessage(fd, RPL_NOTOPIC(searchUser(fd)->getNick(), canal->getName()));
		else
			sendMessage(fd, RPL_TOPIC(searchUser(fd)->getNick(), canal->getName(), canal->getTopic()));
	}
	else if (canal->getSetTopic() == true) //si la flag +t está activada, además ya hemos verificado que la string de topic no esté vacía
	{
		std::vector<User> users_ch = canal->getUsers();
		std::vector<User> ops = canal->getOperators();
		if (canal->operatorExists(searchUser(fd)->getNick()) == true) //cambiar el topic
		{
			canal->setTopic(newTopic);
			canal->setHasTopic(true);
			sendMsgUsersList(canal->getUsers(), RPL_TOPIC(searchUser(fd)->getNick(), canal->getName(), newTopic));
		}
		else
			sendMessage(fd, ERR_CHANOPRIVSNEEDED(searchUser(fd)->getNick(), canal->getName()));
	}
	else //Si hay topic y la flag está desactivada cambiar el topic y listo
	{
		canal->setTopic(newTopic);
		canal->setHasTopic(true);
		sendMsgUsersList(canal->getUsers(), RPL_TOPIC(searchUser(fd)->getNick(), canal->getName(), newTopic));
	}
}
