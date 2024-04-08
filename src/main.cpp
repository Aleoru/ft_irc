/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:58:04 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/08 11:05:52 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

int main(int argc, char **argv)
{
	// validate number or arguments and value of argv1 and argv2
	if (argc == 3 && Server::validPort(argv[1]) && Server::validPass(argv[2]))
	{
		std::cout << "Init Server" << std::endl;
		Server server(std::stoi(argv[1]), argv[2]);
		signal(SIGINT, Server::signalHandler);			// catch the signal (ctrl + c)
		signal(SIGQUIT, Server::signalHandler); 		// catch the signal (ctrl + \)
		try
		{
			server.serverInit();						// initialize the server
		}
		catch(const std::exception& e)
		{
			server.closeFds();							// close the file descriptors
			std::cerr << e.what() << std::endl;
		}
		std::cout << "Server Closed" << std::endl;
	}
	else
	{
		std::cerr << "error: arguments" << std::endl;
		return (1);
	}
	return (0);
}