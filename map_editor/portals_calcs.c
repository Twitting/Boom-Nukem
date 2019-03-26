/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals_calcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 21:41:55 by twitting          #+#    #+#             */
/*   Updated: 2019/03/22 21:42:31 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

int		checknearverts2(t_edit *edit, int first)
{
	int	i;
	int	j;

	i = 0;
	while (i < 64 && edit->portsects[i] != -1)
	{
		j = 0;
		while (i != first && j < (int)PSECT.npoints)
		{
			if (PSECT.vertex[j] == PVERT1 &&
				((PSECT.vertex[(j + 1) % PSECT.npoints] == PVERT2) ||
				(j > 0 && PSECT.vertex[j - 1] == PVERT2) ||
				(j == 0 && PSECT.vertex[PSECT.npoints - 1] == PVERT2)))
					return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int		makeneighbors(t_edit *edit, int sect1, int sect2)
{
	int	i;

	i = -1;
	if (PSECT1.floor > PSECT2.ceiling || PSECT2.floor > PSECT1.ceiling)
		return (0);
	while (++i < (int)PSECT1.npoints)
	{
		if ((PSECT1.vertex[i] == PVERT1 || PSECT1.vertex[i] == PVERT2) &&
			(PSECT1.vertex[(i + 1) % PSECT1.npoints] == PVERT1 ||
			PSECT1.vertex[(i + 1) % PSECT1.npoints] == PVERT2))
				PSECT1.neighbors[i] = sect2;
	}
	i = -1;
	while (++i < (int)PSECT2.npoints)
	{
		if ((PSECT2.vertex[i] == PVERT1 || PSECT2.vertex[i] == PVERT2) &&
			(PSECT2.vertex[(i + 1) % PSECT2.npoints] == PVERT1 ||
			PSECT2.vertex[(i + 1) % PSECT2.npoints] == PVERT2))
				PSECT2.neighbors[i] = sect1;
	}
	printf("PORTAL: Sect1:%d, Sect2:%d, vert1:%d, vert2:%d\n", sect1, sect2, PVERT1, PVERT2);
	return (1);
}

int		checknearverts(t_edit *edit)
{
	int	i;
	int	j;
	int	check2;

	i = -1;
	while (++i < 64 && edit->portsects[i] != -1)
	{
		j = -1;
		while (++j < (int)PSECT.npoints)
		{
			if (PSECT.vertex[j] == PVERT1 && ((PSECT.vertex[(j + 1) %
			PSECT.npoints] == PVERT2) || (j > 0 && PSECT.vertex[j - 1] ==
			PVERT2) || (j == 0 && PSECT.vertex[PSECT.npoints - 1] == PVERT2)))
				{
					if ((check2 = checknearverts2(edit, i)) != -1)
					{
						if (makeneighbors(edit, edit->portsects[i],
							edit->portsects[check2]))
							return (1);
					}
				}
		}
	}
	return (0);
}

void	portalcheck(t_edit *edit)
{
	int	i;
	int	j;
	int	counter;
	int	sectcounter;

	i = -1;
	sectcounter = 0;
	while (++i < edit->sectnum)
	{
		j = -1;
		counter = 0;
		while (++j < (int)edit->sectors[i].npoints)
			if (edit->sectors[i].vertex[j] == PVERT1 ||
				edit->sectors[i].vertex[j] == PVERT2)
				counter++;
		if (counter == 2)
			edit->portsects[sectcounter++] = i;
	}
	if (checknearverts(edit) == 0)
		ft_putstr("Incorrect vertexes\n");
}