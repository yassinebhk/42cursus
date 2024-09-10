/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:09:20 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/11 01:02:45 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Fixed area(Point const &a, Point const &b, Point const &c)
{
	return Fixed(
        std::abs(
            (a.getX().toFloat() * (b.getY().toFloat() - c.getY().toFloat())) +
            (b.getX().toFloat() * (c.getY().toFloat() - a.getY().toFloat())) +
            (c.getX().toFloat() * (a.getY().toFloat() - b.getY().toFloat()))
        ) / 2.0f
    );
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
    Fixed area_ABC = area(a, b, c);

    Fixed area_PAB = area(point, a, b);
    Fixed area_PBC = area(point, b, c);
    Fixed area_PCA = area(point, c, a);

    return area_ABC == (area_PAB + area_PBC + area_PCA);
}
