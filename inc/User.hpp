/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:57:55 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/08 11:05:39 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "../inc/sockets.h"

class User											
{
private:
	int         _fd;					    // client file descriptor
	std::string _iPadd;					    // client ip address
    
public:
	User();
    ~User();	
    									
	int     getFd();						// getter for fd

	void    setFd(int fd);					// setter for fd
	void    setIpAdd(std::string ipadd); 	// setter for ipadd
};

#endif