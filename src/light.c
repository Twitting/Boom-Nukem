/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:24:25 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/12 16:36:21 by twitting         ###   ########.fr       */
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

void	sectorlightapply_support(t_env *env, int *ijkt, unsigned char *pix)
{
	pix[(ijkt[1] * env->sector[ijkt[0]].text[ijkt[3]]->w + ijkt[2]) * 4] = (unsigned char)((double)pix[(ijkt[1] * env->sector[ijkt[0]].text[ijkt[3]]->w + ijkt[2]) * 4] / 100 * env->sector[ijkt[0]].light);
	pix[(ijkt[1] * env->sector[ijkt[0]].text[ijkt[3]]->w + ijkt[2]) * 4 + 1] = (unsigned char)((double)pix[(ijkt[1] * env->sector[ijkt[0]].text[ijkt[3]]->w + ijkt[2]) * 4 + 1] / 100 * env->sector[ijkt[0]].light);
	pix[(ijkt[1] * env->sector[ijkt[0]].text[ijkt[3]]->w + ijkt[2]) * 4 + 2] = (unsigned char)((double)pix[(ijkt[1] * env->sector[ijkt[0]].text[ijkt[3]]->w + ijkt[2]) * 4 + 2] / 100 * env->sector[ijkt[0]].light);
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

void	currentsectorlightapply(t_env *env, int secnum)
{
	unsigned char	*pix;
	int				ijkt[4];

	ijkt[3] = -1;
	while (++ijkt[3] < 3)
	{
		ijkt[0] = secnum;
		if (env->sector[ijkt[0]].sky == 1)
			env->sector[ijkt[0]].light = 100;
		if (env->sector[ijkt[0]].text[ijkt[3]] != NULL)
			SDL_FreeSurface(env->sector[ijkt[0]].text[ijkt[3]]);
		env->sector[ijkt[0]].text[ijkt[3]] = IMG_Load(gettex(env, ijkt[0], ijkt[3]));
		pix = (unsigned char *)env->sector[ijkt[0]].text[ijkt[3]]->pixels;
		ijkt[1] = -1;
		while (++ijkt[1] < env->sector[ijkt[0]].text[ijkt[3]]->h)
		{
			ijkt[2] = -1;
			while (++ijkt[2] < env->sector[ijkt[0]].text[ijkt[3]]->w)
				sectorlightapply_support(env, ijkt, pix);
		}
	}
}

void	currentspritelight(t_env *env)
{
	int	i;
	int	j;

	i = -1;
	while (++i < env->sprcount)
	{
		j = -1;
		if (env->sprite[i].sector == (int)env->player.sector)
		{
			if (env->sprite[i].type == 0 || env->sprite[i].type == 3)
				spritelightapply(env, &env->sprite[i]);
			if (env->sprite[i].type == 1 || env->sprite[i].type == 4)
			{	
				if (env->sprite[i].type == 4)
					enemylightapply(env, &env->sprite[i], 0);
				else
					while (++j < 7)
						enemylightapply(env, &env->sprite[i], j);
			}
		}
	}
}

void	pushswitch(t_env *env)
{
	int	i;

	if (env->player.pushingbutton)
	{
		if (env->sector[env->player.sector].on == 0)
		{
			env->sector[env->player.sector].on = 1;
			env->sector[env->player.sector].light += 40;
			printf("on light:%d\n", env->sector[env->player.sector].light);
		}
		else if (env->sector[env->player.sector].on == 1)
		{
			env->sector[env->player.sector].on = 0;
			env->sector[env->player.sector].light -= 40;
			printf("off light:%d\n", env->sector[env->player.sector].light);
		}
		currentsectorlightapply(env, env->player.sector);
		currentspritelight(env);
		env->player.pushingbutton = 0;
		i = -1;
	}
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
			if (env->sector[ijkt[0]].sky == 1)
				env->sector[ijkt[0]].light = 100;
			if (env->sector[ijkt[0]].text[ijkt[3]] != NULL)
				SDL_FreeSurface(env->sector[ijkt[0]].text[ijkt[3]]);
			env->sector[ijkt[0]].text[ijkt[3]] = IMG_Load(gettex(env, ijkt[0], ijkt[3]));
			pix = (unsigned char *)env->sector[ijkt[0]].text[ijkt[3]]->pixels;
			ijkt[1] = -1;
			while (++ijkt[1] < env->sector[ijkt[0]].text[ijkt[3]]->h)
			{
				ijkt[2] = -1;
				while (++ijkt[2] < env->sector[ijkt[0]].text[ijkt[3]]->w)
					sectorlightapply_support(env, ijkt, pix);
			}
		}
	}
}
