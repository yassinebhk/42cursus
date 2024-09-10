/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:09:27 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/11 01:02:42 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include "Fixed.hpp"

class Point
{
private:
	Fixed const x;
	Fixed const y;
public:
	Point();
	Point(const float &n1, const float &n2);
	Point(const Point &point);
	~Point();
	
    Fixed getX() const;
    Fixed getY() const;
	Point &operator=(const Point &other);
};

bool bsp( Point const a, Point const b, Point const c, Point const point);
Fixed area(Point const &a, Point const &b, Point const &c);

#endif
