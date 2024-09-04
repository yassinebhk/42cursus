/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:40:44 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/04 23:26:24 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	this->num_contacts = 0;
}

PhoneBook::~PhoneBook()
{
}

void PhoneBook::get_valid_number(std::string &arg)
{
    bool valid;

    do {
        valid = true;
        if (arg.empty()) 
            valid = false;
        else 
        {
            for (std::string::size_type i = 0; i < arg.size(); ++i) {
                if (!std::isdigit(arg[i])) 
                {
                    valid = false;
                    break;
                }
            }
        }
        
        if (!valid) 
        {
            std::cout << "◾ Please, enter a valid number:\n";
        	std::getline(std::cin, arg);
            if (std::cin.eof()) 
            {
                std::cerr << "\nEnd of input detected. Exiting...\n";
                return;
            }
            if (std::cin.fail()) 
            {
                std::cerr << "\nError reading input. Exiting...\n";
                return;
            }
        }
    } while (!valid);
}

void PhoneBook::get_args(std::string (&args)[5], std::string (&data)[5])
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for(int i = 0; i < 5; i++)
    {
		do 
		{
        	std::cout << "\033[37;1m◾ Enter the " << data[i] << "\033[0;90m" << std::endl;
        	std::getline(std::cin, args[i]);
            if (std::cin.eof()) 
            {
                std::cerr << "\nEnd of input detected. Exiting...\n";
                return;
            }
            if (std::cin.fail()) 
            {
                std::cerr << "\nError reading input. Exiting...\n";
                return;
            }
		} 	while (args[i].empty());
        if (data[i] == "phonenumber")
			get_valid_number(args[i]);
    }   
}

void	PhoneBook::add_contact(PhoneBook &phonebook)
{
	Contact new_contact;
	std::string args[5];
	std::string data[5] = {"first_name", "last_name", "nickname", "phonenumber", "darkest_secret"};

	std::cout << "\033[32;1m ADD\n";	
	get_args(args, data);
	for(int j = 0; j < 5; j++)
		new_contact.set_data(data[j], args[j]);
	if (phonebook.num_contacts < 8)
		phonebook.contacts[num_contacts] = new_contact;
	else if (phonebook.num_contacts >= 8)
		phonebook.contacts[num_contacts % 8] = new_contact;
	phonebook.num_contacts++;
}

void PhoneBook::print_contacts(const PhoneBook &phonebook) const 
{
    std::string data[3] = {"first_name", "last_name", "nickname"};
    const int column_width = 10;

    std::cout << "\n---------------------------------------------------\n";
    std::cout << std::setw(column_width) << std::right << "|  index   | "
              << std::setw(column_width) << std::right << "first name |"
              << std::setw(column_width) << std::right << " last name  |"
              << std::setw(column_width) << std::right << " nickname   |" << std::endl;
    std::cout << "---------------------------------------------------\n";
    
    for (int i = 0; i < num_contacts && i < 8; ++i) 
    {
        std::string first_name = phonebook.contacts[i].get_data(data[0]);
        std::string last_name = phonebook.contacts[i].get_data(data[1]);
        std::string nickname = phonebook.contacts[i].get_data(data[2]);
        if (first_name.size() > column_width - 1)
            first_name = first_name.substr(0, column_width - 1) + '.';
        if (last_name.size() > column_width - 1)
            last_name = last_name.substr(0, column_width - 1) + '.';
        if (nickname.size() > column_width - 1)
            nickname = nickname.substr(0, column_width - 1) + '.';

        std::cout << std::setw(column_width) << std::right << i%8 + 1 << " | "
                  << std::setw(column_width) << std::right << first_name << " | "
                  << std::setw(column_width) << std::right << last_name << " | "
                  << std::setw(column_width) << std::right << nickname << " \n";
    }
}

void PhoneBook::print_detail_contact(const PhoneBook &phonebook, int input) const
{
    while (true)
    {
        if (std::cin.fail() || input <= 0 || input > phonebook.num_contacts)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "❌ Please, enter a valid number.\n";
            std::cin >> input;
        }
        else
            break;
    }
    
    std::string data[5] = {"first_name", "last_name", "nickname", "phonenumber", "darkest_secret"};
    std::string first_name = phonebook.contacts[input - 1].get_data(data[0]);
    std::string last_name = phonebook.contacts[input - 1].get_data(data[1]);
    std::string nickname = phonebook.contacts[input - 1].get_data(data[2]);
    std::string phonenumber = phonebook.contacts[input - 1].get_data(data[3]);
    std::string darkest_secret = phonebook.contacts[input - 1].get_data(data[4]);

    std::cout << "\n-----------------------------------------------\n";
    std::cout << "\033[0;90m| index | \033[37;1m" << input 
              << "\n\033[0;90m| first name | \033[37;1m" << first_name 
              << "\n\033[0;90m| last name | \033[37;1m" << last_name
              << "\n\033[0;90m| nickname | \033[37;1m" << nickname
              << "\n\033[0;90m| phonenumber | \033[37;1m" << phonenumber
              << "\n\033[0;90m| darkest_secret | \033[37;1m" << darkest_secret;
    std::cout << "\n-----------------------------------------------\n";
}

void PhoneBook::fill_phonebook()
{
    Contact new_contact;
    std::string first_names[8] = {"paco", "maria", "jose", "chema", "amador", "rocio", "lucia", "alberto"};
    std::string last_names[8] = {"cid", "lopez", "jul", "amar", "rivas", "luz", "paz", "gines"};
    std::string nickname[8] = {"el paquito lokito", "maria de la 0", "jose nado", "chema aida", "amador in da house", "rocio ro", "lu", "alb"};
    std::string phonenumber[8] = {"12", "5675", "6782", "3456", "12423", "1", "897", "4564666454"};
    std::string secret[8] = {"?", "¿", "!", "·", "%", "/", "()", "="};

    for(int i=0; i < 8; i++)
    {
        new_contact.set_data("first_name", first_names[i]);
        new_contact.set_data("last_name", last_names[i]);
        new_contact.set_data("nickname", nickname[i]);
        new_contact.set_data("phonenumber", phonenumber[i]);
        new_contact.set_data("darkest_secret", secret[i]);
        this->contacts[i] = new_contact;
        this->num_contacts++;
    }
}
