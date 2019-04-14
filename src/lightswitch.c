/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightswitch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:15:36 by twitting          #+#    #+#             */
/*   Updated: 2019/04/13 15:03:14 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
			else if (env->sprite[i].type == 5)
			while (++j < 8)
				keylightapply(env, &env->sprite[i], j);
		}
	}
}

int		checkswitch(t_env *env)
{
	double	buttondist;

	buttondist = 
	(env->player.where.x - (env->button[env->player.sector].x1 +
	env->button[env->player.sector].x2) / 2) *
	(env->player.where.x - (env->button[env->player.sector].x1 +
	env->button[env->player.sector].x2) / 2) +
	(env->player.where.y - (env->button[env->player.sector].y1 +
	env->button[env->player.sector].y2) / 2) *
	(env->player.where.y - (env->button[env->player.sector].y1 +
	env->button[env->player.sector].y2) / 2);
	if (buttondist <= 10)
		return (1);
	return (0);
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
		}
		else if (env->sector[env->player.sector].on == 1)
		{
			env->sector[env->player.sector].on = 0;
			env->sector[env->player.sector].light -= 40;
		}
		currentsectorlightapply(env, env->player.sector);
		currentspritelight(env);
		env->player.pushingbutton = 0;
		i = -1;
	}
}