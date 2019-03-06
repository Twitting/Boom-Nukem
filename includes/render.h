/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:42:12 by ebednar           #+#    #+#             */
/*   Updated: 2019/03/06 17:49:45 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "engine.h"

typedef struct	s_now
{
	int			sectorno;
	int			sx1;
	int			sx2;
}				t_now;


typedef struct	s_rend
{
				double	vx1;
				double	vy1;
				double	vx2;
				double	vy2;
				t_xy	t1;
				t_xy	t2;
				double	xscale1;
				double	xscale2;
				double	yscale1;
				double	yscale2;
				int		x1;
				int		x2;
				double	yceil;
				double	yfloor;
				int		y1a;
				int		y1b;
				int		y2a;
				int		y2b;
				t_xy	nfz;
				t_xy	nfside;
				t_xy	i1;
				t_xy	i2;
				int		beginx;
				int		endx;
				int		x;
				int		ya;
				int		cya;
				int		yb;
				int		cyb;
}				t_rend;

#endif