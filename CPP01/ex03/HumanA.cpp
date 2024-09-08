/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:06:24 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/06 17:35:47 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::~HumanA()
{
    std::cout << "\033[34;1m" << "HumanA is being destroyed\n";
}

HumanA::HumanA(const std::string &name, Weapon &weapon)
	: name(name), weapon(weapon)
{
}

void HumanA::attack() const
{
	std::cout << "\033[34;1m" << this->name << "  attacks with their " 
	          << this->weapon.getType() << std::endl;
}