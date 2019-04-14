/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:16:17 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 16:02:16 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

void	rules(void)
{
	SDL_Window	*win;
	SDL_Surface	*sur;
	SDL_Color	color_bold;

	win = SDL_CreateWindow("RULES", 1795, 336, 435, 770, SDL_WINDOW_SHOWN);
	sur = SDL_GetWindowSurface(win);
	color_bold.r = 0;
	color_bold.g = 255;
	color_bold.b = 0;
	TTF_Init();
	SDL_FillRect(sur, NULL, 0x000000);
	draw_title(sur);
	draw_strings(sur);
	draw_string("7) Rate of this project can be only above 100.",
	color_bold, 490, sur);
	SDL_UpdateWindowSurface(win);
	TTF_Quit();
}

int		main(void)
{
	t_edit		*edit;
	SDL_Event	e;
	int			i;

	edit = init();
	rules();
	while (edit->quit == 0)
	{
		SDL_UpdateWindowSurface(edit->window);
		handle_events(edit, &e);
	}
	i = 0;
	savemap(edit);
	SDL_Quit();
	exit(1);
	return (0);
}
