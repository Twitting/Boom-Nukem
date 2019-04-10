/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movemob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:06:32 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/10 17:03:53 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void move_mob(t_env *env)
{

    t_xy oldPos;
    t_xy VeryOldPos;
    t_xy playerPos;
    t_sector sect;
    int arr2[4];

    arr2[1] = 0;
    int i = -1;
    playerPos.x = env->player.where.x;
    playerPos.y = env->player.where.y;
    while (++i < env->sprcount)
    {
		arr2[0] = -1;
        if (env->sprite[i].visible && env->sprite[i].type == 1)
		{
			env->sprite[i].movecount++;
			sect = env->sector[env->sprite[i].sector];
			oldPos.x = env->sprite[i].pos1.x;
			oldPos.y = env->sprite[i].pos1.y;
			VeryOldPos.x = env->sprite[i].pos1.x;
			VeryOldPos.y = env->sprite[i].pos1.y;
			double deltaX = fabs(playerPos.x - oldPos.x);
			double deltaY = fabs(playerPos.y - oldPos.y);
			double signX = oldPos.x < playerPos.x ? 0.15 : -0.15;
			double signY = oldPos.y < playerPos.y ? 0.15 : -0.15;
			double error = deltaX - deltaY;       
			while (fabs(oldPos.x - playerPos.x) > 2.0 || fabs(oldPos.y - playerPos.y) > 2.0)
			{

				double error2 = error * 2;
				if (error2 > -deltaY)
				{
					error -= deltaY;
					oldPos.x += signX / 60 * env->oldfps;
				}
				if (error2 < deltaX)
				{
					error += deltaX;
					oldPos.y += signY / 60 * env->oldfps;
				}
				while (++arr2[0] < (int)sect.npoints)
				{
					if (sect.neighbors[arr2[0]] >= 0 && intersect_box(VeryOldPos, oldPos, sect.vertex[arr2[0] % sect.npoints], sect.vertex[(arr2[0] + 1) % sect.npoints]) && point_side(oldPos.x, oldPos.y, sect.vertex[arr2[0] % sect.npoints], sect.vertex[(arr2[0] + 1) % sect.npoints]) < 0)                    
					{
						printf("sector:%d\n", env->sprite[i].sector);
						env->sprite[i].sector = sect.neighbors[arr2[0]];
						env->sprite[i].movecount = 0;
						arr2[2] = env->sprite[i].texnum - 1;
						arr2[3] = -1;
						while (++arr2[3] < 7)
						{
							enemylightapply(env, &env->sprite[i], arr2[2]);
							arr2[2] = arr2[2] == 6 ? 0 : arr2[2] + 1;
						}
					}
				}
				env->sprite[i].pos1.x = oldPos.x;
				env->sprite[i].pos1.y = oldPos.y;
				break;
			}
    	}
    }
}