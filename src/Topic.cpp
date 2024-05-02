
#include "../inc/Channel.hpp"
#include "../inc/replies.hpp"
#include "../inc/Server.hpp"
#include <algorithm>

/*
El topic es simple, tenemos que verificar varias cositas:
1-Que el string que viene por parametro no está vacío, sino, devolvemos el topic actual del canal
2-Que esté la flag o no activada
*/


void changeTopic(Server serv, User usuario, Channel *canal, std::string newTopic, bool needOp)
{
	if (newTopic.length() < 1) //Aquí completamos la primera comprobación y actuamos en base al resultado
	{
		if (!canal->getHasTopic()) //si no hay topic, imprimimos solo un salto de línea
			std::cout << std::endl;
		else
			std::cout << canal->getTopic() << std::endl; //Sino imprimimos el topic
	}
	else if (needOp == 1) //si la flag +t está activada, además ya hemos verificado que la string de topic no esté vacía
	{
		std::vector<User> users_ch = canal->getUsers();
		std::vector<User> ops = canal->getOperators();
		std::vector<User>::iterator it = std::find(ops.begin(), ops.end(), usuario.getNick()); //lleva el iterador a la posición en la que usuario esté en operadores
		if (it != ops.end()) //cambiar el topic
			canal->setTopic(newTopic);
		else
			serv.sendMessage(2, ERR_CHANOPRIVSNEEDED(canal->getName()));
	}
	else //Si hay topic y la flag está desactivada cambiar el topic y listo
		canal->setTopic(newTopic);
}
