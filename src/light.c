/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:24:25 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/12 12:25:09 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	spritelightapply(t_env *env, t_sprite *sprite)
{
	int j;
	int k;
	unsigned char *pix;
	
	if (sprite->texture[0] != NULL)
		SDL_FreeSurface(sprite->texture[0]);
	sprite->texture[0] = sprite->type == 0 ? IMG_Load("textures/barrel.png") : IMG_Load("textures/med.png");
	pix = (unsigned char *)sprite->texture[0]->pixels;
	j = -1;
	while (++j < sprite->texture[0]->h)
	{
		k = -1;
		while (++k < sprite->texture[0]->w - 1)
		{
			pix[(j * sprite->texture[0]->w + k) * 4] = (unsigned char)((double)pix[(j * sprite->texture[0]->w + k) * 4] / 100 * env->sector[sprite->sector].light);
			pix[(j * sprite->texture[0]->w + k) * 4 + 1] = (unsigned char)((double)pix[(j * sprite->texture[0]->w + k) * 4 + 1] / 100 * env->sector[sprite->sector].light);
			pix[(j * sprite->texture[0]->w + k) * 4 + 2] = (unsigned char)((double)pix[(j * sprite->texture[0]->w + k) * 4 + 2] / 100 * env->sector[sprite->sector].light);
		}
	}
}
