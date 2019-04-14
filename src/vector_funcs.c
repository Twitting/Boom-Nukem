/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:10:24 by twitting          #+#    #+#             */
/*   Updated: 2019/04/03 14:15:08 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

double	vxs(double x0, double y0, double x1, double y1)
{
	return (x0 * y1 - x1 * y0);
}

int		overlap(double a0, double a1, double b0, double b1)
{
	if (MIN(a0, a1) <= MAX(b0, b1) && MIN(b0, b1) <= MAX(a0, a1))
		return (1);
	return (0);
}

int		i_b(t_xy a, t_xy b, t_xy c, t_xy d)
{
	if (overlap(a.x, b.x, c.x, d.x) && overlap(a.y, b.y, c.y, d.y))
		return (1);
	return (0);
}

double	point_side(double px, double py, t_xy a, t_xy b)
{
	double	ret;

	ret = vxs(b.x - a.x, b.y - a.y, px - a.x, py - a.y);
	return (ret);
}

t_xy	intersect(t_xy a, t_xy b, t_xy c, t_xy d)
{
	t_xy	ret;

	ret.x = vxs(vxs(a.x, a.y, b.x, b.y), a.x - b.x, vxs(c.x, c.y, d.x, d.y),
	c.x - d.x) / vxs(a.x - b.x, a.y - b.y, c.x - d.x, c.y - d.y);
	ret.y = vxs(vxs(a.x, a.y, b.x, b.y), a.y - b.y, vxs(c.x, c.y, d.x, d.y),
	c.y - d.y) / vxs(a.x - b.x, a.y - b.y, c.x - d.x, c.y - d.y);
	return (ret);
}
