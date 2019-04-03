/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:38:09 by twitting          #+#    #+#             */
/*   Updated: 2019/04/03 20:33:01 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	sectorlightapply(t_env *env)
{
	int	i;
	int j;
	int k;
	unsigned char *pix;
	
	i = -1;
	while (++i < (int)env->nsectors)
	{
		env->sector[i].text = IMG_Load("textures/brick.tga");
		pix = (unsigned char *)env->sector[i].text->pixels;
		j = -1;
		while (++j < env->sector[i].text->h)
		{
			k = -1;
			while (++k < env->sector[i].text->w)
			{
				pix[(j * env->sector[i].text->h + k) * 4] = (unsigned char)((double)pix[(j * env->sector[i].text->h + k) * 4] / 100 * env->sector[i].light);
				pix[(j * env->sector[i].text->h + k) * 4 + 1] = (unsigned char)((double)pix[(j * env->sector[i].text->h + k) * 4 + 1] / 100 * env->sector[i].light);
				pix[(j * env->sector[i].text->h + k) * 4 + 2] = (unsigned char)((double)pix[(j * env->sector[i].text->h + k) * 4 + 2] / 100 * env->sector[i].light);
			}
		}

	}
}

void	init(t_env *env)
{
	env->yaw = 0;
	env->quit = 0;
	env->ground = 0;
	env->falling = 1;
	env->ducking = 0;
	env->player.eye = EYEHEIGHT;
	env->fps = 0;
	env->oldfps = 60;
	env->timer = 0;
	env->sprcount = 3;
	sectorlightapply(env);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_error(4);
	else
	{
		if (!(env->window = SDL_CreateWindow("Doom Nukem 2,5D",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WWIN, HWIN, SDL_WINDOW_OPENGL + SDL_WINDOW_ALLOW_HIGHDPI)))
			ft_error(4);
		env->surface = SDL_GetWindowSurface(env->window);
	if (!(env->sprite = (t_sprite *)malloc(sizeof(t_sprite) * env->sprcount)))
		ft_error(2);
	env->sprite[0].x = 24;
	env->sprite[0].y = 40;
	env->sprite[0].height = 12;
	env->sprite[0].width = 4;
	}
}
