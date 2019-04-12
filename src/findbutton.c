/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbutton.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:33:24 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/12 14:33:47 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	findbutton_di(t_env *env, int i, int s, t_xy *xy)
{
	if (env->sector[i].vertex[s % env->sector[i].npoints].x < env->sector[i].vertex[(s + 1) % env->sector[i].npoints].x)
		xy->x = env->button[i].x1 + 0.1;
	else
		xy->x = env->button[i].x1 - 0.1;
	xy->y = (xy->x - env->sector[i].vertex[s % env->sector[i].npoints].x) *
	(env->sector[i].vertex[(s + 1) % env->sector[i].npoints].y -
	env->sector[i].vertex[s % env->sector[i].npoints].y) / (env->sector[i].vertex[(s + 1) %
	env->sector[i].npoints].x - env->sector[i].vertex[s % env->sector[i].npoints].x) +
	env->sector[i].vertex[s % env->sector[i].npoints].y;
	while (((xy->x - env->button[i].x1) * (xy->x - env->button[i].x1) + (xy->y - env->button[i].y1) * (xy->y - env->button[i].y1)) < BUTTONWIDTH)
	{
		xy->y = (xy->x - env->sector[i].vertex[s % env->sector[i].npoints].x) *
		(env->sector[i].vertex[(s + 1) % env->sector[i].npoints].y -
		env->sector[i].vertex[s % env->sector[i].npoints].y) / (env->sector[i].vertex[(s + 1) %
		env->sector[i].npoints].x - env->sector[i].vertex[s % env->sector[i].npoints].x) +
		env->sector[i].vertex[s % env->sector[i].npoints].y;
		if (env->sector[i].vertex[s % env->sector[i].npoints].x < env->sector[i].vertex[(s + 1) % env->sector[i].npoints].x)
			xy->x += 0.1;
		else
			xy->x -= 0.1;
	}
}

void	findbutton_hv(t_env *env, int i, int s)
{
	t_xy	xy;

	env->button[i].x1 = (env->sector[i].vertex[s % env->sector[i].npoints].x + env->sector[i].vertex[(s + 1) % env->sector[i].npoints].x) / 2;
	env->button[i].y1 = (env->sector[i].vertex[s % env->sector[i].npoints].y + env->sector[i].vertex[(s + 1) % env->sector[i].npoints].y) / 2;
	if (env->sector[i].vertex[s % env->sector[i].npoints].x == env->sector[i].vertex[(s + 1) % env->sector[i].npoints].x)
	{
		xy.x = env->button[i].x1;
		if (env->sector[i].vertex[s % env->sector[i].npoints].y < env->sector[i].vertex[(s + 1) % env->sector[i].npoints].y)
			xy.y = env->button[i].y1 + BUTTONWIDTH;
		else
			xy.y = env->button[i].y1 - BUTTONWIDTH;
	}
	else if (env->sector[i].vertex[s % env->sector[i].npoints].y == env->sector[i].vertex[(s + 1) % env->sector[i].npoints].y)
	{
		xy.y = env->button[i].y1;
		if (env->sector[i].vertex[s % env->sector[i].npoints].x < env->sector[i].vertex[(s + 1) % env->sector[i].npoints].x)
			xy.x = env->button[i].x1 + BUTTONWIDTH;
		else
			xy.x = env->button[i].x1 - BUTTONWIDTH;
	}
	else
		findbutton_di(env, i, s, &xy);
	env->button[i].x2 = xy.x;
	env->button[i].y2 = xy.y;
}

void	findbutton(t_env *env)
{
	unsigned int	s;
	unsigned int	i;

	i = -1;
	while (++i < env->nsectors)
	{
		s = -1;
		while (++s < env->sector[i].npoints)
			if (env->sector[i].neighbors[s] == -2)
				findbutton_hv(env, i, s);
	}
}
