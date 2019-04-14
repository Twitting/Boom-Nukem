/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotatinglight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:39:17 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 16:06:15 by twitting         ###   ########.fr       */
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
	if (SPRTE[tex] != NULL)
		SDL_FreeSurface(SPRTE[tex]);
	SPRTE[tex] = IMG_Load(gettexenemy(tex, sprite));
	pix = (unsigned char *)SPRTE[tex]->pixels;
	j = -1;
	while (++j < SPRTE[tex]->h)
	{
		k = -1;
		while (++k < SPRTE[tex]->w - 1)
		{
			pix[(j * SPRTE[tex]->w + k) * 4] = (unsigned char)((double)pix[(j * SPRTE[tex]->w + k) * 4] / 100 * ESEC[sprite->sector].light);
			pix[(j * SPRTE[tex]->w + k) * 4 + 1] = (unsigned char)((double)pix[(j * SPRTE[tex]->w + k) * 4 + 1] / 100 * ESEC[sprite->sector].light);
			pix[(j * SPRTE[tex]->w + k) * 4 + 2] = (unsigned char)((double)pix[(j * SPRTE[tex]->w + k) * 4 + 2] / 100 * ESEC[sprite->sector].light);
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
		if (ESPRI.type == 0 || ESPRI.type == 3)
			spritelightapply(env, &ESPRI);
		if (ESPRI.type == 1)
			while (++j < 7)
				enemylightapply(env, &ESPRI, j);
		else if (ESPRI.type == 5)
			while (++j < 8)
				keylightapply(env, &ESPRI, j);
	}
}
