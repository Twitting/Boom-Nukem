/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:52:06 by twitting          #+#    #+#             */
/*   Updated: 2019/04/03 20:11:24 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <math.h>
# include <fcntl.h>
# include <SDL2/SDL.h>
# include <SDL_image.h>
# include "libft.h"
# include <stdlib.h>
# include <time.h>

# include <stdio.h>/////////////////////////////////////////////

# define WWIN 1024
# define HWIN 768
# define EYEHEIGHT 6.0
# define DUCKHEIGHT 2.5
# define HEADMARGIN 1.0
# define KNEEHEIGHT 2.0
# define HFOV 1.0 * 0.73 * HWIN / WWIN
# define VFOV 1.0 * 0.2 


# define MIN(a, b) (((a < b)) ? (a) : (b))
# define MAX(a, b) (((a > b)) ? (a) : (b))
# define CLAMP(a, min, max) MIN(MAX(a, min), max)
# define YAW(y, z) (y + z * env->player.yaw)

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

typedef	struct		s_sprite
{
	double			x;
	double			y;
	int				texture;
	double			spritedist;
	int				height;
	int				width;
	int				sector;
	int				type;
}					t_sprite;

typedef struct		s_sector
{
	double			floor;
	double			ceiling;
	t_xy			*vertex;
	int				*neighbors;
	unsigned int	npoints;
	unsigned int	light;
	SDL_Surface		*text;
}					t_sector;

typedef struct		s_player
{
	t_xyz			where;
	t_xyz			velocity;
	t_xyz			dvelocity;
	double			angle;
	double			sinang;
	double			cosang;
	double			yaw;
	unsigned int	sector;
	double			eye;
}					t_player;

typedef struct		s_env
{
	t_player		player;
	t_sector		*sector;
	unsigned int	nsectors;
	t_xy			*vertex;
	unsigned int	nvertexes;
	int				quit;
	SDL_Surface		*surface;
	SDL_Surface		*text[5];
	SDL_Window		*window;
	int				wsad[4];
	int				moving;
	int				ground;
	int				falling;
	int				ducking;
	float			yaw;
	double			frame;
	double			timer;
	int				fps;
	int				oldfps;
	t_sprite		*sprite;
	int				sprcount;
	t_xy			plane;


	
	double			debugtempdouble;
	int				debugtempint;
	double			debugtempint1;
	double			debugtempint2;
	double			debugtempint3;
	int				debugtempint4;
	int				debugtempint5;
}					t_env;

void	movement_calcs(t_env *env);
void	movement(t_env *env, float dx, float dy);
void	handle_events(t_env *env, SDL_Event *e);
void	init(t_env *env);
void	ft_error(int errnum);
t_xy	intersect(t_xy a, t_xy b, t_xy c, t_xy d);
double	point_side(double px, double py, t_xy a, t_xy b);
int		intersect_box(t_xy a, t_xy b, t_xy c, t_xy d);
int		overlap(double a0, double a1, double b0, double b1);
double	vxs(double x0, double y0, double x1, double y1);
t_env	*structure_init(void);
int		start_engine(t_env *env, SDL_Event *e);
void	inittext(t_env *env);
void	verttosect(t_env *env, t_sector *sect, char *line, int i);
void	neighborstosect(t_sector *sect, char *line, int i);

#endif
