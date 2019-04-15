/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:38:37 by daharwoo          #+#    #+#             */
/*   Updated: 2019/04/15 15:41:53 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	keyboard_events3(t_env *env, SDL_Event *e)
{
	if (e->type == SDL_KEYUP && e->key.keysym.sym ==
		1073741901 && env->volume > 0)
	{
		env->volume -= 15;
		if (env->volume < 0)
			env->volume = 0;
		Mix_VolumeMusic(env->volume);
	}
	if (e->type == SDL_KEYUP && e->key.keysym.sym ==
		1073741898 && env->volume < 128)
	{
		env->volume += 15;
		if (env->volume > 128)
			env->volume = 128;
		Mix_VolumeMusic(env->volume);
	}
	if (e->type == SDL_KEYUP && e->key.keysym.sym == 127)
	{
		if (env->help)
			env->help = 0;
		else
			env->help = 1;
	}
}

void	mixtex_support(t_env *env, t_sprite *sprite, SDL_Surface *temp)
{
	if (sprite->type == 1 && sprite->visible == 1)
	{
		temp = SPRTE[0];
		SPRTE[0] = SPRTE[sprite->texnum % 7];
		SPRTE[sprite->texnum % 7] = temp;
	}
	else if (sprite->type == 4 && sprite->hp > 666)
	{
		if (sprite->hp == 716)
			SDL_FreeSurface(SPRTE[0]);
		if ((sprite->hp - 676) % 10 == 0)
			SPRTE[0] = ET[(sprite->hp - 676) / 10 + 3];
		sprite->hp--;
	}
	else if (sprite->type == 4 && sprite->hp == 666)
	{
		temp = SPRTE[0];
		SPRTE[0] = SPRTE[7];
		SPRTE[7] = temp;
		sprite->hp--;
		enemylightapply(env, sprite, 0);
	}
}

void	mixtex(t_env *env, t_sprite *sprite)
{
	SDL_Surface *temp;

	temp = NULL;
	if (sprite->type == 4 && sprite->hp <= 0)
		sprite->hp = 716;
	mixtex_support(env, sprite, temp);
	temp = NULL;
}

void	mixkeytex(t_sprite *sprite)
{
	SDL_Surface	*temp;

	temp = SPRTE[0];
	SPRTE[0] = SPRTE[sprite->texnum % 8];
	SPRTE[sprite->texnum % 8] = temp;
}

void	applytermtex(t_env *env, t_sprite *sprite)
{
	SPRTE[0] = ET[14 + sprite->texnum];
	if (sprite->texnum == 0 || sprite->texnum == 4)
		sprite->width = 3;
	else if (sprite->texnum == 6 || sprite->texnum == 2)
		sprite->width = 1;
	else
		sprite->width = 2;
}
