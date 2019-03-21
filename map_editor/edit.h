/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:16:36 by twitting          #+#    #+#             */
/*   Updated: 2019/03/21 12:51:23 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDIT_H
# define EDIT_H

# include <math.h>
# include <fcntl.h>
# include <SDL2/SDL.h>
# include "libft.h"
# include <stdlib.h>

# include <stdio.h>/////////////////////////////////////////////

# define CMP edit->cmp_port
# define SECT edit->sectors[edit->sectnum]
# define WWIN 1024
# define HWIN 768

typedef struct		s_xy
{
	int				x;
	int				y;
}					t_xy;

typedef struct		s_sector
{
	int				floor;
	int				ceiling;
	int				vertex[64];
	int				neighbors[64];
	unsigned int	npoints;
	unsigned int	light;
	int				finished;
}					t_sector;

typedef struct		s_line
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				color;
}					t_line;

typedef struct		s_edit
{
	SDL_Surface		*surface;
	SDL_Window		*window;
	t_xy			verts[16384];
	int				quit;
	t_line			nowln;
	t_sector		sectors[256];
	int				sectnum;
	int				vertnum;
	int				glvertnum;
	int				put;
	int				cmp_port[16]; //x0,y0,x1,y1,s1,v1,s2,v2 and the same for second point
	int				check1;
}					t_edit;

t_edit	*init();
int		putline(t_edit *edit, t_line *l);

#endif