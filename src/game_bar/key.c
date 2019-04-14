/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 06:36:58 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 06:39:23 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"



void keys(t_env *env)
{
	SDL_Rect	position;
	SDL_Rect	position2;
	position.x = 300;
	position.y = 665;
	position2.x = 300;
	position2.y = 650;
	env->keys_shot++;
	if (env->keys_shot > 100000)
		env->keys_shot = 0;
	unsigned long time_o = env->keys_shot % 10;
	if (time_o == 0)
	{
		env->key++;
		env->key %= 8;
	}
	if (env->key == 0)
		SDL_BlitSurface(env->text_keys[0], NULL, env->surface, &position);
	else if (env->key == 1)
		SDL_BlitSurface(env->text_keys[1], NULL, env->surface, &position);
	else if (env->key == 2)
		SDL_BlitSurface(env->text_keys[2], NULL, env->surface, &position);
	else if (env->key == 3)
		SDL_BlitSurface(env->text_keys[3], NULL, env->surface, &position);
	else if (env->key == 4)
		SDL_BlitSurface(env->text_keys[4], NULL, env->surface, &position);
	else if (env->key == 5)
		SDL_BlitSurface(env->text_keys[5], NULL, env->surface, &position);
	else if (env->key == 6)
		SDL_BlitSurface(env->text_keys[6], NULL, env->surface, &position);
	else
		SDL_BlitSurface(env->text_keys[7], NULL, env->surface, &position);

	SDL_Surface	*new;
	SDL_Color	color_title;

	char *str;
	str = ft_itoa(env->player.keys);

	position.x = 344;
	position.y = 711;
	color_title.r = 70;
	color_title.g = 70;
	color_title.b = 70;
	new = TTF_RenderText_Solid(env->fonts[0],
	str, color_title);
	SDL_BlitSurface(new, NULL, env->surface, &position);
	SDL_FreeSurface(new);

	position.x = 341;
	color_title.r = 216;
	color_title.g = 160;
	color_title.b = 55;
	new = TTF_RenderText_Solid(env->fonts[0],
	str, color_title);
	SDL_BlitSurface(new, NULL, env->surface, &position);
	SDL_UpdateWindowSurface(env->window);
	SDL_FreeSurface(new);
	free(str);
	//TTF_CloseFont(bold);
	//TTF_CloseFont(bold2);
}
