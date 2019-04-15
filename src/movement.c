/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:10:46 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 15:06:51 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	v_collision_support(t_env *env)
{
	double	nz;

	env->player.velocity.z -= (0.05 * 60.0 / (double)env->oldfps);
	nz = EPW.z + env->player.velocity.z;
	if (env->player.velocity.z < 0 && nz <
			ESEC[EPS].floor + env->player.eye)
	{
		EPW.z = ESEC[EPS].floor
			+ env->player.eye;
		env->player.velocity.z = 0;
		env->falling = 0;
		env->ground = 1;
	}
	else if (env->player.velocity.z > 0 &&
			nz > ESEC[EPS].ceiling)
	{
		env->player.velocity.z = 0;
		env->falling = 1;
	}
	if (env->falling)
	{
		EPW.z += env->player.velocity.z;
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

void	h_collision_support(t_env *env, t_xy *d, int s)
{
	t_xy	b_pd;
	double	temp[3];

	b_pd.x = env->sprite[s].pos2.x - env->sprite[s].pos1.x;
	b_pd.y = env->sprite[s].pos2.y - env->sprite[s].pos1.y;
	temp[1] = ESEC[EPS].neighbors[s] < 0 ? 9e9 :
			MAX(ESEC[EPS].floor, ESEC[ESEC[EPS].neighbors[s]].floor);
	temp[2] = ESEC[EPS].neighbors[s] < 0 ? 9e9 :
			MIN(ESEC[EPS].ceiling, ESEC[ESEC[EPS].neighbors[s]].ceiling);
	if (temp[2] < EPW.z + HEADMARGIN || temp[1] > EPW.z
			- (env->ducking ? DUCKHEIGHT : EYEHEIGHT) + KNEEHEIGHT)
	{
		b_pd.x = ESEC[EPS].vertex[(s + 1) %
				ESEC[EPS].npoints].x - ESEC[EPS].vertex[s
				% ESEC[EPS].npoints].x;
		b_pd.y = ESEC[EPS].vertex[(s + 1) %
				ESEC[EPS].npoints].y - ESEC[EPS].vertex[s
				% ESEC[EPS].npoints].y;
		temp[0] = d->x;
		d->x = b_pd.x * (d->x * b_pd.x + b_pd.y * d->y) /
				(b_pd.x * b_pd.x + b_pd.y * b_pd.y);
		d->y = b_pd.y * (temp[0] * b_pd.x + b_pd.y * d->y) /
				(b_pd.x * b_pd.x + b_pd.y * b_pd.y);
		env->moving = -1;
	}
}

int		h_collision_pt1(t_env *env, t_xy *p, t_xy *d, t_xy *dd)
{
	int		s;
	double	arr;
	t_xy	b_pd[2];

	b_pd[1].x = p->x + dd->x;
	b_pd[1].y = p->y + dd->y;
	s = -1;
	while (++s < env->sprcount)
		if (env->sprite[s].type == 2)
			if (i_b(*p, b_pd[1], env->sprite[s].pos1, env->sprite[s].pos2)
			&& point_side(b_pd[1].x, b_pd[1].y, env->sprite[s].pos1,
			env->sprite[s].pos2) < 0)
			{
				b_pd[0].x = env->sprite[s].pos2.x - env->sprite[s].pos1.x;
				b_pd[0].y = env->sprite[s].pos2.y - env->sprite[s].pos1.y;
				arr = d->x;
				d->x = b_pd[0].x * (d->x * b_pd[0].x + b_pd[0].y * d->y) /
					(b_pd[0].x * b_pd[0].x + b_pd[0].y * b_pd[0].y);
				d->y = b_pd[0].y * (arr * b_pd[0].x + b_pd[0].y * d->y) /
					(b_pd[0].x * b_pd[0].x + b_pd[0].y * b_pd[0].y);
				env->moving = -1;
				return (0);
			}
	return (1);
}

void	h_collision_pt2(t_env *env, t_xy *p, t_xy *d, t_xy *dd)
{
	int		s;
	double	arr[2];
	t_xy	b_pd;

	b_pd.x = p->x + dd->x;
	b_pd.y = p->y + dd->y;
	s = -1;
	while (++s < (int)ESEC[EPS].NP)
	{
		if (i_b(*p, b_pd, ESEC[EPS].vertex[s % ESEC[EPS].npoints],
		ESEC[EPS].vertex[(s + 1) % ESEC[EPS].npoints]) && point_side(b_pd.x,
		b_pd.y, ESEC[EPS].vertex[s % ESEC[EPS].npoints],
		ESEC[EPS].vertex[(s + 1) % ESEC[EPS].npoints]) < 0)
		{
			arr[0] = ESEC[EPS].neighbors[s] < 0 ? 9e9 :
				MAX(ESEC[EPS].floor, ESEC[ESEC[EPS].neighbors[s]].floor);
			arr[1] = ESEC[EPS].neighbors[s] < 0 ? 9e9 :
				MIN(ESEC[EPS].ceiling, ESEC[ESEC[EPS].neighbors[s]].ceiling);
			if (arr[1] < EPW.z + HEADMARGIN || arr[0] > EPW.z -
				(env->ducking ? DUCKHEIGHT : EYEHEIGHT) + KNEEHEIGHT)
				h_collision_support(env, d, s);
		}
	}
}

int		h_collision(t_env *env, t_xy *p, t_xy *d, t_xy *dd)
{
	if (!h_collision_pt1(env, p, d, dd))
		return (0);
	h_collision_pt2(env, p, d, dd);
	env->falling = 1;
	return (0);
}

void	movement_support(t_env *env, float dx, float dy)
{
	int i;

	i = 0;
	while (i < env->sprcount)
	{
		if (ESPRI.spritedist < ESPRI.width * 2 && ESPRI.type == 0)
		{
			EPW.x -= dy;
			EPW.y -= dx;
			return ;
		}
		i++;
	}
	EPW.x += dx;
	EPW.y += dy;
}

void	movement_support2(t_xy *arr, int *arr2, t_env *env)
{
	arr[0].x = EPW.x;
	arr[0].y = EPW.y;
	arr2[0] = -1;
	arr2[1] = -1;
}

void	movement_support3(t_env *env, t_sector sect, int *arr2, t_xy *points)
{
	while (++arr2[1] < (int)ESEC[EPS].NP)
	{
		points[arr2[1]].x = SV[arr2[1]].x;
		points[arr2[1]].y = SV[arr2[1]].y;
	}
}

void	movement(t_env *env, float dx, float dy)
{
	t_sector		sect;
	int				arr2[2];
	t_xy			points[ESEC[EPS].NP];
	t_xy			arr[2];

	sect = ESEC[EPS];
	movement_support2(arr, arr2, env);
	arr[1].x = arr[0].x + dx;
	arr[1].y = arr[0].y + dy;
	while (++arr2[0] < (int)ESEC[EPS].NP)
		if (WTF1 < 0)
			if (i_b(arr[0], arr[1], ESEC[EPS].vertex[arr2[0] % ESEC[EPS].NP],
			ESEC[EPS].vertex[(arr2[0] + 1) % ESEC[EPS].NP]) && point_side(
			arr[1].x, arr[1].y, ESEC[EPS].vertex[arr2[0] % ESEC[EPS].NP],
			ESEC[EPS].vertex[(arr2[0] + 1) % ESEC[EPS].NP]) < 0)
				return ;
	arr2[0] = -1;
	while (++arr2[0] < (int)SNP)
		if (WTF1 >= 0 && i_b(arr[0], arr[1], SV[arr2[0]
		% SNP], SV[(arr2[0] + 1) % SNP]) && point_side(
		arr[1].x, arr[1].y, SV[arr2[0] % SNP], SV[(arr2[0] + 1) % SNP]) < 0)
		{
			EPS = sect.neighbors[arr2[0]];
			break ;
		}
	movement_support3(env, sect, arr2, points);
	movement_support(env, dx, dy);
}

t_xy	wsad_read_support(t_env *env, t_xy mv)
{
	if (env->wsad[0])
	{
		mv.x += cos(PANG) * 0.4;
		mv.y += sin(PANG) * 0.4;
	}
	if (env->wsad[1])
	{
		mv.x -= cos(PANG) * 0.4;
		mv.y -= sin(PANG) * 0.4;
	}
	if (env->wsad[2])
	{
		mv.x += sin(PANG) * 0.4;
		mv.y -= cos(PANG) * 0.4;
	}
	if (env->wsad[3])
	{
		mv.x -= sin(PANG) * 0.4;
		mv.y += cos(PANG) * 0.4;
	}
	return (mv);
}

t_xy	wsad_read_support2(t_env *env, t_xy dmv)
{
	if (env->wsad[0])
	{
		dmv.x += cos(PANG) * 2.0;
		dmv.y += sin(PANG) * 2.0;
	}
	if (env->wsad[1])
	{
		dmv.x -= cos(PANG) * 2.0;
		dmv.y -= sin(PANG) * 2.0;
	}
	if (env->wsad[2])
	{
		dmv.x += sin(PANG) * 2.0;
		dmv.y -= cos(PANG) * 2.0;
	}
	if (env->wsad[3])
	{
		dmv.x -= sin(PANG) * 2.0;
		dmv.y += cos(PANG) * 2.0;
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
		p.x = EPW.x;
		p.y = EPW.y;
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
