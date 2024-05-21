/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 04:02:56 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/21 05:16:37 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

int main(int argc, char **argv)
{
	if (argc == 5)
	{
		Bot bot(argv[1], std::stoi(argv[2]), argv[3], argv[4]);
		bot.connectBot();
		bot.workingBot();
	}
	else
	{
		std::cout<<"usage: [ip] [port] [pass] [nick]"<<std::endl;
		return (1);
	}

	return (0);
}