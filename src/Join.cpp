/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:32:29 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/18 14:31:27 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void	Server::createNewChannel(std::string name, User *user)
{
	std::cout << CYA << "Creating channel [" << name << "] without pass" << WHI << std::endl;
	if ((name.front() != '&' && name.front() != '#') || name.size() > 200) {
		std::cout << RED << "Invalid channel name" << WHI << std::endl;
		sendMessage(user->getFd(), ERR_BADCHANMASK(user->getNick(), name, "Invalid channel name"));
		return;
	}
	Channel	channel(name, *user);
	_channels.push_back(channel);
	sendMessage(user->getFd(), RPL_JOIN(getUserSource(user), channel.getName()));
	sendMessage(user->getFd(), RPL_NOTOPIC(user->getNick(), channel.getName()));
	sendUserList(channel, *user);
	std::cout << GRE << "Channel [" << name << "] succesfully created" << WHI << std::endl;
}

void	Server::createNewChannel(std::string name, std::string pass, User *user)
{
	std::cout << CYA << "Creating channel [" << name << "] with pass" << WHI << std::endl;
	if ((name.front() != '&' && name.front() != '#') || name.size() > 200) {
		std::cout << RED << "Invalid channel name" << WHI << std::endl;
		sendMessage(user->getFd(), ERR_BADCHANMASK(user->getNick(), name, "Invalid channel name"));
		return;
	}
	Channel	channel(name, pass, *user);
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
		if (userExists(channel->getUsers(), user->getNick()))
			return ;
		if (!channel->getPass().empty())
		{
			sendMessage(user->getFd(), ERR_BADCHANNELKEY(user->getNick(), channel->getName(), "You need a password to access here!!"));
			return ;
		}
		if (channel->getLimit() != NOLIMIT && channel->getUsers().size() + channel->getOperators().size())
		{
			sendMessage(user->getFd(), ERR_CHANNELISFULL(user->getNick(), channel->getName(), "Channel is full"));
			return ;
		}
		std::cout << CYA << "Joining channel [" << name << "] without pass" << WHI << std::endl;
		channel->addUserToList(*user);
		user->setNbChannels(1);
		sendMsgUsersList(channel->getUsers(), RPL_JOIN(getUserSource(user), channel->getName()));
		if (channel->getHasTopic())
			sendMessage(user->getFd(), RPL_TOPIC(user->getNick(), channel->getName(), channel->getTopic()));
		else
			sendMessage(user->getFd(), RPL_NOTOPIC(user->getNick(), channel->getName()));
		sendUserList(*channel, *user);
		std::cout << CYA << "User [" << user->getFd() << "] joined the channel [" << channel->getName() << "]" << WHI << std::endl;
	}
}

void	Server::joinNewChannel(std::string name, std::string pass, User *user)
{
	if (!channelExists(name))
		createNewChannel(name, pass, user);
	else
	{
		Channel *channel = searchChannel(name);
		if (userExists(channel->getUsers(), user->getNick()))
			return;
		if (pass.compare(channel->getPass()))
		{
			sendMessage(user->getFd(), ERR_BADCHANNELKEY(user->getNick(), channel->getName(), "Wrong password, try again, make sure is the correct one."));
			return ;
		}
		if (channel->getLimit() != NOLIMIT && channel->getUsers().size() + channel->getOperators().size())
		{
			sendMessage(user->getFd(), ERR_CHANNELISFULL(user->getNick(), channel->getName(), "Channel is full"));
			return ;
		}
		std::cout << CYA << "Joining channel [" << name << "] with pass" << WHI << std::endl;
		channel->addUserToList(*user);
		user->setNbChannels(1);
		sendMsgUsersList(channel->getUsers(), RPL_JOIN(getUserSource(user), channel->getName()));
		if (channel->getHasTopic())
			sendMessage(user->getFd(), RPL_TOPIC(user->getNick(), channel->getName(), channel->getTopic()));
		else
			sendMessage(user->getFd(), RPL_NOTOPIC(user->getNick(), channel->getName()));
		sendUserList(*channel, *user);
		std::cout << CYA << "User [" << user->getFd() << "] joined the channel [" << channel->getName() << "]" << WHI << std::endl;
	}
}

void	Server::joinCmd(std::vector<std::string> cmd, int fd)
{
	std::vector<std::string>	names;
	std::vector<std::string>	passwords;
	User	*user = searchUser(fd);
	bool	pass;

	if (cmd[1].empty())
	{
		sendMessage(fd, ERR_NEEDMOREPARAMS(user->getNick(), cmd[0], "You must specify at least one channel name."));
		return ;
	}
	names = split(cmd[1], ',');
	if (cmd.size() > 2)
	{
		passwords = split(cmd[2], ',');
		pass = true;
	}
	else
		pass = false;
	for (size_t i = 0; i < names.size(); i++) {
		if (pass == false || passwords[i].empty())
			joinNewChannel(names[i], user);
		else
			joinNewChannel(names[i], passwords[i], user);

	}
}
