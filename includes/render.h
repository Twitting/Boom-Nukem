/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:42:12 by ebednar           #+#    #+#             */
/*   Updated: 2019/03/29 15:16:02 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# define SCALER_INIT(a, b, c, d, f)\
					{d + (b - 1 - a) * (f - d) / (c - a), \
					((f < d) ^ (c < a)) ? -1 : 1, abs(f - d), \
					abs(c - a), (int)((b - 1 - a) * abs(f - d)) % abs(c - a)}
# define TOMAPCCORD(mapy, screenx, screeny, x, z) \
					do {z = (mapy) * HWIN * VFOV / ((HWIN / 2 - (screeny)) - env->player.yaw * HWIN * VFOV); \
					x = (z) * (WWIN / 2 - (screenx)) / (WWIN * HFOV); \
					TOABSCOORD(x,z); } while (0)
# define TOABSCOORD(X, Z) \
					do {float rtx = (Z) * env->player.cosang + (X) * env->player.sinang; \
					float rtz = (Z) * env->player.sinang - (X) * env->player.cosang; \
					X = rtx + env->player.where.x; Z = rtz + env->player.where.y; \
					} while(0)

# include "engine.h"

typedef struct	s_now
{
	int			sectorno;
	int			sx1;
	int			sx2;
}				t_now;

enum
{
				maxqueue = 8
};

typedef struct s_scaler
{
	int			result;
	int			bop;
	int			fd;
	int			ca;
	int			cache;
}				t_scaler;


typedef struct	s_rend
{
			t_sector	*nowsect;
			double		vx1;
			double		vy1;
			double		vx2;
			double		vy2;
			t_xy		t1;
			t_xy		t2;
			double		xscale1;
			double		xscale2;
			double		yscale1;
			double		yscale2;
			int			x1;
			int			x2;
			double		yceil;
			double		yfloor;
			int			y1a;
			int			y1b;
			int			y2a;
			int			y2b;
			t_xy		nfz;
			t_xy		nfside;
			t_xy		i1;
			t_xy		i2;
			int			beginx;
			int			endx;
			int			x;
			int			y;
			int			ya;
			int			cya;
			int			yb;
			int			cyb;
			float		nyceil;
			float		nyfloor;
			int			ny1a;
			int			ny1b;
			int			ny2a;
			int			ny2b;
			int			nya;
			int			ncya;
			int			nyb;
			int			ncyb;
			t_now		*head;
			t_now		*tail;
			int			u0;
			int			u1;
			t_xy		org1;
			t_xy		org2;
			int			txtx;
			int			txtz;
			float		hei;
			float		mapx;
			float		mapz;
			int			pel;
}				t_rend;

int		scaler_next(t_scaler *sc);

#endif