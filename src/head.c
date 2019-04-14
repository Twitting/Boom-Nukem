/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:25:35 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 06:38:20 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

void head_one(t_env *env)
{
	SDL_Rect	position;
	SDL_Rect	position2;
	position.x = 20;
	position.y = 650;
	position2.x = 120;
	position2.y = 725;
	env->head_shot++;
	if (env->head_shot > 100000)
		env->head_shot = 0;
	int time_o = env->head_shot % 25;
	if (time_o == 0)
	{
		env->head++;
		env->head %= 4;
	}
	if (env->head == 0)
		SDL_BlitSurface(env->text_head[0], NULL, env->surface, &position);
	else if (env->head == 1)
		SDL_BlitSurface(env->text_head[1], NULL, env->surface, &position);
	else if (env->head == 2)
		SDL_BlitSurface(env->text_head[2], NULL, env->surface, &position);
	else
		SDL_BlitSurface(env->text_head[1], NULL, env->surface, &position);
	if (env->player.hp == 100)
		SDL_BlitSurface(env->text_head[15], NULL, env->surface, &position2);
	else
		SDL_BlitSurface(env->text_head[16], NULL, env->surface, &position2);
	
}

void head_two(t_env *env)
{
	SDL_Rect	position;
	SDL_Rect	position2;
	position.x = 20;
	position.y = 650;
	position2.x = 120;
	position2.y = 725;
	env->head_shot++;
	if (env->head_shot > 100000)
		env->head_shot = 0;
	unsigned long time_o = env->head_shot % 25;
	if (time_o == 0)
	{
		env->head++;
		env->head %= 4;
	}
	if (env->head == 0)
		SDL_BlitSurface(env->text_head[3], NULL, env->surface, &position);
	else if (env->head == 1)
		SDL_BlitSurface(env->text_head[4], NULL, env->surface, &position);
	else if (env->head == 2)
		SDL_BlitSurface(env->text_head[5], NULL, env->surface, &position);
	else
		SDL_BlitSurface(env->text_head[4], NULL, env->surface, &position);
	if (env->player.hp == 80)
		SDL_BlitSurface(env->text_head[17], NULL, env->surface, &position2);
	else
		SDL_BlitSurface(env->text_head[18], NULL, env->surface, &position2);
}

void head_three(t_env *env)
{
	SDL_Rect	position;
	SDL_Rect	position2;
	position.x = 20;
	position.y = 650;
	position2.x = 120;
	position2.y = 725;
	env->head_shot++;
	if (env->head_shot > 100000)
		env->head_shot = 0;
	unsigned long time_o = env->head_shot % 25;
	if (time_o == 0)
	{
		env->head++;
		env->head %= 4;
	}
	if (env->head == 0)
		SDL_BlitSurface(env->text_head[6], NULL, env->surface, &position);
	else if (env->head == 1)
		SDL_BlitSurface(env->text_head[7], NULL, env->surface, &position);
	else if (env->head == 2)
		SDL_BlitSurface(env->text_head[8], NULL, env->surface, &position);
	else
		SDL_BlitSurface(env->text_head[7], NULL, env->surface, &position);
	if (env->player.hp == 60)
		SDL_BlitSurface(env->text_head[19], NULL, env->surface, &position2);
	else
		SDL_BlitSurface(env->text_head[20], NULL, env->surface, &position2);
}

void head_four(t_env *env)
{
	SDL_Rect	position;
	SDL_Rect	position2;
	position.x = 20;
	position.y = 650;
	position2.x = 120;
	position2.y = 725;
	env->head_shot++;
	if (env->head_shot > 100000)
		env->head_shot = 0;
	unsigned long time_o = env->head_shot % 25;
	if (time_o == 0)
	{
		env->head++;
		env->head %= 4;
	}
	if (env->head == 0)
		SDL_BlitSurface(env->text_head[9], NULL, env->surface, &position);
	else if (env->head == 1)
		SDL_BlitSurface(env->text_head[10], NULL, env->surface, &position);
	else if (env->head == 2)
		SDL_BlitSurface(env->text_head[11], NULL, env->surface, &position);
	else
		SDL_BlitSurface(env->text_head[10], NULL, env->surface, &position);
	if (env->player.hp == 40)
		SDL_BlitSurface(env->text_head[21], NULL, env->surface, &position2);
	else
		SDL_BlitSurface(env->text_head[22], NULL, env->surface, &position2);
}

void head_five(t_env *env)
{
	SDL_Rect	position;
	SDL_Rect	position2;
	position.x = 20;
	position.y = 650;
	position2.x = 120;
	position2.y = 725;
	env->head_shot++;
	if (env->head_shot > 100000)
		env->head_shot = 0;
	unsigned long time_o = env->head_shot % 25;
	if (time_o == 0)
	{
		env->head++;
		env->head %= 4;
	}
	if (env->head == 0)
		SDL_BlitSurface(env->text_head[12], NULL, env->surface, &position);
	else if (env->head == 1)
		SDL_BlitSurface(env->text_head[13], NULL, env->surface, &position);
	else if (env->head == 2)
		SDL_BlitSurface(env->text_head[14], NULL, env->surface, &position);
	else
		SDL_BlitSurface(env->text_head[13], NULL, env->surface, &position);
	if (env->player.hp == 20)
		SDL_BlitSurface(env->text_head[23], NULL, env->surface, &position2);
	else
		SDL_BlitSurface(env->text_head[24], NULL, env->surface, &position2);
}

