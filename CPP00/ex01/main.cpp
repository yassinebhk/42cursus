/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 04:00:33 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/04 17:02:33 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"

void	print_menu(int type)
{	
	std::string color1 = "\033[0;90m";
	std::string color2 = "\033[0;90m";
	std::string color3 = "\033[0;90m";

	if (type == 1)
		color1 = "\033[33;1m";
	else if (type == 2)
		color2 = "\033[33;1m";
		
	std::cout << "\033[34;1m----------------------------------\n";		
	std::cout << "\033[34;1m              Phonebook           \n";
	std::cout << "\033[34;1m----------------------------------\n";	
	
	std::cout << "\033[37;1mSelect an option:\n";
	std::cout << color1 << " -> ADD\n";
	std::cout << color2 << " -> SEARCH\n";	
	std::cout << color3 << " -> EXIT\n\033[37;1m";	
}

int main()
{
	int					index;
	std::string			input;
	PhoneBook			phonebook;

	std::cin.clear();
	do
	{
		print_menu(0);
		std::cin >> input;
		if (std::cin.eof() || !std::cin.good()) {
			std::cout << "\n\033[31;1mLeaving the phonebook due to input error or EOF...\n";
			break;
		}
		if (input == "ADD")
		{
			print_menu(1);
			phonebook.add_contact(phonebook);
		}
		else if (input == "SEARCH")
		{
			print_menu(2);

			phonebook.print_contacts(phonebook);
			std::cout << "Select an index\n";
			std::cin >> index;
			phonebook.print_detail_contact(phonebook, index);
		}
		else if (input == "EXIT")
			std::cout << "\n\033[31;1mLeaving the phonebook...\n";
		else if (input == "fill")
			phonebook.fill_phonebook();		
		else
			std::cout << "\n\033[35;1mCommand not found\n";
	} while (input != "EXIT");
	std::cin.ignore(1000, '\n');
}
