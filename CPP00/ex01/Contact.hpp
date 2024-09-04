/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:40:42 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/26 04:57:46 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>

class Contact
{
private:
	std::string nickname;
	std::string last_name;
	std::string first_name;
	std::string phonenumber;
	std::string darkest_secret;
public:
	Contact();
	~Contact();
    int which_data(const std::string &input) const;
    void set_data(const std::string &input, const std::string &data);
    std::string get_data(const std::string &input) const;
};

#endif