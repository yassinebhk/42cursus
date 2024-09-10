/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:35:09 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/09 20:31:09 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP_
#define FIXED_HPP_

#include <iostream>
#include <limits>
#include <string>

class Fixed
{
private:
	int					value;
	static const int	fracctional;

public:
	Fixed();
	Fixed(const Fixed &fixed_point);
	~Fixed();
	Fixed& operator=(const Fixed& other);
	int getRawBits(void) const;
	void setRawBits( int const raw );
};


#endif
