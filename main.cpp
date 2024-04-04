/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:58:04 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/04 00:52:15 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		//validate argv1,2
		Server server(4242, argv[2]);
		std::cout << "---- SERVER ----" << std::endl;
		try
		{
			signal(SIGINT, Server::signalHandler);		// catch the signal (ctrl + c)
			signal(SIGQUIT, Server::signalHandler); 	// catch the signal (ctrl + \)
			server.serverInit();						// initialize the server
		}
		catch(const std::exception& e)
		{
			server.closeFds();							// close the file descriptors
			std::cerr << e.what() << std::endl;
		}
		std::cout << "The Server Closed!" << std::endl;
	}
	else
	{
		std::cerr << "error: arguments" << std::endl;
		return (1);
	}
	return (0);
}