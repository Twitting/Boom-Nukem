/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:17:10 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/11 14:46:45 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <render.h>

void    shoot(t_env *env, SDL_Event *e)
{
	int	i;

    if (e->button.button == SDL_BUTTON_LEFT)
        if (env->player.target >= 0)
        {
			
			i = -1;
			while (++i < env->sprcount)
				if (env->sprite[i].type == 5)
				{
					printf("shoot ");
					env->sprite[i].pos1.x = env->player.where.x;
					env->sprite[i].pos1.y = env->player.where.y;
					env->sprite[i].sector = env->player.sector;
					env->sprite[i].width = 1;
					env->bx = env->player.velocity.x;
					env->by = env->player.velocity.y;
				}
            env->sprite[env->player.target].hp -= 35;
            if (env->sprite[env->player.target].hp <= 0)
                env->sprite[env->player.target].type = 4;
           // printf("%d\n",env->sprite[env->player.target].hp);
        }
}

void    cross(t_env *env)
{
    int            i;
    int            *pix1;
    int            *pix2;

    pix1 = (int*)env->surface->pixels;
    pix2 = (int*)env->surface->pixels;
    pix1 += (HWIN / 2 - 6) * WWIN + WWIN / 2;
    i = -1;
    while (++i <= 12)
    {
        *pix1 = 0xffffff;
        pix1 += WWIN;
    }
    pix2 += HWIN / 2 * WWIN + WWIN / 2 - 6;
    i = -1;
    while (++i <= 12)
    {
        *pix2 = 0xffffff;
        pix2 += 1;
    }
}