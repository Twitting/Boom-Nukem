/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:38:37 by daharwoo          #+#    #+#             */
/*   Updated: 2019/04/15 16:08:12 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

int			h_collision(t_env *env, t_xy *p, t_xy *d, t_xy *dd)
{
	if (!h_collision_pt1(env, p, d, dd))
		return (0);
	h_collision_pt2(env, p, d, dd);
	env->falling = 1;
	return (0);
}

void		movement_support(t_env *env, float dx, float dy)
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

t_sector	movement_support2(t_xy *arr, int *arr2, t_env *env)
{
	t_sector		sect;

	sect = ESEC[EPS];
	arr[0].x = EPW.x;
	arr[0].y = EPW.y;
	arr2[0] = -1;
	arr2[1] = -1;
	return (sect);
}

void		movement_support3(t_env *env, t_sector sect,
								int *arr2, t_xy *points)
{
	while (++arr2[1] < (int)ESEC[EPS].NP)
	{
		points[arr2[1]].x = SV[arr2[1]].x;
		points[arr2[1]].y = SV[arr2[1]].y;
	}
}
