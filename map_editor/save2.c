/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:02:43 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 15:38:04 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

void	putvertstofile(t_edit *edit, int fd)
{
	int	i;

	i = -1;
	while (++i < edit->glvertnum)
	{
		ft_putstr_fd("vertex\t", fd);
		ft_putnbr_fd(edit->verts[i].y, fd);
		ft_putchar_fd('\t', fd);
		ft_putnbr_fd(edit->verts[i].x, fd);
		ft_putchar_fd('\n', fd);
	}
	ft_putchar_fd('\n', fd);
}

void	sectinfotofile(t_edit *edit, int fd, int i)
{
	ft_putstr_fd("sector\t", fd);
	ft_putnbr_fd(edit->sectors[i].floor, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(edit->sectors[i].ceiling, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(edit->sectors[i].light, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(edit->sectors[i].texture, fd);
	ft_putchar_fd('\t', fd);
}

void	button_event(kiss_button *button, SDL_Event *e, int *draw,
		int *quit)
{
	if (kiss_button_event(button, e, draw))
		*quit = 1;
}

void	makebars(t_edit *edit, int sect1, int sect2)
{
	edit->bars[edit->barsnum].vert1 = PVERT1;
	edit->bars[edit->barsnum].vert2 = PVERT2;
	edit->bars[edit->barsnum].sect1 = sect1;
	edit->bars[edit->barsnum].sect2 = sect2;
	edit->barsnum++;
	putportalline(edit, 0x777777);
}
