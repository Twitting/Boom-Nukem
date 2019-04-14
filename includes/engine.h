/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:52:06 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 13:46:35 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <math.h>
# include <fcntl.h>
# include <SDL2/SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# include "libft.h"
# include <stdlib.h>
# include <time.h>

# define WWIN 1024
# define HWIN 768
# define EYEHEIGHT 6.0
# define DUCKHEIGHT 2.5
# define HEADMARGIN 2.0
# define KNEEHEIGHT 2.0
# define HFOV 1.0 * 0.73 * HWIN / WWIN
# define VFOV 1.0 * 0.2
# define SKYSIZE 3840
# define TEXP env->sector[secnum].textpack
# define PROC_VOLUME 0.78125

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
	t_xy			pos1;
	t_xy			pos2;
	SDL_Surface		*texture[8];
	double			spritedist;
	int				height;
	int				floor;
	int				width;
	int				sector;
	int				type;
	int				visible;
	int				hp;
	int				movecount;
	int				texnum;
	double			mobtimer;
}					t_sprite;

typedef	struct		s_button
{
	double			x1;
	double			y1;
	double			x2;
	double			y2;
	SDL_Surface		*texture;
	int				height;
	int				width;
	int				sector;
}					t_button;

typedef struct		s_sector
{
	double			floor;
	double			ceiling;
	t_xy			*vertex;
	int				*neighbors;
	unsigned int	npoints;
	unsigned int	light;
	SDL_Surface		*text[3];
	int				sky;
	int				textpack;
	int				on;
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
	int				target;
	int				hp;
	int				pushingbutton;
	int				keys;
}					t_player;

typedef struct		s_wallsp
{
	int				vert1;
	int				vert2;
	int				sect1;
	int				sect2;
	int				minceil;
	int				maxfl;
}					t_wallsp;

typedef struct		s_env
{
	char			mapname[64];
	t_player		player;
	t_sector		*sector;
	unsigned int	nsectors;
	t_xy			*vertex;
	unsigned int	nvertexes;
	int				quit;
	SDL_Surface		*surface;
	SDL_Surface		*text[20];
	SDL_Window		*window;
	SDL_Surface		*temp;
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
	int				skyangle;
	int				sprcount;
	t_button		*button;
	unsigned int	butcount;
	int				jetpack;
	int				spacebar;
	t_wallsp		wallsp;
	double			bx;
	double			by;
	int				shooting;
	SDL_Window		*window2;
	SDL_Surface		*surface2;
	t_player		save[4];
	int				save_number;
	int				state;
	int				b_one;
	int				b_two;
	int				b_three;
	int				b_four;
	int				head;
	int				head_shot;
	int				keys_shot;
	int				key;
	SDL_Surface		*text_head[26];
	SDL_Surface		*text_keys[8];
	SDL_Surface		*game_over[48];
	Mix_Music		*music[2];
	Mix_Chunk		*sound[11];
	int				blood;
	int				volume;
	TTF_Font		*fonts[3];
	int				help;
}					t_env;

void				sortsprite(t_env *env);
void				keylightapply(t_env *env, t_sprite *sprite, int tex);
void				sectorlightapply_support(t_env *env, int *ijkt,
						unsigned char *pix);
char				*gettex(t_env *env, int secnum, int tex);
int					checkswitch(t_env *env);
void				initspritelight(t_env *env);
void				sectorlightapply(t_env *env);
void				pushswitch(t_env *env);
void				spritelightapply(t_env *env, t_sprite *sprite);
void				mob_attack(t_env *env);
void				enemylightapply(t_env *env, t_sprite *sprite, int tex);
void				shoot(t_env *env, SDL_Event *e);
void				cross(t_env *env);
void				texnulling(t_env *env);
void				fps(t_env *env);
void				movement_calcs(t_env *env);
void				movement(t_env *env, float dx, float dy);
void				handle_events(t_env *env, SDL_Event *e);
void				init(t_env *env);
void				ft_error(int errnum);
t_xy				intersect(t_xy a, t_xy b, t_xy c, t_xy d);
double				point_side(double px, double py, t_xy a, t_xy b);
int					intersect_box(t_xy a, t_xy b, t_xy c, t_xy d);
int					overlap(double a0, double a1, double b0, double b1);
double				vxs(double x0, double y0, double x1, double y1);
void				grandparser(t_env *env);
void				inittext(t_env *env);
void				verttosect(t_env *env, t_sector *sect, char *line, int i);
void				neighborstosect(t_sector *sect, char *line, int i);
void				move_mob(t_env *env);
void				spritedist(t_env *env);
void				findbutton(t_env *env);
/*
** menu/main.c
*/
void				menu(t_env *env, SDL_Event *e);

/*
** menu.c
*/
void				menu_pause(t_env *env, SDL_Event *e);
void				save_game(t_env *env, SDL_Event *e);
void				load_game(t_env *env, SDL_Event *e);
void				game_mode(t_env *env, SDL_Event *e);

/*
** handle_pause.c
*/
void				handle_events_pause(t_env *env, SDL_Event *e);

/*
** handle_menu.c
*/
void				handle_events_menu(t_env *env, SDL_Event *e);

/*
** handle_load.c
*/
void				handle_events_load(t_env *env, SDL_Event *e);

/*
** handle_save.c
*/
void				handle_events_save(t_env *env, SDL_Event *e);

/*
** handle_game_mode.c
*/
void				handle_events_game_mode(t_env *env, SDL_Event *e);
void				save_game1(t_env *env, int i);
void				load_player_init(t_env *env);

/*
** game_over.c
*/
void				game_over(t_env *env, SDL_Event *e);

/*
** game_bar/head.c
*/
void				head_one(t_env *env);
void				head_two(t_env *env);
void				head_three(t_env *env);
void				head_four(t_env *env);
void				head_five(t_env *env);
void				keys(t_env *env);

/*
** game_bar/help.c
*/
void				help(t_env *env);

/*
** game_bar/key.c
*/
void				keys(t_env *env);

/*
** game_bar/bar.c
*/
void				put_bar(t_env *env);

/*
** game_bar/hp.c
*/
void				good_frame_for_head(t_env *env);
void				put_hp(t_env *env);

#endif
