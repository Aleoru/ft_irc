/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:57:44 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/03 14:13:02 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() 
{
    std::cout << "Client created" << std::endl;
}

User::~User()
{
    std::cout << "Client deleted" << std::endl;
}

//get
int     User::getFd() {return _fd;}

//set
void    User::setFd(int fd) {_fd = fd;}
void    User::setIpAdd(std::string ipadd) {_iPadd = ipadd;}
