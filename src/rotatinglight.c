/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotatinglight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:39:17 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 10:40:02 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

char	*gettexenemy(int tex, t_sprite *sprite)
{
	if (sprite->type == 4)
		return ("textures/dead.png");
	if (tex == 0)
		return ("textures/1.png");
	else if (tex == 1)
		return ("textures/2.png");
	else if (tex == 2)
		return ("textures/3.png");
	else if (tex == 3)
		return ("textures/4.png");
	else if (tex == 4)
		return ("textures/5.png");
	else if (tex == 5)
		return ("textures/6.png");
	return ("textures/7.png");
}

void	enemylightapply(t_env *env, t_sprite *sprite, int tex)
{
	int				j;
	int				k;
	unsigned char	*pix;

	sprite->hp = 100;
	sprite->movecount = 0;
	sprite->texnum = 0;
	sprite->mobtimer = 0;
	if (sprite->texture[tex] != NULL)
		SDL_FreeSurface(sprite->texture[tex]);
	sprite->texture[tex] = IMG_Load(gettexenemy(tex, sprite));
	pix = (unsigned char *)sprite->texture[tex]->pixels;
	j = -1;
	while (++j < sprite->texture[tex]->h)
	{
		k = -1;
		while (++k < sprite->texture[tex]->w - 1)
		{
			pix[(j * sprite->texture[tex]->w + k) * 4] = (unsigned char)((double)pix[(j * sprite->texture[tex]->w + k) * 4] / 100 * env->sector[sprite->sector].light);
			pix[(j * sprite->texture[tex]->w + k) * 4 + 1] = (unsigned char)((double)pix[(j * sprite->texture[tex]->w + k) * 4 + 1] / 100 * env->sector[sprite->sector].light);
			pix[(j * sprite->texture[tex]->w + k) * 4 + 2] = (unsigned char)((double)pix[(j * sprite->texture[tex]->w + k) * 4 + 2] / 100 * env->sector[sprite->sector].light);
		}
	}
}

void	initspritelight(t_env *env)
{
	int	i;
	int	j;

	i = -1;
	while (++i < env->sprcount)
	{
		j = -1;
		if (env->sprite[i].type == 0 || env->sprite[i].type == 3)
			spritelightapply(env, &env->sprite[i]);
		if (env->sprite[i].type == 1)
			while (++j < 7)
				enemylightapply(env, &env->sprite[i], j);
		else if (env->sprite[i].type == 5)
			while (++j < 8)
				keylightapply(env, &env->sprite[i], j);
	}
}