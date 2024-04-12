/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:32:29 by aoropeza          #+#    #+#             */
/*   Updated: 2024/04/12 18:45:48 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void	Server::createNewChannel(std::string name, User user)
{
	name.erase(name.begin() + name.length() - 2, name.end());
	std::cout << "[" << RED << name << WHI << "]" << std::endl;
	Channel	channel(name, user);
	std::string	rpl = RPL_NOTOPIC(user.getNick(), channel.getName());
	_channels.push_back(channel);

	std::string msg = ":aoropeza!aoropeza@" + user.getIpAdd() + " JOIN :" + channel.getName();
	msg.append("\r\n");
	//std::string msg = RPL_JOIN(user.getNick() + "!" + user.getUsername() + "@" + user.getIpAdd(), channel.getName());

	send(user.getFd(), msg.c_str(), msg.length(), 0);
	send(user.getFd(), rpl.c_str(), rpl.length(), 0);
	sendUserList(channel, user);
	std::cout << GRE << "Channel [" << name << "] succesfully created" << WHI << std::endl;
}

void	Server::joinNewChannel(std::string name, User user)
{
	std::string	rpl;
	
	if (!channelExists(name))
		createNewChannel(name, user);
	else
	{
		Channel channel(searchChannel(name));
		std::string msg = ":aoropeza!aoropeza@" + user.getIpAdd() + " JOIN :" + channel.getName();
		msg.append("\r\n");
		//std::string msg = RPL_JOIN(user.getNick() + "!" + user.getUsername() + "@" + user.getIpAdd(), channel.getName());
		if (channel.getHasTopic())
			rpl = RPL_TOPIC(user.getNick(), channel.getName(), channel.getTopic());
		else
			rpl = RPL_NOTOPIC(user.getNick(), channel.getName());
		send(user.getFd(), rpl.c_str(), rpl.length(), 0);
		std::cout << CYA << "User [" << user.getFd() << "] joined the channel [" << channel.getName() << "]" << WHI << std::endl;
	}
}

User	Server::searchUser(int fd)
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (_users[i].getFd() == fd)
			return (_users[i]);
	}
	throw std::exception();
}

Channel	Server::searchChannel(std::string name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName().compare(name) == 0)
			return (_channels[i]);
	}
	throw std::exception();

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
	std::vector<User>	userlist(channel.getUsers());

	
	for (size_t i = 0; i < userlist.size(); i++)
	{
		list.append(userlist[i].getNick() + " ");	// cambiar por _nick
	}
	rpl = RPL_NAMREPLY(user.getNick(), channel.getName(), list);
	send(user.getFd(), rpl.c_str(), rpl.length(), 0);

}