/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:14 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/06 17:37:14 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HumanA_HPP_
#define HumanA_HPP_

#include <iostream>
#include "Weapon.hpp"

class HumanA
{
private:
	std::string name;
	Weapon		&weapon;
public:
	~HumanA();
	HumanA(const std::string &name, Weapon &weapon);
	void attack() const;
};

#endif
