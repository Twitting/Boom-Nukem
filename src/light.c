/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:24:25 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 12:31:27 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	spritelightapply(t_env *env, t_sprite *sprite)
{
	int				j;
	int				k;
	unsigned char	*pix;

	if (SPRTE[0] != NULL)
		SDL_FreeSurface(SPRTE[0]);
	SPRTE[0] = sprite->type == 0 ? IMG_Load("textures/barrel.png") : IMG_Load("textures/med.png");
	pix = (unsigned char *)SPRTE[0]->pixels;
	j = -1;
	while (++j < SPRTE[0]->h)
	{
		k = -1;
		while (++k < SPRTE[0]->w - 1)
		{
			pix[(j * SPRTE[0]->w + k) * 4] = ESECT3] / 100 * ESEC[sprite->sector].light);
			pix[(j * SPRTE[0]->w + k) * 4 + 1] = ESECT3 + 1] / 100 * ESEC[sprite->sector].light);
			pix[(j * SPRTE[0]->w + k) * 4 + 2] = ESECT3 + 2] / 100 * ESEC[sprite->sector].light);
		}
	}
}

void	sectorlightapply_support(t_env *env, int *ijkt, unsigned char *pix)
{
	pix[(ijkt[1] * ESECT->w + ijkt[2]) * 4] = ESECT2] / 100 * ESEC[ijkt[0]].light);
	pix[(ijkt[1] * ESECT->w + ijkt[2]) * 4 + 1] = ESECT2 + 1] / 100 * ESEC[ijkt[0]].light);
	pix[(ijkt[1] * ESECT->w + ijkt[2]) * 4 + 2] = ESECT2 + 2] / 100 * ESEC[ijkt[0]].light);
}

char	*gettex(t_env *env, int secnum, int tex)
{
	if (((TEXP == 0 || TEXP == 4) && tex == 0) || (TEXP == 5 && tex == 2))
		return ("textures/asphalt.tga");
	if ((TEXP == 0 && tex == 1) || (TEXP == 1 && tex == 1))
		return ("textures/brick.tga");
	if (((TEXP == 0 || TEXP == 1 || TEXP == 2) && tex == 2) || TEXP == 2)
		return ("textures/metal.tga");
	if (((TEXP == 1 || TEXP == 5) && tex == 0) || (TEXP == 3 && tex == 1))
		return ("textures/stone.tga");
	return ("textures/wood.tga");
}

void	sectorlightapply(t_env *env)
{
	unsigned char	*pix;
	int				ijkt[4];

	ijkt[3] = -1;
	while (++ijkt[3] < 3)
	{
		ijkt[0] = -1;
		while (++ijkt[0] < (int)env->nsectors)
		{
			if (ESEC[ijkt[0]].sky == 1)
				ESEC[ijkt[0]].light = 100;
			if (ESECT != NULL)
				SDL_FreeSurface(ESECT);
			ESECT = IMG_Load(gettex(env, ijkt[0], ijkt[3]));
			pix = (unsigned char *)ESECT->pixels;
			ijkt[1] = -1;
			while (++ijkt[1] < ESECT->h)
			{
				ijkt[2] = -1;
				while (++ijkt[2] < ESECT->w)
					sectorlightapply_support(env, ijkt, pix);
			}
		}
	}
}
