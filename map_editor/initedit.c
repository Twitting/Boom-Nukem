/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initedit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:26:05 by twitting          #+#    #+#             */
/*   Updated: 2019/04/05 17:58:29 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

void	portalinit(t_edit *edit)
{
	int	i;

	i = -1;
	while (++i < 64)
		edit->portsects[i] = -1;
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

void	sectvertinit(t_edit *edit) //if segfault on macos see there
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (j < 256)
	{
		i = 0;
		while (i < 64)
		{
			edit->sectors[j].vertex[i] = -1;
			edit->verts[j * 64 + i].x = -1;
			edit->verts[j * 64 + i].y = -1;
			edit->sectors[j].neighbors[i] = -1;
			edit->sectors[j].light = 1;
			edit->sectors[j].npoints = 0;
			edit->sectors[j].finished = 0;
			edit->sectors[j].floor = 0;
			edit->sectors[j].ceiling = 20;
			i++;
		}
		j++;
	}
}

t_edit	*init(void)
{
	t_edit	*edit;

	edit = (t_edit *)malloc(sizeof(t_edit));
	edit->quit = 0;
	edit->put = 0;
	edit->playersetflag = 0;
	edit->glvertnum = 0;
	edit->nowln.color = 0xffffff;
	edit->sectnum = 0;
	edit->vertnum = 0;
	edit->sprnum = 0;
	sectvertinit(edit);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_putchar('!');
	else
	{
		if (!(edit->window = SDL_CreateWindow("Super Map Editor 2020",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				WWIN, HWIN, SDL_WINDOW_OPENGL + SDL_WINDOW_ALLOW_HIGHDPI)))
			ft_putchar('!');
		edit->surface = SDL_GetWindowSurface(edit->window);
	}
	makegrid(edit);
	return (edit);
}
