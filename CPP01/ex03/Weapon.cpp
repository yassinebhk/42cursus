/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:01:46 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/05 21:40:02 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

Weapon::Weapon(const std::string &weapon)
{
	this->type = weapon;
}

const std::string &Weapon::getType() const
{
	return (this->type);
}

void Weapon::setType(const std::string &type)
{
	this->type = type;
}