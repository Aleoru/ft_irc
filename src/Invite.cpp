/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:55:14 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/06 18:54:08 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"
#include "../inc/Server.hpp"
#include "../inc/Channel.hpp"
#include "../inc/replies.hpp"

/*Una vez incluidas las librerias ahora vamos a ponernos con el Invite
Tiene como estructura: invite <nick> #<canal>
PASOS:
1-Verificar si el usuario que invita tiene permisos, lo vamos a poner como variable nula por ahora
2-Verificar si existe el usuario invitado comprobando su nick
3-Si existe el usuario y hay permisos y existe el canal, añadirlo a la lista de invitados
3.5- Si ya existe en la lista de invitados, ignorar el comando, osea no hace nada
*/

void	Server::invite(std::vector<std::string> cmd, int fd) //cmd es la linea de comandos y fd?
{
	//cmd[1,2,3...] son todos los argumentos, en el caso del invite, cmd[1] tiene que ser el nombre del canal

	if (!channelExists(cmd[1])) //Esta comprobación es innecesaria según el protocolo pero es posible que de lugar a un error de segmentación o se crea un canal nuevo?
		return ;
	std::string channel_name = cmd[1];
	std::string invited_user = cmd[2];
	Channel *canal = searchChannel(channel_name);
	bool needOp = canal->getInvite();
	std::vector<User> users = getUsers(); //Vector for Users in the server
	std::vector<User>::iterator it = users.begin(); //Iterator for users in the server
	
	for(it; it != users.end(); it++)
	{
		if (needOp == true)
		{ //debajo: Si hemos encontrado el usuario en la lista de usuarios del servidor, y el usuario no está en el canal y el que ha pedido solicitud es admin
			if (it->getNick() == invited_user && !canal->operatorExists(searchUser(fd)->getNick()))  //si existe el nick en el servidor y no está unido al canal
			{
				canal->addUserToList(*it);
				sendMessage(1, RPL_INVITING(it->getNick(), canal->getName()));
				return ;
			}
		}
		else if (needOp == false)
		{
			if (it->getNick() == invited_user)  //si existe el nick en el servidor (MIRAR SI TENGO QUE COMPROBAR QUE NO ESTÉ EN EL SERVIDOR)
				canal->addUserToList(*it);
		}
	}
	sendMessage(1, ERR_NOSUCHNICK(it->getNick())); //Si no hemos podido añadir el usuario al canal, la última opción es que no exista el usuario y por ende, no se haya podido invitar
	return ;
}