/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:10:46 by ebednar           #+#    #+#             */
/*   Updated: 2019/03/10 19:08:55 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	v_collision(t_env *env)
{
	double	nz;
	env->ground = !env->falling;
	env->player.eye = env->ducking ? DUCKHEIGHT : EYEHEIGHT;
	if(env->falling)
	{
		env->player.velocity.z -= 0.05;
		nz = env->player.where.z + env->player.velocity.z;
		if (env->player.velocity.z < 0 && nz < env->sector[env->player.sector].floor + env->player.eye)
		{
			env->player.where.z = env->sector[env->player.sector].floor + env->player.eye;
			env->player.velocity.z = 0;
			env->falling = 0;
			env->ground = 1;
		}
		else if (env->player.velocity.z > 0 && nz > env->sector[env->player.sector].ceiling)
		{
			env->player.velocity.z = 0;
			env->falling = 1;
		}
		if (env->falling)
		{
			env->player.where.z += env->player.velocity.z;
			env->moving = 1;
		}
	}
}

void	h_collision(t_env *env, t_xy *p, t_xy *d)
{
	int			s;
	t_sector	sect;
	t_xy		b;
	t_xy		pd;

	sect = env->sector[env->player.sector];
	pd.x = p->x + d->x;
	pd.y = p->y + d->y;
	s = -1;
	while (++s < (int)sect.npoints)
		if (intersect_box(*p, pd, sect.vertex[s % sect.npoints], 
		sect.vertex[(s + 1) % sect.npoints]) &&
		point_side(pd.x, pd.y, sect.vertex[s % sect.npoints], sect.vertex\
		[(s + 1) % sect.npoints]) < 0)
		{
			double hole_low = sect.neighbors[s] < 0 ? 9e9 : MAX(sect.floor, env->sector[sect.neighbors[s]].floor);
			double hole_high = sect.neighbors[s] < 0 ? 9e9 : MIN(sect.ceiling, env->sector[sect.neighbors[s]].ceiling);
			if (hole_high < env->player.where.z + HEADMARGIN || hole_low > env->player.where.z - EYEHEIGHT + KNEEHEIGHT)
			{
				ft_putstr("collision\n");
				b.x = sect.vertex[(s + 1) % sect.npoints].x - sect.vertex[s % sect.npoints].x;
				b.y = sect.vertex[(s + 1) % sect.npoints].y - sect.vertex[s % sect.npoints].y;
				d->x = b.x * (d->x * b.x + b.y * d->y) / (b.x * b.x + b.y * b.y);
				d->y = b.y * (d->x * b.x + b.y * d->y) / (b.x * b.x + b.y * b.y);
				env->moving = 0;
			}
		}
	env->falling = 1;
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
	env->player.velocity.x = env->player.velocity.x * 0.8 + mv.x * 0.2;
	env->player.velocity.y = env->player.velocity.y * 0.8 + mv.y * 0.2;
	env->moving = (mv.x != 0 || mv.y != 0 || env->falling) ? 1 : 0;
}

void	movement_calcs(t_env *env)
{
	t_xy		p;
	t_xy		d;
	
	wsad_read(env);
	if (env->moving)
	{
		p.x = env->player.where.x;
		p.y = env->player.where.y;
		d.x = env->player.velocity.x;
		d.y = env->player.velocity.y;
		v_collision(env);
		h_collision(env, &p, &d);
		movement(env, d.x, d.y);
	}
	movement(env, 0, 0);
	
}