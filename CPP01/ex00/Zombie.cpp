/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:34 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/05 18:17:12 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie()
{
}

Zombie::Zombie(std::string arg) : name(arg)
{
}

Zombie::~Zombie()
{
	std::cout << "\033[31;1m" << this->name << ": Has died...\n\033[37;1m";
}

void Zombie::announce(void)
{
	std::cout << "\033[32;1m" << this->name << ": BraiiiiiiinnnzzzZ...\n";
}
