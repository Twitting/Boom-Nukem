/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:10:46 by ebednar           #+#    #+#             */
/*   Updated: 2019/03/08 18:21:28 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	collision(t_sector sect, t_xy p, t_xy dp)
{
	int s;

	dp.x += 1;
	dp.y += 1;
	s = -1;
	while (++s < (int)sect.npoints)
		if (sect.neighbors[s] < 0 && intersect_box(p, dp, sect.vertex[s % \
		sect.npoints], sect.vertex[(s + 1) % sect.npoints]) && \
		point_side(dp.x, dp.y, sect.vertex[s % sect.npoints], sect.vertex\
		[(s + 1) % sect.npoints]) < 0)
		{
			ft_putendl("collision");
			return (1);
		}
	return(0);
}

void	movement(t_env *env, float dx, float dy)
{
	t_xy		p;
	t_xy		dp;
	t_sector	sect;
	int			s;

	p.x = env->player.where.x;
	p.y = env->player.where.y;
	dp.x = p.x + dx;
	dp.y = p.y + dy;
	sect = env->sector[env->player.sector];
	if (collision(sect, p, dp))
		return ;
	s = -1;
	while (++s < (int)sect.npoints)
		if (sect.neighbors[s] >= 0 && intersect_box(p, dp, sect.vertex[s % \
		sect.npoints], sect.vertex[(s + 1) % sect.npoints]) && \
		point_side(dp.x, dp.y, sect.vertex[s % sect.npoints], sect.vertex\
		[(s + 1) % sect.npoints]) < 0)
		{
			env->player.sector = sect.neighbors[s];
			break;
		}
	env->player.where.x += dx;
	env->player.where.y += dy;
}