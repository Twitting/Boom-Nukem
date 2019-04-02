/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:10:46 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/02 15:15:45 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	v_collision(t_env *env)
{
	double	nz;

	env->ground = !env->falling;
	env->player.eye = env->ducking ? DUCKHEIGHT : EYEHEIGHT;
	if (env->falling)
	{
		env->player.velocity.z -= 0.05 * 60.0 / (double)env->oldfps;;
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

void	h_collision(t_env *env, t_xy *p, t_xy *d, t_xy *dd)
{
	int			s;
	t_sector	sect;
	t_xy		b;
	t_xy		pd;
	double		temp;

	sect = env->sector[env->player.sector];
	pd.x = p->x + dd->x;
	pd.y = p->y + dd->y;
	s = -1;
	while (++s < (int)sect.npoints)
		if (intersect_box(*p, pd, sect.vertex[s % sect.npoints], 
		sect.vertex[(s + 1) % sect.npoints]) &&
		point_side(pd.x, pd.y, sect.vertex[s % sect.npoints], sect.vertex\
		[(s + 1) % sect.npoints]) < 0)
		{
			double hole_low = sect.neighbors[s] < 0 ? 9e9 : MAX(sect.floor, env->sector[sect.neighbors[s]].floor);
			double hole_high = sect.neighbors[s] < 0 ? 9e9 : MIN(sect.ceiling, env->sector[sect.neighbors[s]].ceiling);
			if (hole_high < env->player.where.z + HEADMARGIN || hole_low > env->player.where.z - (env->ducking ? DUCKHEIGHT : EYEHEIGHT) + KNEEHEIGHT)
			{
				ft_putstr("collision\n");
				b.x = sect.vertex[(s + 1) % sect.npoints].x - sect.vertex[s % sect.npoints].x;
				b.y = sect.vertex[(s + 1) % sect.npoints].y - sect.vertex[s % sect.npoints].y;
				temp = d->x;
				d->x = b.x * (d->x * b.x + b.y * d->y) / (b.x * b.x + b.y * b.y);
				d->y = b.y * (temp * b.x + b.y * d->y) / (b.x * b.x + b.y * b.y);
				env->moving = -1;
			}
		}
	env->falling = 1;
}

int can_i_go(t_env *env, t_xy *p, double x, double y)
{
	double			oldx = x;
	double			oldy = y;
	double			a, b, c, s;
	double			hh[env->sector[env->player.sector].npoints];
	unsigned int	i = 0;
	unsigned int	ii = i % env->sector[env->player.sector].npoints;
	unsigned int	ii1 = (i + 1) % env->sector[env->player.sector].npoints;

	while (i < env->sector[env->player.sector].npoints)
	{
		a = sqrt(pow(p[i].x - oldx, 2) + pow(p[i].y - oldy, 2));
		b = sqrt(pow(p[ii1].x - oldx, 2) + pow(p[ii1].y - oldy, 2));
		c = sqrt(pow(p[i].x - p[ii1].x, 2) + pow(p[i].y - p[ii1].y, 2));
		s = 0.25 * sqrt(pow(pow(a, 2) + pow(b, 2) + pow(c, 2), 2) \
			- 2 * (pow(a, 4) + pow(b, 4) + pow(c, 4)));
		hh[i] = (2 * s) / c;
		if ( a < 0.7 || b < 0.7) // нет зависимости от высоты
			return (0);

		i++;
	}
	return (1);
}

void	movement(t_env *env, float dx, float dy)
{
	t_xy			p;
	t_xy			dp;
	t_sector		sect;
	int				s;
	unsigned int 	i = 0;
	t_xy 			points[env->sector[env->player.sector].npoints];
	unsigned int 	counter = 0;

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
			break ;
		}
	while (i < env->sector[env->player.sector].npoints)
	{
		points[i].x = sect.vertex[i].x;
		points[i].y = sect.vertex[i].y;
		i++;
	}

	i = 0;
	while (i < sect.npoints)
	{
		if (points[(i + 1) % sect.npoints].x && (points[(i + 1) % sect.npoints].x - points[(i + 1) % env->sector[env->player.sector].npoints].x == 0 || points[i + 1].y - points[(i + 1) % env->sector[env->player.sector].npoints].y == 0))
			counter++;
		else if (!points[i].x && (points[0].x - points[(i + 1) % env->sector[env->player.sector].npoints].x == 0 || points[0].y - points[(i + 1) % env->sector[env->player.sector].npoints].y == 0))
			counter++;
		i++;
	}
	if (can_i_go(env, points, env->player.where.x + dx, env->player.where.y + dy))
	{
		env->player.where.x += dx;
		env->player.where.y += dy;
	}
	else
	{
		printf("no\n");
	}
	
}

void	wsad_read(t_env *env)
{
	t_xy	mv;
	t_xy	dmv;

	mv.x = 0;
	mv.y = 0;
	if (env->wsad[0])
	{
		mv.x += cos(env->player.angle) * 0.4;
		mv.y += sin(env->player.angle) * 0.4;
	}
	if (env->wsad[1])
	{
		mv.x -= cos(env->player.angle) * 0.4;
		mv.y -= sin(env->player.angle) * 0.4;
	}
	if (env->wsad[2])
	{
		mv.x += sin(env->player.angle) * 0.4;
		mv.y -= cos(env->player.angle) * 0.4;
	}
	if (env->wsad[3])
	{
		mv.x -= sin(env->player.angle) * 0.4;
		mv.y += cos(env->player.angle) * 0.4;
	}
	dmv.x = 0;
	dmv.y = 0;
	if (env->wsad[0])
	{
		dmv.x += cos(env->player.angle) * 1;
		dmv.y += sin(env->player.angle) * 1;
	}
	if (env->wsad[1])
	{
		dmv.x -= cos(env->player.angle) * 1;
		dmv.y -= sin(env->player.angle) * 1;
	}
	if (env->wsad[2])
	{
		dmv.x += sin(env->player.angle) * 1;
		dmv.y -= cos(env->player.angle) * 1;
	}
	if (env->wsad[3])
	{
		dmv.x -= sin(env->player.angle) * 1;
		dmv.y += cos(env->player.angle) * 1;
	}
	env->player.velocity.x = mv.x * 60.0 / (double)env->oldfps;
	env->player.velocity.y = mv.y * 60.0 / (double)env->oldfps;
	env->player.dvelocity.x = dmv.x * 60.0 / (double)env->oldfps;
	env->player.dvelocity.y = dmv.y * 60.0 / (double)env->oldfps;
	env->moving = (mv.x != 0 || mv.y != 0 || env->falling) ? 1 : 0;
}

void	movement_calcs(t_env *env)
{
	t_xy		p;
	t_xy		d;
	t_xy		dd;
	
	wsad_read(env);
	if (env->moving)
	{
		p.x = env->player.where.x;
		p.y = env->player.where.y;
		d.x = env->player.velocity.x;
		d.y = env->player.velocity.y;
		dd.x = env->player.dvelocity.x;
		dd.y = env->player.dvelocity.y;
		v_collision(env);
		h_collision(env, &p, &d, &dd);
		movement(env, d.x, d.y);
	}
	movement(env, 0, 0);
	
}
