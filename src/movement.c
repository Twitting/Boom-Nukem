/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:10:46 by ebednar           #+#    #+#             */
/*   Updated: 2019/03/09 12:26:21 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	collision(t_env *env)
{
	int			s;
	t_xy		p;
	t_xy		d;
	t_sector	sect;
	t_xy		bump;
	t_xy		pd;

	sect = env->sector[env->player.sector];
	p.x = env->player.where.x;
	p.y = env->player.where.y;
	d.x = env->player.velocity.x;
	d.y = env->player.velocity.y;
	pd.x = p.x + d.x;
	pd.y = p.y + d.y;
	s = -1;
	while (++s < (int)sect.npoints)
		if (sect.neighbors[s] < 0 && intersect_box(p, pd, sect.vertex[s % sect.npoints], 
		sect.vertex[(s + 1) % sect.npoints]) &&
		point_side(pd.x, pd.y, sect.vertex[s % sect.npoints], sect.vertex\
		[(s + 1) % sect.npoints]) < 0)
		{
			ft_putstr("collision\n");
			bump.x = sect.vertex[(s + 1) % sect.npoints].x - sect.vertex[s % sect.npoints].x;
			bump.y = sect.vertex[(s + 1) % sect.npoints].y - sect.vertex[s % sect.npoints].y;
			d.x = bump.x * (d.x * bump.x + bump.y * d.y) / (bump.x * bump.x + bump.y * bump.y);
			d.y = bump.y * (d.x * bump.x + bump.y * d.y) / (bump.x * bump.x + bump.y * bump.y);
			env->moving = 0;
		}
	movement(env, d.x, d.y);
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

void	wsad_read(t_env *env)
{
	t_xy	mv;

	mv.x = 0;
	mv.y = 0;
	if (env->wsad[0])
	{
		mv.x += cos(env->player.angle) * 0.2;
		mv.y += sin(env->player.angle) * 0.2;
	}
	if (env->wsad[1])
	{
		mv.x -= cos(env->player.angle) * 0.2;
		mv.y -= sin(env->player.angle) * 0.2;
	}
	if (env->wsad[2])
	{
		mv.x += sin(env->player.angle) * 0.2;
		mv.y -= cos(env->player.angle) * 0.2;
	}
	if (env->wsad[3])
	{
		mv.x -= sin(env->player.angle) * 0.2;
		mv.y += cos(env->player.angle) * 0.2;
	}
	env->player.velocity.x = env->player.velocity.x * 0.6 + mv.x * 0.4;
	env->player.velocity.y = env->player.velocity.y * 0.6 + mv.y * 0.4;
	env->moving = (mv.x != 0 || mv.y != 0) ? 1 : 0;
}

void	movement_calcs(t_env *env)
{
	wsad_read(env);
	if (env->moving)
	{
		collision(env);
	}
	else
		movement(env, 0, 0);
	
}