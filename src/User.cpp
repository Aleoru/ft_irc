/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:57:44 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/15 20:25:11 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

User::User()
{
    //this->_nick = "default";
	std::cout << "User constructor called" << std::endl;
}

User::User(int fd, std::string ipAdd) : _fd(fd), _ipAdd(ipAdd)
{
	std::cout << "User constructor called" << std::endl;
}

User::User(User const &src)
{
	*this = src;
	std::cout << "Copy constructor called" << std::endl;
}

User::~User()
{
	std::cout << "User destructor called" << std::endl;
}

User &User::operator=(User const &src)
{
	if (this != &src)
	{
		this->_fd = src._fd;
		this->_ipAdd = src._ipAdd;
		this->_nickname = src._nickname;
		this->_username = src._username;
	}
	return (*this);
}

//get
int				User::getFd() const {return this->_fd;}
std::string		User::getIpAdd() const {return this->_ipAdd;}
std::string		User::getNick() const {return this->_nickname;}
std::string		User::getUsername() const {return this->_username;}

//set
void	User::setFd(int fd) {this->_fd = fd;}
void	User::setIpAdd(std::string ipadd) {this->_ipAdd = ipadd;}
void	User::setNickname(std::string nickname) {this->_nickname = nickname;}
void	User::setUsername(std::string username) {this->_username = username;}
