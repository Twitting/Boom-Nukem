/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:30:49 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 16:05:25 by twitting         ###   ########.fr       */
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

void	inittext_term(t_env *env)
{
	env->text[14] = IMG_Load("textures/t1.png");
	env->text[15] = IMG_Load("textures/t2.png");
	env->text[16] = IMG_Load("textures/t3.png");
	env->text[17] = IMG_Load("textures/t4.png");
	env->text[18] = IMG_Load("textures/t5.png");
	env->text[19] = IMG_Load("textures/t6.png");
	env->text[20] = IMG_Load("textures/t7.png");
	env->text[21] = IMG_Load("textures/t8.png");
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