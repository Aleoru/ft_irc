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
#include <algorithm>

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

void	Server::Kick(std::vector<std::string> cmd, int fd)
{
	//Para el kick, tengo que verificar que el usuario que lo está haciendo sea admin del canal
	//También que el usuario que vamos a expulsar exista

	std::string channel_name = cmd[1];
	std::string kickedUser = cmd[2];
	std::string comment = cmd[3];
	Channel *canal = searchChannel(channel_name);

	if (cmd.size() < 2) //aqui comprobamos si el comando esta vacío
		sendMessage(fd, ERR_NOSUCHCHANNEL(canal->getName()));
	if (canal->operatorExists(searchUser(fd)->getNick())) //Si el admin es admin y el usuario a echar está en el canal
	{
		if (searchUser(kickedUser) != NULL) //Si el usuario está en el canal
		{
			canal->removeUser(searchUser(kickedUser)->getFd()); //eliminar al usuario del canal
			sendMessage(fd, RPL_PART(getUserSource(searchUser(fd)), canal->getName())); //enviar respuesta
		}
		else
			sendMessage(1, ERR_NOTONCHANNEL(canal->getName()));
	}
	else
		sendMessage(1, ERR_CHANOPRIVSNEEDED(searchUser(fd)->getNick(), canal->getName()));
}