/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sed.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:01:41 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/06 23:40:45 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sed.hpp"

Sed::Sed()
{
}

Sed::~Sed()
{
}

void Sed::get_args()
{
	std::string filename, s1, s2;
	
    while (true) 
	{
        std::cout << "\033[37;1m> Write the filename: \033[0;90m\n";
        std::getline(std::cin, filename);
        if (std::cin.eof()) 
		{
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "❌ End of input detected. Exiting...\n";
            return ;
		}
        if (std::cin.fail() || filename.empty()) 
		{
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "❌ Invalid input. Please try again.\n";
            continue;
        }
        break;
    }
    while (true) 
	{
		std::cout << "\033[37;1m> Write the first string: \033[0;90m\n";
        std::getline(std::cin, s1);
        if (std::cin.eof()) 
		{
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "❌ End of input detected. Exiting...\n";
            return ;
		}
        if (std::cin.fail() || s1.empty()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "❌ Invalid input. Please try again.\n";
            continue;
        }
        break;
    }
    while (true) 
	{
		std::cout << "\033[37;1m> Write the second string: \033[0;90m\n";
        std::getline(std::cin, s2);
        if (std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return ;
        }
        if (std::cin.fail() || s2.empty()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "❌ Invalid input. Please try again.\n";
            continue;
        }
        break;
    }
	this->filename = filename;
	this->s1 = s1;
	this->s2 = s2;
}

int Sed::ft_substr(const std::string &str, int &start, int &end, size_t &pos)
{
    int str_pos = 0;

    while (pos < str.length())
    {
        if (str[pos] == this->s1[str_pos])
        {
            if (str_pos == 0)
                start = pos;
            end = pos;
            str_pos++;
            if (str_pos == (int)this->s1.length())
            {
                pos++;
                return 1;
            }
        }
        else
        {
            str_pos = 0;
            start = -1;
            end = -1;
        }
        pos++;
    }
    return 0;
}

void Sed::open_and_replace()
{
    std::string str;
    std::ifstream fin;
    std::ofstream fout;
    int end = -1;
    int start = -1;
    size_t pos = 0;

    fin.open(this->filename.c_str());
    if (fin.fail())
    {
        std::cout << "\033[31;1m❌ Cannot open " << this->filename << std::endl;
        return;
    }
    fout.open((this->filename + ".replace").c_str());
    if (fout.fail())
    {
        std::cout << "\033[31;1m❌ Cannot open " << this->filename + ".replace" << std::endl;
        return;
    }
    while (std::getline(fin, str))
    {
        pos = 0;
        int old_pos = 0;

        while (this->ft_substr(str, start, end, pos))
        {
            fout << str.substr(old_pos, start - old_pos);
            fout << this->s2;
            old_pos = end + 1;
        }
        fout << str.substr(old_pos);
        fout << std::endl;
    }
    fin.close();
    fout.close();
}

