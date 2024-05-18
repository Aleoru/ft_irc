/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:55:17 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/02 19:55:17 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"
#include "../inc/Server.hpp"
#include "../inc/Channel.hpp"

/*
El kick es un comando que va a eliminar a un usuario de un canal.
1-Solo los operadores pueden usar este comando

TODO

1. Verificar que el usuario haciendo el request está en el canal, y es admin
2. Verificar que el usuario al que va a expulsar existe
3. Expulsar al usuario eliminando su FD de la lista de ese canal

*/

/*
Esta función busca a un usuario en un vector de usuarios, devuelve verdadero si lo encuentra y falso si no
*/

void	Server::kickCmd(std::vector<std::string> cmd, int fd)
{
	//Para el kick, tengo que verificar que el usuario que lo está haciendo sea admin del canal
	//También que el usuario que vamos a expulsar exista

	std::string channel_name = cmd[1];
	std::string kickedUser = cmd[2];
	std::string comment = cmd[3];
	Channel *canal = searchChannel(channel_name);
	std::vector<User> users = canal->getUsers();
	std::vector<User>::iterator it = users.begin();

	if (cmd.size() < 2) //aqui comprobamos si el comando esta vacío
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), cmd[0], "/kick [channel] [user] [<reason>]"));
	if (canal->operatorExists(searchUser(fd)->getNick())) //Si el admin es admin 
	{
		for(; it != users.end(); ++it)
		{
			if (!it->getNick().compare(kickedUser)) //Si el usuario esta en el canal
			{
				if (comment.empty())
					comment = "No reason given";
				sendMsgUsersList(canal->getUsers(), RPL_KICK(getUserSource(searchUser(fd)), canal->getName(), kickedUser, comment)); //enviar respuesta
				canal->removeUser(searchUser(kickedUser)->getFd()); //eliminar al usuario del canal
				return ;
			}
		}
			sendMessage(fd, ERR_NOTONCHANNEL(searchUser(fd)->getNick(), canal->getName()));
			return ;
	}
	else
		sendMessage(fd, ERR_CHANOPRIVSNEEDED(searchUser(fd)->getNick(), canal->getName()));
}