/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:55:18 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/27 04:40:57 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void Server::changeTopic(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() < 2)
	{
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), cmd[0], "You must specify the channel name."));
		return ;
	}
	
	std::string channel_name = cmd[1];
	std::string newTopic;

	Channel *canal = searchChannel(channel_name);

	if (!channelExists(cmd[1]))
		return ;
	for (size_t i = 2; i < cmd.size(); ++i)
	{
		newTopic.append(cmd[i]);
		if (i < cmd.size())
			newTopic.append(" ");
	}
	if (newTopic.length() < 1 || cmd.size() < 2) 
	{
		std::cout << "Topic guardado:" << canal->getTopic();
		if (canal->getHasTopic())
			sendMessage(fd, RPL_TOPIC(searchUser(fd)->getNick(), canal->getName(), canal->getTopic()));
		else
			sendMessage(fd, RPL_NOTOPIC(searchUser(fd)->getNick(), canal->getName()));
		return ;
	}
	if (canal->getSetTopic() == true) 
	{
		std::vector<User> users_ch = canal->getUsers();
		std::vector<User> ops = canal->getOperators();
		if (canal->operatorExists(searchUser(fd)->getNick()) == true) 
		{
			canal->setTopic(newTopic);
			canal->setHasTopic(true);
			sendMsgUsersList(canal->getUsers(), RPL_TOPIC(searchUser(fd)->getNick(), canal->getName(), newTopic));
		}
		else
			sendMessage(fd, ERR_CHANOPRIVSNEEDED(searchUser(fd)->getNick(), canal->getName()));
	}
	else
	{
		canal->setTopic(newTopic);
		canal->setHasTopic(true);
		sendMsgUsersList(canal->getUsers(), RPL_TOPIC(searchUser(fd)->getNick(), canal->getName(), newTopic));
	}
}
