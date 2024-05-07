/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:55:18 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/07 20:26:53 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

/*
El topic es simple, tenemos que verificar varias cositas:
1-Que el string que viene por parametro no está vacío, sino, devolvemos el topic actual del canal
2-Que esté la flag o no activada
*/


void Server::changeTopic(std::vector<std::string> cmd, int fd)
{
	if (!channelExists(cmd[1])) //Esta comprobación es innecesaria según el protocolo pero es posible que de lugar a un error de segmentación o se crea un canal nuevo?
		return ;
	std::string channel_name = cmd[1];
	Channel *canal = searchChannel(channel_name);

	if (cmd.size() == 2)
	{
		std::cout << YEL << "Te digo el topic" << WHI << std::endl;
		if (canal->getHasTopic())
			sendMessage(fd, (searchUser(fd)->getNick(), canal->getName(), canal->getTopic()));
		else
			sendMessage(fd, RPL_NOTOPIC(searchUser(fd)->getNick(), channel_name));
		return ;
	}
	
	std::string newTopic;
	std::vector<User> users_ch = canal->getUsers();
	cmd[2].erase(cmd[2].begin());
	for (size_t i = 2; i < cmd.size(); i++)
	{
		newTopic.append(cmd[i]);
		if (i < cmd.size())
			newTopic.append(" ");
	}
	std::cout << YEL << newTopic << WHI << std::endl;
	if (canal->getSetTopic()) //si la flag +t está activada, además ya hemos verificado que la string de topic no esté vacía
	{
		std::cout << YEL << "Te cambio el Topic solo porque eres mi amigo" << WHI << std::endl;
		std::vector<User> ops = canal->getOperators();
		if (canal->operatorExists(searchUser(fd)->getNick())){ //cambiar el topic
			canal->setTopic(newTopic);
			canal->setHasTopic(true);
			sendMsgUsersList(users_ch, RPL_TOPIC(searchUser(fd)->getNick(), channel_name, newTopic));
		}
		else
			sendMessage(fd, ERR_CHANOPRIVSNEEDED(searchUser(fd)->getNick(), channel_name));
	}
	else
	{
		std::cout << YEL << "Te cambio el Topic" << WHI << std::endl;
		canal->setTopic(newTopic);
		canal->setHasTopic(true);
		sendMsgUsersList(users_ch, RPL_TOPIC(searchUser(fd)->getNick(), channel_name, newTopic));
	} //Si hay topic y la flag está desactivada cambiar el topic y listo
}