/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:40:46 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/03 20:44:01 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact()
{
}

Contact::~Contact()
{
}

int Contact::which_data(const std::string &input) const 
{
	if ("first_name" == input)
		return (1);
	else if ("last_name" == input)
		return (2);
	else if ("nickname" == input)
		return (3);
	else if ("phonenumber" == input)
		return (4);
	else if ("darkest_secret" == input)
		return (5);
	else
		return (0);
}

void Contact::set_data(const std::string &input, const std::string &data)
{
    switch (which_data(input)) 
	{
        case 1: this->first_name = data; break;
        case 2: this->last_name = data; break;
        case 3: this->nickname = data; break;
        case 4: this->phonenumber = data; break;
        case 5: this->darkest_secret = data; break;
    }
}

std::string Contact::get_data(const std::string &input) const 
{
    switch (which_data(input)) 
	{
        case 1: return this->first_name;
        case 2: return this->last_name;
        case 3: return this->nickname;
        case 4: return this->phonenumber;
        case 5: return this->darkest_secret;
        default: return "";
    }
}
