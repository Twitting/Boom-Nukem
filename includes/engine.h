/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:52:06 by twitting          #+#    #+#             */
/*   Updated: 2019/03/06 15:28:20 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <math.h>
# include <fcntl.h>
//# include "SDL2/SDL.h"
# include "../libft/libft.h"
# include <stdlib.h>

# include <stdio.h>/////////////////////////////////////////////

# define WWIN 1024
# define HWIN 768
# define EYEHEIGHT 6.0
# define DUCKHEIGHT 2.5
# define HEADMARGIN 1.0
# define KNEEHEIGHT 2.0
# define HFOV 0.73 * HWIN
# define VFOV 0.2 * HWIN

# define MIN(a, b) (((a < b)) ? (a) : (b))
# define MAX(a, b) (((a > b)) ? (a) : (b))
# define CLAMP(a, min, max) MIN(MAX(a, min), max)

typedef struct		s_xy
{
	double			x;
	double			y;
}					t_xy;

typedef struct		s_xyz
{
	double			x;
	double			y;
	double			z;
}					t_xyz;

typedef struct		s_sector
{
	double			floor;
	double			ceiling;
	t_xy			*vertex;
	int				*neighbors;
	unsigned int	npoints;
	unsigned int	light;
}					t_sector;

typedef struct		s_player
{
	t_xyz			where;
	t_xyz			velocity;
	double			angle;
	double			anglesin;
	double			yaw;
	unsigned int	sector;
}					t_player;

typedef struct		s_env
{
	t_player		player;
	t_sector		*sector;	
	unsigned int	nsectors;
	t_xy			*vertex;
	unsigned int	nvertexes;
}					t_env;

t_xy	intersect(t_xy a, t_xy b, t_xy c, t_xy d);
double	point_side(double px, double py, t_xy a, t_xy b);
int		intersect_box(t_xy a, t_xy b, t_xy c, t_xy d);
int		overlap(double a0, double a1, double b0, double b1);
double	vxs(double x0, double y0, double x1, double y1);
t_env	*structure_init(void);

#endif
