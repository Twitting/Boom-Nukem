/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:30:49 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 07:35:03 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

char	*gettexkey(int tex)
{
	if (tex == 0)
		return ("textures/k1.png");
	else if (tex == 1)
		return ("textures/k2.png");
	else if (tex == 2)
		return ("textures/k3.png");
	else if (tex == 3)
		return ("textures/k4.png");
	else if (tex == 4)
		return ("textures/k5.png");
	else if (tex == 5)
		return ("textures/k6.png");
	else if (tex == 6)
		return ("textures/k7.png");
	return ("textures/k8.png");
}

void	keylightapply(t_env *env, t_sprite *sprite, int tex)
{
	int				j;
	int				k;
	unsigned char	*pix;

	sprite->movecount = 0;
	sprite->texnum = 0;
	sprite->mobtimer = 0;
	if (sprite->texture[tex] != NULL)
		SDL_FreeSurface(sprite->texture[tex]);
	sprite->texture[tex] = IMG_Load(gettexkey(tex));
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