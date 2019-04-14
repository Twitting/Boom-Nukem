/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:10:46 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 18:08:39 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	v_collision_support(t_env *env)
{
	double	nz;

	env->player.velocity.z -= (0.05 * 60.0 / (double)env->oldfps);
	nz = env->player.where.z + env->player.velocity.z;
	if (env->player.velocity.z < 0 && nz <
			env->sector[env->player.sector].floor + env->player.eye)
	{
		env->player.where.z = env->sector[env->player.sector].floor
			+ env->player.eye;
		env->player.velocity.z = 0;
		env->falling = 0;
		env->ground = 1;
		
	}
	else if (env->player.velocity.z > 0 &&
			nz > env->sector[env->player.sector].ceiling)
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

void	v_collision(t_env *env)
{
	env->ground = !env->falling;
	env->player.eye = env->ducking ? DUCKHEIGHT : EYEHEIGHT;
	if (env->falling)
		v_collision_support(env);
}

void	h_collision_support(t_env *env, double *arr, t_xy *b_pd, t_xy *d, int s)
{
	arr[1] = env->sector[env->player.sector].neighbors[s] < 0 ? 9e9 : MAX(env->sector[env->player.sector].floor, env->sector[env->sector[env->player.sector].neighbors[s]].floor);
	arr[2] = env->sector[env->player.sector].neighbors[s] < 0 ? 9e9 : MIN(env->sector[env->player.sector].ceiling, env->sector[env->sector[env->player.sector].neighbors[s]].ceiling);
	if (arr[2] < env->player.where.z + HEADMARGIN || arr[1] > env->player.where.z - (env->ducking ? DUCKHEIGHT : EYEHEIGHT) + KNEEHEIGHT)
	{
		b_pd[0].x = env->sector[env->player.sector].vertex[(s + 1) % env->sector[env->player.sector].npoints].x - env->sector[env->player.sector].vertex[s % env->sector[env->player.sector].npoints].x;
		b_pd[0].y = env->sector[env->player.sector].vertex[(s + 1) % env->sector[env->player.sector].npoints].y - env->sector[env->player.sector].vertex[s % env->sector[env->player.sector].npoints].y;
		arr[0] = d->x;
		d->x = b_pd[0].x * (d->x * b_pd[0].x + b_pd[0].y * d->y) / (b_pd[0].x * b_pd[0].x + b_pd[0].y * b_pd[0].y);
		d->y = b_pd[0].y * (arr[0] * b_pd[0].x + b_pd[0].y * d->y) / (b_pd[0].x * b_pd[0].x + b_pd[0].y * b_pd[0].y);
		env->moving = -1;
	}
}

int		h_collision(t_env *env, t_xy *p, t_xy *d, t_xy *dd)
{
	int		s;
	double	arr[3];
	t_xy	b_pd[2];

	b_pd[1].x = p->x + dd->x;
	b_pd[1].y = p->y + dd->y;
	s = -1;
	while (++s < env->sprcount)
		if (env->sprite[s].type == 2)
			if (intersect_box(*p, b_pd[1], env->sprite[s].pos1, env->sprite[s].pos2) && point_side(b_pd[1].x, b_pd[1].y, env->sprite[s].pos1, env->sprite[s].pos2) < 0)
			{
				b_pd[0].x = env->sprite[s].pos2.x - env->sprite[s].pos1.x;
				b_pd[0].y = env->sprite[s].pos2.y - env->sprite[s].pos1.y;
				arr[0] = d->x;
				d->x = b_pd[0].x * (d->x * b_pd[0].x + b_pd[0].y * d->y) / (b_pd[0].x * b_pd[0].x + b_pd[0].y * b_pd[0].y);
				d->y = b_pd[0].y * (arr[0] * b_pd[0].x + b_pd[0].y * d->y) / (b_pd[0].x * b_pd[0].x + b_pd[0].y * b_pd[0].y);
				env->moving = -1;
				return(0);
			}
	s = -1;
	while (++s < (int)env->sector[env->player.sector].npoints)
	{
		if (intersect_box(*p, b_pd[1], env->sector[env->player.sector].vertex[s % env->sector[env->player.sector].npoints], env->sector[env->player.sector].vertex[(s + 1) % env->sector[env->player.sector].npoints]) && point_side(b_pd[1].x, b_pd[1].y, env->sector[env->player.sector].vertex[s % env->sector[env->player.sector].npoints], env->sector[env->player.sector].vertex[(s + 1) % env->sector[env->player.sector].npoints]) < 0)
		{
			arr[1] = env->sector[env->player.sector].neighbors[s] < 0 ? 9e9 : MAX(env->sector[env->player.sector].floor, env->sector[env->sector[env->player.sector].neighbors[s]].floor);
			arr[2] = env->sector[env->player.sector].neighbors[s] < 0 ? 9e9 : MIN(env->sector[env->player.sector].ceiling, env->sector[env->sector[env->player.sector].neighbors[s]].ceiling);
			if (arr[2] < env->player.where.z + HEADMARGIN || arr[1] > env->player.where.z - (env->ducking ? DUCKHEIGHT : EYEHEIGHT) + KNEEHEIGHT)
				h_collision_support(env, arr, b_pd, d, s);
		}
	}
	env->falling = 1;
	return (0);
}

int		can_i_go(t_env *env, t_xy *p, double x, double y)
{
	double			hh[env->sector[env->player.sector].npoints];
	unsigned int	i;
	unsigned int	ii1;
	double			arr[6];

	i = 0;
	ii1 = (i + 1) % env->sector[env->player.sector].npoints;
	arr[0] = x;
	arr[1] = y;
	while (i < env->sector[env->player.sector].npoints)
	{
		arr[2] = sqrt(pow(p[i].x - arr[0], 2) + pow(p[i].y - arr[1], 2));
		arr[3] = sqrt(pow(p[ii1].x - arr[0], 2) + pow(p[ii1].y - arr[1], 2));
		arr[4] = sqrt(pow(p[i].x - p[ii1].x, 2) + pow(p[i].y - p[ii1].y, 2));
		arr[5] = 0.25 * sqrt(pow(pow(arr[2], 2) + pow(arr[3], 2) + pow(arr[4], 2), 2) - 2 * (pow(arr[2], 4) + pow(arr[3], 4) + pow(arr[4], 4)));
		hh[i] = (2 * arr[5]) / arr[4];
		//if (arr[2] < 1 || arr[3] < 1)
		//	return (0);
		i++;
	}
	return (1);
}

void	movement_support(t_env *env, float dx, float dy)
{
	int i;

	i = 0;
	while (i < env->sprcount)
	{
		if (env->sprite[i].spritedist < env->sprite[i].width * 2 && env->sprite[i].type != 2 && env->sprite[i].type != 3 && env->sprite[i].type != 5)
		{
			env->player.where.x -= dy;
			env->player.where.y -= dx;
			return ;
		}
		i++;
	}
	env->player.where.x += dx;
	env->player.where.y += dy;
}

void	movement(t_env *env, float dx, float dy)
{
	t_sector		sect;
	int				arr2[2];
	t_xy			points[env->sector[env->player.sector].npoints];
	t_xy			arr[2];

	arr[0].x = env->player.where.x;
	arr[0].y = env->player.where.y;
	arr[1].x = arr[0].x + dx;
	arr[1].y = arr[0].y + dy;
	sect = env->sector[env->player.sector];
	arr2[0] = -1;
	arr2[1] = -1;
	while (++arr2[0] < (int)env->sector[env->player.sector].npoints)
		if (sect.neighbors[arr2[0]] < 0)
			if (intersect_box(arr[0], arr[1], env->sector[env->player.sector].vertex[arr2[0] % env->sector[env->player.sector].npoints], env->sector[env->player.sector].vertex[(arr2[0] + 1) % env->sector[env->player.sector].npoints]) && point_side(arr[1].x,arr[1].y, env->sector[env->player.sector].vertex[arr2[0] % env->sector[env->player.sector].npoints], env->sector[env->player.sector].vertex[(arr2[0] + 1) % env->sector[env->player.sector].npoints]) < 0)
				return ;
	arr2[0] = -1;
	while (++arr2[0] < (int)sect.npoints)
		if (sect.neighbors[arr2[0]] >= 0 && intersect_box(arr[0], arr[1], sect.vertex[arr2[0] % sect.npoints], sect.vertex[(arr2[0] + 1) % sect.npoints]) && point_side(arr[1].x, arr[1].y, sect.vertex[arr2[0] % sect.npoints], sect.vertex[(arr2[0] + 1) % sect.npoints]) < 0)
		{
			env->player.sector = sect.neighbors[arr2[0]];
			break ;
		}
	while (++arr2[1] < (int)env->sector[env->player.sector].npoints)
	{
		points[arr2[1]].x = sect.vertex[arr2[1]].x;
		points[arr2[1]].y = sect.vertex[arr2[1]].y;
	}
	if (can_i_go(env, points, env->player.where.x + dx, env->player.where.y + dy))
		movement_support(env, dx, dy);
}

t_xy	wsad_read_support(t_env *env, t_xy mv)
{
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
	return (mv);
}

t_xy	wsad_read_support2(t_env *env, t_xy dmv)
{
	if (env->wsad[0])
	{
		dmv.x += cos(env->player.angle) * 2.0;
		dmv.y += sin(env->player.angle) * 2.0;
	}
	if (env->wsad[1])
	{
		dmv.x -= cos(env->player.angle) * 2.0;
		dmv.y -= sin(env->player.angle) * 2.0;
	}
	if (env->wsad[2])
	{
		dmv.x += sin(env->player.angle) * 2.0;
		dmv.y -= cos(env->player.angle) * 2.0;
	}
	if (env->wsad[3])
	{
		dmv.x -= sin(env->player.angle) * 2.0;
		dmv.y += cos(env->player.angle) * 2.0;
	}
	return (dmv);
}

void	wsad_read(t_env *env)
{
	t_xy	mv;
	t_xy	dmv;

	mv.x = 0;
	mv.y = 0;
	mv = wsad_read_support(env, mv);
	dmv.x = 0;
	dmv.y = 0;
	dmv = wsad_read_support2(env, dmv);
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
