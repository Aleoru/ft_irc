/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:57:44 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/05 18:56:29 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() 
{
    std::cout << "User constructor called" << std::endl;
}

User::~User()
{
    std::cout << "User destructor called" << std::endl;
}

//get
int     User::getFd() {return _fd;}

//set
void    User::setFd(int fd) {_fd = fd;}
void    User::setIpAdd(std::string ipadd) {_iPadd = ipadd;}
