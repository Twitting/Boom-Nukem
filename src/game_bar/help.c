/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 06:34:02 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 07:32:40 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

static void free_for_help(SDL_Surface	*new, char *str, char *ia)
{
	free(ia);
	free(str);
	SDL_FreeSurface(new);
}

void help(t_env *env)
{
	SDL_Surface	*new;
	SDL_Color	color;
	SDL_Rect	position;
	char *str;
	char *ia;

	position.x = 840;
	position.y = 10;
	color.r = 210;
	color.g = 210;
	color.b = 210;
	ia = ft_itoa((int)((float)env->volume * PROC_VOLUME));
	str = ft_strjoin(ia, "% music");
	new = TTF_RenderText_Solid(env->fonts[2],
	str, color);
	SDL_BlitSurface(new, NULL, env->surface, &position);
	free_for_help(new, str, ia);
	position.y = 55;
	ia = ft_itoa((int)(env->oldfps));
	str = ft_strjoin(ia, " fps");
	new = TTF_RenderText_Solid(env->fonts[2],
	str, color);
	SDL_BlitSurface(new, NULL, env->surface, &position);
	free_for_help(new, str, ia);
}
