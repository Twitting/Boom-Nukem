/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:52:06 by twitting          #+#    #+#             */
/*   Updated: 2019/03/04 20:40:07 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <SDL.h>

# define WWIN 1024
# define HWIN 768
# define EYEHEIGHT 6.0
# define DUCKHEIGHT 2.5
# define HEADMARGIN 1.0
# define KNEEHEIGHT 2.0
# define HFOV 0.73 * HWIN
# define VFOV 0.2 * HWIN

typedef struct		s_xy
{
	float			x;
	float			y;
}					t_xy;

typedef struct		s_xyz
{
	float			x;
	float			y;
	float			z;
}					t_xyz;

typedef struct		s_sector
{
    float			floor;
	float			ceiling;
	t_xy			*vertex;
	int				*neighbors;
	unsigned int	npoints;
}					t_sector;

typedef struct		s_player
{
	t_xyz			where;
	t_xyz			velocity;
	float			angle;
	float			anglesin;
	float			yaw;
	unsigned int	sector;
}					t_player;




#endif