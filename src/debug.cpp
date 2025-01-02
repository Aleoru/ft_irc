/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:44:37 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/18 22:29:56 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Channel.hpp"

void	Server::printUsers(std::vector<User> userlist, std::string name)
{
	std::cout << "-----  " << name << "  users["<<userlist.size()<<"] -----"<< std::endl;
	for(size_t i = 0; i < userlist.size(); i++)
	{
		int fd = userlist[i].getFd();
		std::cout << " User[" << i << "], fd:" << fd << ", nick:" << searchUser(fd)->getNick()
		<< ", access:" << searchUser(fd)->getHasAccess() << std::endl;
 	}
}

void	Server::printChannels()
{
	std::cout << "Server fd: " << _fds[0].fd << std::endl;
	for(size_t i = 0; i < _channels.size(); i++)
	{
		std::cout << "Channel [" << i << "] name: " << _channels[i].getName() << std::endl;
 	}
}

void	Server::infoServer()
{
	std::cout<<YEL<<"--------- SERVER INFO ---------"<<WHI<<std::endl;
	printUsers(_users, "Server");
	std::cout << std::endl;
	for (size_t i = 0; i < _channels.size(); i++)
	{
		std::cout<<"Channel: "<<_channels[i].getName()<<" has "
		<<_channels[i].getUsers().size()<<" users"<<std::endl;
		std::cout << "HasTopic: " << _channels[i].getHasTopic() << std::endl;
		std::cout << "Topic can be modified: " << _channels[i].getSetTopic() << std::endl;
		std::cout << "HasPass: " << _channels[i].getHasPass() << std::endl;
		std::cout << "Can invite: " << _channels[i].getInvite() << std::endl;
		std::cout << "Channel user limit: " << _channels[i].getLimit() << std::endl;
		printUsers(_channels[i].getUsers(), _channels[i].getName());
		std::cout << std::endl;
	}
	std::cout<<YEL<<"-------------------------------"<<WHI<<std::endl;
}