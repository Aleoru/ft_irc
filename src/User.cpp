/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:57:44 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/12 13:12:46 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

User::User()
{
    //this->_nick = "default";
	std::cout << "User constructor called" << std::endl;
}

User::User(const User &src) : _fd(src.getFd()), _ipAdd(src.getIpAdd()), _nickname(src.getNick())
{
    //this->_nick = "default";
	std::cout << "User copy constructor called" << std::endl;
}

User::~User()
{
	std::cout << "User destructor called" << std::endl;
}

//get
int				User::getFd() const {return this->_fd;}
std::string		User::getIpAdd() const {return this->_ipAdd;}
std::string		User::getNick() const {return this->_nickname;}
std::string		User::getUsername() const {return this->_username;}

//set
void	User::setFd(int fd) {this->_fd = fd;}
void	User::setIpAdd(std::string ipadd) {this->_ipAdd = ipadd;}
