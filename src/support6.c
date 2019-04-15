/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:38:37 by daharwoo          #+#    #+#             */
/*   Updated: 2019/04/15 16:03:38 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

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
		b_pd.x = ESEC[EPS].VT[(s + 1) %
				ESEC[EPS].npoints].x - ESEC[EPS].VT[s
				% ESEC[EPS].npoints].x;
		b_pd.y = ESEC[EPS].VT[(s + 1) %
				ESEC[EPS].npoints].y - ESEC[EPS].VT[s
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
		if (i_b(*p, b_pd, ESEC[EPS].VT[s % ESEC[EPS].npoints],
		ESEC[EPS].VT[(s + 1) % ESEC[EPS].npoints]) && point_side(b_pd.x,
		b_pd.y, ESEC[EPS].VT[s % ESEC[EPS].npoints],
		ESEC[EPS].VT[(s + 1) % ESEC[EPS].npoints]) < 0)
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
