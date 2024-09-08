/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sed.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:01:51 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/06 23:39:53 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <limits>
#include <string>


class Sed
{
private:
	std::string filename;
	std::string s1;
	std::string s2;
public:
	Sed();
	~Sed();
	void get_args();
	void open_and_replace();
	int  ft_substr(const std::string &str, int &start, int &end, size_t &pos);
};

