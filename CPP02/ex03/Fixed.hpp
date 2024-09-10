/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:35:09 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/11 00:32:56 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP_
#define FIXED_HPP_

#include <iostream>
#include <limits>
#include <string>
#include <cmath>

class Fixed
{
private:
	int					value;
	static const int	fracctional;

public:
	Fixed();
	Fixed(const Fixed &fixed_point);
	Fixed(const int &num);	
	Fixed(const float &num);	
	~Fixed();
	
	Fixed& operator=(const Fixed& other);
	bool operator<(const Fixed& other) const;
	bool operator>(const Fixed& other) const;
	bool operator<=(const Fixed& other) const;
	bool operator>=(const Fixed& other) const;
	bool operator==(const Fixed& other) const;
	bool operator!=(const Fixed& other) const;
	Fixed operator+(const Fixed& other) const;
	Fixed operator-(const Fixed& other) const;
	Fixed operator*(const Fixed& other) const;
	Fixed operator/(const Fixed& other) const;
	Fixed &operator++();
	Fixed &operator--();
	Fixed operator++(int);
	Fixed operator--(int);
	
	int getRawBits(void) const;
	void setRawBits( int const raw );
	float toFloat( void ) const;
	int toInt( void ) const;
	static Fixed &min(Fixed &a, Fixed &b);
	static Fixed &max(Fixed &a, Fixed &b);
	static const Fixed &min(const Fixed &a, const Fixed &b);
	static const Fixed &max(const Fixed &a, const Fixed &b);

	friend std::ostream& operator<<(std::ostream& os, const Fixed& fixed);
};

#endif
