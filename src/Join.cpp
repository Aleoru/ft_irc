/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:32:29 by aoropeza          #+#    #+#             */
/*   Updated: 2024/04/29 20:30:18 by aoropeza         ###   ########.fr       */
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
		if (channel->userExists(user->getNick()))
			return ;
		channel->addUserToList(*user);
		sendMsgUsersList(channel->getUsers(), RPL_JOIN(getUserSource(user), channel->getName()));
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

std::string	Server::strUsersChannel(std::string channelName)
{
	std::vector<std::string> users;
	std::vector<std::string> operators;
	std::vector<User> vecUsers = searchChannel(channelName)->getUsers();
	std::vector<User> vecOperators = searchChannel(channelName)->getOperators();
	for (size_t i = 0; i < vecUsers.size(); i++)
		users.push_back(vecUsers[i].getNick());	
	for (size_t i = 0; i < vecOperators.size(); i++)
		operators.push_back(vecOperators[i].getNick());
	std::vector<std::string> copy;
	std::string str;
	std::vector<std::string>::iterator res;
	for (size_t i = 0; i < users.size(); i++)
	{
		res = std::find(operators.begin(), operators.end(), users[i]);
		if (*res == users[i])
			copy.push_back("@" + users[i]);
		else
			copy.push_back(users[i]);
	}
	std::sort(copy.begin(), copy.end());
	for (size_t i = 0; i < copy.size(); i++)
	{
		str.append(copy[i]);
		if (i + 1 < copy.size())
			str.append(" ");
	}
	return (str);
}

void	Server::sendUserList(Channel channel, User user)
{
	std::string			rpl;
	std::string			list;
	std::vector<User>	userList(channel.getUsers());
	std::vector<User>	operatorsList(channel.getOperators());

	std::sort(operatorsList.begin(), operatorsList.end());
	std::sort(userList.begin(), userList.end());
	for (size_t i = 0; i < operatorsList.size(); i++)
	{
		list.append("@" + operatorsList[i].getNick() + " ");
	}
	for (size_t i = 0; i < userList.size(); i++)
	{
		if (!channel.operatorExists(userList[i].getNick()))
			list.append(userList[i].getNick() + " ");
	}
	std::cout << CYA << list << std::endl;
	sendMsgUsersList(userList, RPL_NAMREPLY(user.getNick(), channel.getName(), list));
	//sendMsgUsersList(userList, RPL_NAMREPLY(user.getNick(), channel.getName(), strUsersChannel(channel.getName())));
	sendMsgUsersList(userList, RPL_ENDOFNAMES(user.getNick(), channel.getName()));

}