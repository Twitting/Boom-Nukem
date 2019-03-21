/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:10:46 by ebednar           #+#    #+#             */
/*   Updated: 2019/03/21 15:35:34 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	v_collision(t_env *env)
{
	double	nz;

	env->ground = !env->falling;
	PEYE = env->ducking ? DUCKHEIGHT : EYEHEIGHT;
	if (env->falling)
	{
		PVELOSITY.z -= 0.01;
		nz = PWHERE.z + PVELOSITY.z;
		if (PVELOSITY.z < 0 && nz < ESECTOR[PSECT].floor + PEYE)
		{
			PWHERE.z = ESECTOR[PSECT].floor + PEYE;
			PVELOSITY.z = 0;
			env->falling = 0;
			env->ground = 1;
		}
		else if (PVELOSITY.z > 0 && nz > ESECTOR[PSECT].ceiling)
		{
			PVELOSITY.z = 0;
			env->falling = 1;
		}
		if (env->falling)
		{
			PWHERE.z += PVELOSITY.z;
			env->moving = 1;
		}
	}
}

void	h_collision(t_env *env, t_xy *p, t_xy *d, t_xy *dd)
{
	int			i;
	double		hole_low;
	double		hole_high;
	t_sector	s;
	t_xy		b;
	t_xy		pd;

	s = ESECTOR[PSECT];
	pd.x = p->x + dd->x;
	pd.y = p->y + dd->y;
	i = -1;
	while (++i < (int)s.npoints)
		if (intersect_box(*p, pd, s.vertex[i % s.npoints],
		s.vertex[(i + 1) % s.npoints]) &&
		point_side(pd.x, pd.y, s.vertex[i % s.npoints], s.vertex\
		[(i + 1) % s.npoints]) < 0)
		{
			hole_low = s.neighbors[i] < 0 ? 9e9 :
					MAX(s.floor, ESECTOR[s.neighbors[i]].floor);
			hole_high = s.neighbors[i] < 0 ? 9e9 :
					MIN(s.ceiling, ESECTOR[s.neighbors[i]].ceiling);
			if (hole_high < PWHERE.z + HEADMARGIN ||
				hole_low > PWHERE.z - EYEHEIGHT + KNEEHEIGHT)
			{
				b.x = s.vertex[(i + 1) % s.npoints].x -
						s.vertex[i % s.npoints].x;
				b.y = s.vertex[(i + 1) % s.npoints].y -
						s.vertex[i % s.npoints].y;
				d->x = b.x * (d->x * b.x + b.y * d->y) /
						(b.x * b.x + b.y * b.y);
				d->y = b.y * (d->x * b.x + b.y * d->y) /
						(b.x * b.x + b.y * b.y);
				env->moving = 0;
			}
		}
	env->falling = 1;
}

int can_i_go(t_env *env, t_xy *p, double x, double y)
{
	double			oldx = x;
	double			oldy = y;
	double			a, b, c, s;
	double			hh[ESECTOR[PSECT].npoints];
	unsigned int	i = 0;
	unsigned int	ii = i % ESECTOR[PSECT].npoints;
	unsigned int	ii1 = (i + 1) % ESECTOR[PSECT].npoints;

	while (i < ESECTOR[PSECT].npoints)
	{
		a = sqrt(pow(p[i].x - oldx, 2) + pow(p[i].y - oldy, 2));
		b = sqrt(pow(p[ii1].x - oldx, 2) + pow(p[ii1].y - oldy, 2));
		c = sqrt(pow(p[i].x - p[ii1].x, 2) + pow(p[i].y - p[ii1].y, 2));
		s = 0.25 * sqrt(pow(pow(a, 2) + pow(b, 2) + pow(c, 2), 2) \
			- 2 * (pow(a, 4) + pow(b, 4) + pow(c, 4)));
		hh[i] = (2 * s) / c;
		if (hh[ii] < 0.1 && (ESECTOR[PSECT].neighbors[ii] == -1))
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
	t_xy 			points[ESECTOR[PSECT].npoints];
	unsigned int 	counter = 0;

	p.x = PWHERE.x;
	p.y = PWHERE.y;
	dp.x = p.x + dx;
	dp.y = p.y + dy;
	sect = ESECTOR[PSECT];

	s = -1;
	while (++s < (int)sect.npoints)
		if (sect.neighbors[s] >= 0 && intersect_box(p, dp, sect.vertex[s % \
		sect.npoints], sect.vertex[(s + 1) % sect.npoints]) && \
		point_side(dp.x, dp.y, sect.vertex[s % sect.npoints], sect.vertex\
		[(s + 1) % sect.npoints]) < 0)
		{
			PSECT = sect.neighbors[s];
			break ;
		}
	while (i < ESECTOR[PSECT].npoints)
	{
		points[i].x = sect.vertex[i].x;
		points[i].y = sect.vertex[i].y;
		i++;
	}

	i = 0;
	while (i < sect.npoints)
	{
		if (points[(i + 1) % sect.npoints].x && (points[(i + 1) % sect.npoints].x - points[(i + 1) % ESECTOR[PSECT].npoints].x == 0 || points[i + 1].y - points[(i + 1) % ESECTOR[PSECT].npoints].y == 0))
			counter++;
		else if (!points[i].x && (points[0].x - points[(i + 1) % ESECTOR[PSECT].npoints].x == 0 || points[0].y - points[(i + 1) % ESECTOR[PSECT].npoints].y == 0))
			counter++;
		i++;
	}
	if (can_i_go(env, points, PWHERE.x + dx, PWHERE.y + dy))
	{
		PWHERE.x += dx;
		PWHERE.y += dy;
	}
}

void	wsad_read(t_env *env)
{
	t_xy	mv;
	t_xy	dmv;

	mv.x = 0;
	mv.y = 0;
	
	// env->wsad[0] ? mv.x += cos(PANGLE) * 0.2, mv.y += sin(PANGLE) * 0.2 : 0.0;
	// env->wsad[1] ? mv.x -= cos(PANGLE) * 0.2, mv.y -= sin(PANGLE) * 0.2 : 0.0;
	// env->wsad[2] ? mv.x += sin(PANGLE) * 0.2, mv.y -= cos(PANGLE) * 0.2 : 0.0;
	// env->wsad[3] ? mv.x -= sin(PANGLE) * 0.2, mv.y += cos(PANGLE) * 0.2 : 0.0;

	if (env->wsad[0])
	{
		mv.x += cos(PANGLE) * 0.2;
		mv.y += sin(PANGLE) * 0.2;
	}
	if (env->wsad[1])
	{
		mv.x -= cos(PANGLE) * 0.2;
		mv.y -= sin(PANGLE) * 0.2;
	}
	if (env->wsad[2])
	{
		mv.x += sin(PANGLE) * 0.2;
		mv.y -= cos(PANGLE) * 0.2;
	}
	if (env->wsad[3])
	{
		mv.x -= sin(PANGLE) * 0.2;
		mv.y += cos(PANGLE) * 0.2;
	}
	dmv.x = 0;
	dmv.y = 0;
	if (env->wsad[0])
	{
		dmv.x += cos(PANGLE) * 1;
		dmv.y += sin(PANGLE) * 1;
	}
	if (env->wsad[1])
	{
		dmv.x -= cos(PANGLE) * 1;
		dmv.y -= sin(PANGLE) * 1;
	}
	if (env->wsad[2])
	{
		dmv.x += sin(PANGLE) * 1;
		dmv.y -= cos(PANGLE) * 1;
	}
	if (env->wsad[3])
	{
		dmv.x -= sin(PANGLE) * 1;
		dmv.y += cos(PANGLE) * 1;
	}
	PVELOSITY.x = mv.x;
	PVELOSITY.y = mv.y;
	env->player.dvelocity.x = dmv.x;
	env->player.dvelocity.y = dmv.y;
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
		p.x = PWHERE.x;
		p.y = PWHERE.y;
		d.x = PVELOSITY.x;
		d.y = PVELOSITY.y;
		dd.x = env->player.dvelocity.x;
		dd.y = env->player.dvelocity.y;
		v_collision(env);
		h_collision(env, &p, &d, &dd);
		movement(env, d.x, d.y);
	}
	movement(env, 0, 0);
}
