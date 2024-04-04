/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:57:55 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/03 14:12:03 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "sockets.h"

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