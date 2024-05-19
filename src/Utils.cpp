/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:13:53 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/18 15:38:23 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

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

bool	Server::userExists(std::vector<User> userlist, std::string nickname)
{
	for (size_t i = 0; i < userlist.size(); i++)
	{
		if (userlist[i].getNick().compare(nickname) == 0)
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

void	Server::sendMsgUsersList(std::vector<User> users, std::string str)
{
	for (size_t i = 0; i < users.size(); i++)
	{
		sendMessage(users[i].getFd(), str);
	}
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
	sendMsgUsersList(userList, RPL_ENDOFNAMES(user.getNick(), channel.getName()));
}

bool Server::maskMacht(std::string mask, std::string name)
{
	size_t pos = 0;
	pos = mask.find("*");
	std::string	sub;
	if (pos <= mask.size() && (mask.size()-1) <= name.size())
	{
		if (pos == 0)
		{
			mask.erase(mask.begin());
			sub = name.substr((name.size() - mask.size()), (mask.size()));
			if (!sub.compare(mask))
				return (true);
		}
		else if (pos == mask.size()-1)
		{
			mask.erase(mask.end()-1);
			sub = name.substr(0, mask.size());
			if (!sub.compare(mask))
				return (true);
		}
		else
		{
			std::string maskIni = mask.substr(0, pos);
			std::string maskEnd = mask.substr(pos + 1, mask.size() -1);
			sub = name.substr(0, maskIni.size());
			if (!sub.compare(maskIni))
			{
				sub = name.substr((name.size() - maskEnd.size()), (maskEnd.size()));
				if (!sub.compare(maskEnd))
					return (true);
			}
		}
	}
	else if (!name.compare(mask))
		return (true);
	return (false);
}