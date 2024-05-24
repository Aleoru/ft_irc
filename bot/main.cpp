/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 04:02:56 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/24 03:53:26 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

int	ft_stoi(char const *str)
{
	int i;
	int sign;
	int n;

	i = 0;
	sign = 1;
	n = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

int main(int argc, char **argv)
{
	if (argc == 5)
	{
		std::string ip = argv[1];
		if (!ip.compare("localhost"))
			ip = "127.0.0.1";
		Bot bot(argv[1], ft_stoi(argv[2]), argv[3], argv[4]);
		bot.connectBot();
		bot.working();
	}
	else
	{
		std::cout<<"usage: [ip] [port] [pass] [nick]"<<std::endl;
		return (1);
	}

	return (0);
}