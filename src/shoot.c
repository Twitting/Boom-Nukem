/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:17:10 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 15:28:21 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <render.h>

void	shoot(t_env *env, SDL_Event *e)
{
	if (e->button.button == SDL_BUTTON_LEFT && ESHOOT == 0)
	{
		Mix_PlayChannel(-1, env->sound[0], 0);
		ESHOOT = 11;
		if (env->player.target >= 0)
		{
			Mix_PlayChannel(-1, env->sound[6], 0);
			env->sprite[env->player.target].hp -= 35;
			if (env->sprite[env->player.target].hp <= 0)
			{
				Mix_PlayChannel(-1, env->sound[7], 0);
				env->sprite[env->player.target].type = 4;
			}
		}
	}
}

void	cross(t_env *env)
{
	int i;
	int *pix1;
	int *pix2;

	pix1 = (int *)env->surface->pixels;
	pix2 = (int *)env->surface->pixels;
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
