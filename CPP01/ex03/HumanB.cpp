/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:06:24 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/06 17:39:23 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB()
{
	std::cout << "\033[33;1m" << "HumanB has taken a weapon\n";
}

HumanB::~HumanB()
{
    std::cout << "\033[33;1m" << "HumanB is being destroyed\n";
}

HumanB::HumanB(const std::string &name) : weapon(NULL)
{
	this->name = name;
}

void HumanB::setWeapon(Weapon &weapon)
{
	this->weapon = &weapon;
}

void HumanB::attack()
{
	if (weapon) 
 	{
		std::cout << "\033[33;1m" << name << " attacks with their " 
					<< weapon->getType() << std::endl;
	}
	else
		std::cout << "\033[33;1m" << name << " has no weapon to attack with!" << std::endl;
}