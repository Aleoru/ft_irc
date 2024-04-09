/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:57:44 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/08 19:41:47 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

User::User()
{
	std::cout << "User constructor called" << std::endl;
}

User::User(const User &src) : _fd(src.getFd()), _ipAdd(src.getIpAdd())
{
	std::cout << "User copy constructor called" << std::endl;
}

User::~User()
{
	std::cout << "User destructor called" << std::endl;
}

//get
int				User::getFd() const {return this->_fd;}
std::string		User::getIpAdd() const {return this->_ipAdd;}
std::string		User::getNick() const {return this->_nick;}

//set
void	User::setFd(int fd) {_fd = fd;}
void	User::setIpAdd(std::string ipadd) {_ipAdd = ipadd;}
