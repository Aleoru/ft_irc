/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:32:29 by aoropeza          #+#    #+#             */
/*   Updated: 2024/04/25 19:33:50 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void	Server::createNewChannel(std::string name, User *user)
{
	Channel	channel(name, *user);

	_channels.push_back(channel);
	sendMessage(user->getFd(), RPL_JOIN(getUserSource(user), channel.getName()));
	sendMessage(user->getFd(), RPL_NOTOPIC(user->getNick(), channel.getName()));
	sendUserList(channel, *user);
	std::cout << GRE << "Channel [" << name << "] succesfully created" << WHI << std::endl;
}

void	Server::joinNewChannel(std::string name, User *user)
{
	if (!channelExists(name))
		createNewChannel(name, user);
	else
	{
		Channel *channel = searchChannel(name);
		channel->addUserToList(*user);
		sendMessage(user->getFd(), RPL_JOIN(getUserSource(user), channel->getName()));
		if (channel->getHasTopic())
			sendMessage(user->getFd(), (user->getNick(), channel->getName(), channel->getTopic()));
		else
			sendMessage(user->getFd(), RPL_NOTOPIC(user->getNick(), channel->getName()));
		sendUserList(*channel, *user);
		std::cout << CYA << "User [" << user->getFd() << "] joined the channel [" << channel->getName() << "]" << WHI << std::endl;
	}
}

User	*Server::searchUser(int fd)
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (_users[i].getFd() == fd)
			return (&_users[i]);
	}
	return NULL;
}

User	*Server::searchUser(std::string nick)
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (_users[i].getNick().compare(nick) == 0)
			return (&_users[i]);
	}
	return NULL;
}

Channel	*Server::searchChannel(std::string name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName().compare(name) == 0)
			return (&_channels[i]);
	}
	return NULL;
}

bool	Server::userExists(std::string nick)
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (_users[i].getNick().compare(nick) == 0)
			return (true);
	}
	return (false);
}

bool	Server::channelExists(std::string name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName().compare(name) == 0)
			return (true);
	}
	return (false);

}

void	Server::sendUserList(Channel channel, User user)
{
	std::string			rpl;
	std::string			list;
	std::vector<User>	userList(channel.getUsers());
	std::vector<User>	operatorsList(channel.getOperators());

	for (size_t i = 0; i < operatorsList.size(); i++)
	{
		list.append("@" + operatorsList[i].getNick() + " ");
	}
	for (size_t i = 0; i < userList.size(); i++)
	{
		if (!channel.operatorExists(userList[i].getNick()))
			list.append(userList[i].getNick() + " ");
	}
	sendMsgUsersList(userList, RPL_NAMREPLY(user.getNick(), channel.getName(), list));
	sendMsgUsersList(userList, RPL_ENDOFNAMES(user.getNick(), channel.getName()));

}