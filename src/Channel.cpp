/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:19:31 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/08 19:55:22 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Channel.hpp"

Channel::Channel(std::string name, User user): _name(name)
{
	this->_setTopic = false;
	this->_hasTopic = false;
	this->_limit = NOLIMIT;
	this->_invite = false;
	_users.push_back(user);
	_operators.push_back(user);
	std::cout << GRE << "Channel: "<< name <<" created" << WHI << std::endl;

}

Channel::Channel(std::string name, std::string pass, User user): _name(name), _pass(pass)
{
	this->_setTopic = false;
	this->_limit = NOLIMIT;
	this->_invite = false;
	_users.push_back(user);
	_operators.push_back(user);
	std::cout << GRE << "Channel created with password" << WHI << std::endl;

}

Channel::~Channel()
{
	std::cout << RED << "Channel destroyed" << WHI << std::endl;
}


std::string	Channel::getName() const { return (this->_name); }
std::string	Channel::getTopic() const { return (this->_topic); }
std::vector<User>	Channel::getUsers() const { return (this->_users); }

std::vector<int>	Channel::channelListUsers()
{
	std::vector<int> channelUsers;

	return (channelUsers);
}
