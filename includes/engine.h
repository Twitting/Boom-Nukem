/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:52:06 by twitting          #+#    #+#             */
/*   Updated: 2019/04/15 14:05:00 by daharwoo         ###   ########.fr       */
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
	int				openbar;
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
	int				visible;
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
	SDL_Surface		*text[22];
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
	Mix_Chunk		*sound[15];
	int				blood;
	int				volume;
	TTF_Font		*fonts[3];
	int				help;
	int				mode;
}					t_env;

void				inittext_term(t_env *env);
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
int					i_b(t_xy a, t_xy b, t_xy c, t_xy d);
int					overlap(double a0, double a1, double b0, double b1);
double				vxs(double x0, double y0, double x1, double y1);
void				grandparser(t_env *env);
void				inittext(t_env *env);
void				verttosect(t_env *env, t_sector *sect, char *line, int i);
void				neighborstosect(t_sector *sect, char *line, int i);
void				move_mob(t_env *env);
void				spritedist(t_env *env);
void				findbutton(t_env *env);
void				barsanimate(t_env *env);
int					openbars(t_env *env);
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

# define ESPRI env->sprite[i]
# define ESHOOT env->shooting
# define ESIV env->sector[i].vertex
# define ESIN env->sector[i].npoints
# define EBUTT env->button[i]
# define SPRTE sprite->texture
# define ESEC env->sector
# define ESECT ESEC[ijkt[0]].text[ijkt[3]]
# define ESECT2 (unsigned char)((double)pix[(ijkt[1] * env->sector->w + ijkt[2]) * 4
# define ESECT3 (unsigned char)((double)pix[(j * sprite->texture[0]->w + k) * 4
# define EPS env->player.sector
# define SV sect.vertex
# define WTF1 i_b(arr[0], arr[1], ESEC[EPS].vertex[arr2[0] % ESEC[EPS].npoints], ESEC[EPS].vertex[(arr2[0] + 1) % ESEC[EPS].npoints]) && point_side(arr[1].x,arr[1].y, ESEC[EPS].vertex[arr2[0] % ESEC[EPS].npoints], ESEC[EPS].vertex[(arr2[0] + 1) % ESEC[EPS].npoints]
# define WTF2 sect.neighbors[arr2[0]] >= 0 && i_b(arr[0], arr[1], SV[arr2[0] % sect.npoints], SV[(arr2[0] + 1) % sect.npoints]) && point_side(arr[1].x, arr[1].y, SV[arr2[0] % sect.npoints], SV[(arr2[0] + 1) % sect.npoints]
# define WTF3 i_b(*p, b_pd[1], ESEC[EPS].vertex[s % ESEC[EPS].npoints], ESEC[EPS].vertex[(s + 1) % ESEC[EPS].npoints]) && point_side(b_pd[1].x, b_pd[1].y, ESEC[EPS].vertex[s % ESEC[EPS].npoints], ESEC[EPS].vertex[(s + 1) % ESEC[EPS].npoints]
# define WTF4 i_b(*p, b_pd[1], env->sprite[s].pos1, env->sprite[s].pos2) && point_side(b_pd[1].x, b_pd[1].y, env->sprite[s].pos1, env->sprite[s].pos2
# define WTF5 sect.neighbors[arr2[0]] >= 0 && i_b(opvoppp[1], opvoppp[0], SV[arr2[0] % sect.npoints], SV[(arr2[0] + 1) % sect.npoints]) && point_side(opvoppp[0].x, opvoppp[0].y, SV[arr2[0] % sect.npoints], SV[(arr2[0] + 1) % sect.npoints]
# define ESJT0 env->sprite[j].texture[0]
# define EPW env->player.where
# define EPSIN env->player.sinang
# define EPCOS  env->player.cosang
# define RO1 rend->org1
# define RO2 rend->org2
# define R rend
# define NST nowsect->text
# define PANG env->player.angle
# define ET env->text
# define PIXUD j * sprite->texture[0]->w + k) * 4
#endif
