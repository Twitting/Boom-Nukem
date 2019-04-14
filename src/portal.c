/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:08:32 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/13 12:12:22 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"


int	portaledge(t_env *env, t_rend *rend)
{
	t_xy	p;
	t_xy	d;
	int		i;

	i = -1;
	while (++i < (int)env->sector[env->player.sector].npoints)
		if (rend->head->sectorno == env->sector[env->player.sector].neighbors[i])
		{
			//printf("search %d", rend->s);
			p.x = env->player.where.x;
			p.y = env->player.where.y;
			d.x = p.x + 1;
			d.y = p.y + 1;
			rend->butx = 0;
			if (intersect_box(p, d, env->sector[env->player.sector].vertex[rend->s % env->sector[env->player.sector].npoints], env->sector[env->player.sector].vertex[(rend->s + 1) % env->sector[env->player.sector].npoints]) && point_side(d.x, d.y, env->sector[env->player.sector].vertex[rend->s % env->sector[env->player.sector].npoints], env->sector[env->player.sector].vertex[(rend->s + 1) % env->sector[env->player.sector].npoints]) < 0)
			{
				ft_putnbr (env->player.sector);
				ft_putendl(" bug1?");
				return (1);
			}
			d.x = p.x - 1;
			d.y = p.y - 1;
			rend->butx = 0;
			if (intersect_box(p, d, env->sector[env->player.sector].vertex[rend->s % env->sector[env->player.sector].npoints], env->sector[env->player.sector].vertex[(rend->s + 1) % env->sector[env->player.sector].npoints]) && point_side(d.x, d.y, env->sector[env->player.sector].vertex[rend->s % env->sector[env->player.sector].npoints], env->sector[env->player.sector].vertex[(rend->s + 1) % env->sector[env->player.sector].npoints]) < 0)
			{
				ft_putendl(" bug2?");
				return (1);
			}
	}
	return (0);
}