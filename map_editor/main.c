/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:16:17 by twitting          #+#    #+#             */
/*   Updated: 2019/03/19 20:40:52 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

void	handle_events(t_edit *edit, SDL_Event *e)
{
	int x;
	int y;

	SDL_GetMouseState(&x,&y);
	x = (x + 12)/ 25 * 25;
	y = (y + 12)/ 25 * 25;
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			edit->quit = 1;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
			edit->quit = 1;
		if (e->type == SDL_TEXTINPUT)
			ft_putnbr(atoi(e->text.text));
		if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT && edit->click == 0)
		{
			edit->click = 1;
			edit->nowln.x0 = x;
			edit->nowln.y0 = y;
		}
		if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT && edit->click == 1)
		{
			edit->click = 0;
			edit->nowln.x1 = x;
			edit->nowln.y1 = y;
			if (edit->nowln.x0 != edit->nowln.x1 || edit->nowln.y0 != edit->nowln.y1)
			putline(edit, &edit->nowln);
		}
		//if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
		//	SDL_StartTextInput;
		//if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
		//	SDL_StopTextInput;
	}
	
	//x = (x + 12) / 25 * 10;
	//y = (y + 12) / 25 * 10;
	//ft_putnbr(x);
	//ft_putchar(' ');
	//ft_putnbr(y);
	//ft_putchar('\n');
	//ft_putstr(e->text.text);
}

void	makegrid(t_edit *edit)
{
	int		*pix;
	int		i;
	int		j;

	pix = edit->surface->pixels;
	i = 0;
	while (i < HWIN)
	{
		j = 0;
		while (j < WWIN)
		{
			pix[i * WWIN + j] = 0x888888;
			j += 25;
		}
		i += 25;
	}
}

t_edit	*init()
{
	t_edit	*edit;

	edit = (t_edit *)malloc(sizeof(t_edit));
	edit->quit = 0;
	edit->click = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_putchar('!');//ft_error(4);
	else
	{
		if (!(edit->window = SDL_CreateWindow("Doom Nukem 2,5D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WWIN, HWIN, SDL_WINDOW_OPENGL + SDL_WINDOW_ALLOW_HIGHDPI)))
			ft_putchar('!');//ft_error(4);
		edit->surface = SDL_GetWindowSurface(edit->window);
	}
	makegrid(edit);
	return (edit);
}

int		main(void)
{
	t_edit		*edit;
	SDL_Event	e;

	edit = init();
	while (edit->quit == 0)
	{
		SDL_LockSurface(edit->surface);
		//render_wall(env);
		SDL_UnlockSurface(edit->surface);
		SDL_UpdateWindowSurface(edit->window);
		handle_events(edit, &e);
	}
	printf("!!!\n");
	return (0);
}