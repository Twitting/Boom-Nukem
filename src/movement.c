/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:10:46 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 16:06:44 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void		movement(t_env *env, float dx, float dy)
{
	t_sector		sect;
	int				arr2[2];
	t_xy			points[ESEC[EPS].NP];
	t_xy			arr[2];

	sect = movement_support2(arr, arr2, env);
	arr[1].x = arr[0].x + dx;
	arr[1].y = arr[0].y + dy;
	while (++A1 < (int)ESEC[EPS].NP)
		if (WTF1 < 0)
			if (i_b(arr[0], arr[1], ESEC[EPS].VT[A1 % ESEC[EPS].NP],
	ESEC[EPS].VT[(A1 + 1) % ESEC[EPS].NP]) && point_side(arr[1].x, arr[1].y,
	ESEC[EPS].VT[A1 % ESEC[EPS].NP], ESEC[EPS].VT[(A1 + 1) % ESEC[EPS].NP]) < 0)
				return ;
	A1 = -1;
	while (++A1 < (int)SNP)
		if (WTF1 >= 0 && i_b(arr[0], arr[1], SV[A1
		% SNP], SV[(A1 + 1) % SNP]) && point_side(
		arr[1].x, arr[1].y, SV[A1 % SNP], SV[(A1 + 1) % SNP]) < 0)
		{
			EPS = sect.neighbors[A1];
			break ;
		}
	movement_support3(env, sect, arr2, points);
	movement_support(env, dx, dy);
}

t_xy		wsad_read_support(t_env *env, t_xy mv)
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

t_xy		wsad_read_support2(t_env *env, t_xy dmv)
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

void		wsad_read(t_env *env)
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

void		movement_calcs(t_env *env)
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
