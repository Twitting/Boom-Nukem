/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:10:46 by ebednar           #+#    #+#             */
/*   Updated: 2019/03/08 15:42:32 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

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
	s = -1;
	while (++s < (int)sect.npoints)
		if (sect->neighbors[s] >= 0 && intersect_box(p, dp, sect->vertex[s % nowsect.npoints], sect->vertex[(s + 1) % nowsect.npoints]))
		{
			env->player.sector = sect->neighbors[s];
			break;
		}
	env->player.where.x += dp.x;
	env->player.where.y += dp.y;
}