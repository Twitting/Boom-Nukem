/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:52:06 by twitting          #+#    #+#             */
/*   Updated: 2019/03/05 17:25:18 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

//# include <math.h>
//# include <fcntl.h>
//# include "SDL2/SDL.h"
# include "../libft/libft.h"
# include <stdlib.h>

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
# define VXS(x0, y0, x1, y1) ((x0) * (y1) - (x1) * (y0))

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

t_env	*structure_init(void);

#endif
