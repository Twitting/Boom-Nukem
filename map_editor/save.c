/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 21:38:17 by twitting          #+#    #+#             */
/*   Updated: 2019/03/22 22:46:49 by twitting         ###   ########.fr       */
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

void	putsectstofile(t_edit *edit, int fd)
{
	int	i;
	int j;

	i = -1;
	while (++i < edit->sectnum)
	{
		j = -1;
		ft_putstr_fd("sector\t", fd);
		ft_putnbr_fd(edit->sectors[i].floor, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(edit->sectors[i].ceiling, fd);
		ft_putchar_fd('\t', fd);
		while (++j < (int)edit->sectors[i].npoints)
		{
			ft_putnbr_fd(edit->sectors[i].vertex[j], fd);
			if (j + 1 < (int)edit->sectors[i].npoints)
				ft_putchar_fd(' ', fd);
		}
		ft_putstr_fd("\t\t", fd);
		j = -1;
		while (++j < (int)edit->sectors[i].npoints)
		{
			ft_putnbr_fd(edit->sectors[i].neighbors[j], fd);
			if (j + 1 < (int)edit->sectors[i].npoints)
				ft_putchar_fd(' ', fd);
		}
		ft_putchar_fd('\n', fd);
	}
	ft_putchar_fd('\n', fd);
}

void	putplayertofile(t_edit *edit, int fd)
{
	ft_putstr_fd("player\t", fd);
	ft_putnbr_fd(edit->player.x, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(edit->player.y, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(edit->playerangle, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(edit->playersect, fd);
}

void	savemap(t_edit *edit)
{
	int	fd;

	if ((fd = open("test1.map", O_WRONLY | O_CREAT | O_TRUNC,
		S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
		perror("open failed\n");
	putvertstofile(edit, fd);
	putsectstofile(edit, fd);
	putplayertofile(edit, fd);
}