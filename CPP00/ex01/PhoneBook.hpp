/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:40:40 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/03 20:30:32 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "Contact.hpp"

class PhoneBook
{
private:
	Contact contacts[8];
	int		num_contacts;

public:
	PhoneBook();
	~PhoneBook();
	void get_args(std::string (&args)[5], std::string (&data)[5]);
	void get_valid_number(std::string &arg);
	void add_contact(PhoneBook &phonebook);
	void print_contacts(const PhoneBook &phonebook) const;
	void print_detail_contact(const PhoneBook &phonebook, int input) const;
	void fill_phonebook();
};

#endif