/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:57:44 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/20 15:07:28 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

User::User()
{
	//std::cout << "User constructor called" << std::endl;
}

User::User(int fd, std::string ipAdd) : _fd(fd), _ipAdd(ipAdd)
{
	this->_hasAccess = false;
	this->_checkPass = false;
	this->_checkNick = false;
	this->_checkUser = false;
	this->_nickname = "*";
	this->_username = "*";
	this->_nbChannels = 0;
	//std::cout << "User constructor called" << std::endl;
}

User::User(User const &src)
{
	*this = src;
	//std::cout << "Copy constructor called" << std::endl;
}

User::~User()
{
	//std::cout << "User destructor called" << std::endl;
}

User &User::operator=(User const &src)
{
	if (this != &src)
	{
		this->_fd = src._fd;
		this->_ipAdd = src._ipAdd;
		this->_nickname = src._nickname;
		this->_username = src._username;
		this->_hasAccess = src._hasAccess;
		this->_checkNick = src._checkNick;
		this->_checkPass = src._checkPass;
		this->_checkUser = src._checkUser;
		this->_nbChannels = src._nbChannels;
	}
	return (*this);
}

//get
int				User::getFd() const {return this->_fd;}
std::string		User::getIpAdd() const {return this->_ipAdd;}
std::string		User::getNick() const {return this->_nickname;}
std::string		User::getUsername() const {return this->_username;}
bool			User::getHasAccess() const {return this->_hasAccess;}
bool			User::getCheckPass() const {return this->_checkPass;}
bool			User::getCheckNick() const {return this->_checkNick;}
bool			User::getCheckUser() const {return this->_checkUser;}
int				User::getNbChannels() const {return this->_nbChannels;}

//set
void	User::setFd(int fd) {this->_fd = fd;}
void	User::setIpAdd(std::string ipadd) {this->_ipAdd = ipadd;}
void	User::setNickname(std::string nickname) {this->_nickname = nickname;}
void	User::setUsername(std::string username) {this->_username = username;}
void	User::setHasAccess(bool access) {this->_hasAccess = access;}
void	User::setCheckPass(bool pass) {this->_checkPass = pass;}
void	User::setCheckNick(bool nick) {this->_checkNick = nick;}
void	User::setCheckUser(bool user) {this->_checkUser = user;}
void	User::setNbChannels(int num) {this->_nbChannels+=num;}
