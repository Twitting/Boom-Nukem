/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:37:47 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/11 16:40:36 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

/*static void	vline(t_env *env, int x, int y1, int y2, int top, int middle, int bottom)
{
	int *pix;
	int y;

	pix = (int *)env->surface->pixels;
	y1 = CLAMP(y1, 0, HWIN - 1);
	y2 = CLAMP(y2, 0, HWIN - 1);
	if (y2 == y1)
		pix[y1 * WWIN + x] = middle;
	else if (y2 > y1)
	{
		pix[y1 * WWIN + x] = top;
		y = y1 + 1;
        while (y < y2)
		{
			pix[y * WWIN + x] = middle;
			y++;
		}
        pix[y2 * WWIN + x] = bottom;
	}
}*/

static void	vline2(t_env *env, t_rend *rend, int y1, int y2, t_scaler ty) //текстурирование стен
{
	int *pix;
	int y;
	int txty;
	//unsigned char *print;

	pix = (int*)env->surface->pixels;
	y1 = CLAMP(y1, 0, HWIN - 1) - 1;
	y2 = CLAMP(y2, 0, HWIN - 1) + 1;
	pix += y1 * WWIN + rend->x;
	y = y1;
	while (++y <= y2)
	{
		txty = scaler_next(&ty) * (rend->nowsect->ceiling - rend->nowsect->floor) / 64;
		*pix = ((int *)(rend->nowsect->text[1]->pixels))[txty % rend->nowsect->text[1]->h * rend->nowsect->text[1]->w + rend->txtx % rend->nowsect->text[1]->w];
		//*pix = ((int *)(env->text[0]->pixels))[txty % env->text[0]->h * env->text[0]->w + rend->txtx % env->text[0]->w];
		// print = (unsigned char *)pix;
		// print[0] = (int)((double)print[0] / 100 * rend->nowsect->light);
		// print[1] = (int)((double)print[1] / 100 * rend->nowsect->light);
		// print[2] = (int)((double)print[2] / 100 * rend->nowsect->light);
		pix += WWIN;
	}
}

static void	wallintersect(t_rend *rend, t_env *env)
{
	if (rend->t1.y <= 0 || rend->t2.y <= 0)
		{
			rend->nfz.x = 1e-4;
			rend->nfz.y = 5;
			rend->nfside.x = 1e-5;
			rend->nfside.y = 20;
			rend->wintsect1.x = -rend->nfside.x;
			rend->wintsect1.y = rend->nfz.x;
			rend->wintsect2.x = -rend->nfside.y;
			rend->wintsect2.y = rend->nfz.y;
			rend->i1 = intersect(rend->t1, rend->t2, rend->wintsect1, rend->wintsect2);
			rend->wintsect1.x = rend->nfside.x;
			rend->wintsect2.x = rend->nfside.y;
			rend->i2 = intersect(rend->t1, rend->t2, rend->wintsect1, rend->wintsect2);
			rend->org1 = (t_xy){rend->t1.x, rend->t1.y};
			rend->org2 = (t_xy){rend->t2.x, rend->t2.y};
			if (rend->t1.y < rend->nfz.x)
			{
				if (rend->i1.y > 0)
				{
					rend->t1.x = rend->i1.x;
					rend->t1.y = rend->i1.y;
				}
				else 
				{
					rend->t1.x = rend->i2.x;
					rend->t1.y = rend->i2.y;
				}
			}
			if (rend->t2.y < rend->nfz.x)
			{
				if (rend->i1.y > 0)
				{
					rend->t2.x = rend->i1.x;
					rend->t2.y = rend->i1.y;
				}
				else
				{
					rend->t2.x = rend->i2.x;
					rend->t2.y = rend->i2.y;
				}
			}
			if (fabs(rend->t2.x - rend->t1.x) > fabs(rend->t2.y - rend->t1.y))
			{
				rend->u0 = (rend->t1.x - rend->org1.x) * (env->text[0]->w - 1) / (rend->org2.x - rend->org1.x);
				rend->u1 = (rend->t2.x - rend->org1.x) * (env->text[0]->w - 1) / (rend->org2.x - rend->org1.x);
			}
			else
			{
				rend->u0 = (rend->t1.y - rend->org1.y) * (env->text[0]->w - 1) / (rend->org2.y - rend->org1.y);
				rend->u1 = (rend->t2.y - rend->org1.y) * (env->text[0]->w - 1) / (rend->org2.y - rend->org1.y);
			}
		}
}

static void	render_wall(t_env *env, t_rend *rend)
{
	int			s;
	t_now		now;
	int			ytop[WWIN] = {0};
	int			ybottom[WWIN];
	int			renderedsect[env->nsectors];
	//unsigned char *print;

	rend->head = rend->queue;
	rend->tail = rend->queue;
	rend->nyceil = 0;
	rend->nyfloor = 0;
	s = -1;
	
	while (++s < WWIN)
		ybottom[s] = HWIN - 1;
	*(rend->head) = (t_now){env->player.sector, 0, WWIN - 1};
	s = -1;
	while (++s < (int)env->nsectors)
		renderedsect[s] = 0;
	if (++rend->head == rend->queue + MAXQUEUE)
		rend->head = rend->queue;
	while (rend->head != rend->tail)
	{
		now = *(rend->tail);
		rend->sprq[now.sectorno].sector = now.sectorno;
		if (rend->sprq[now.sectorno].visible == 1)
		{
			if (rend->sprq[now.sectorno].sx1 > now.sx1)
				rend->sprq[now.sectorno].sx1 = now.sx1;
			if (rend->sprq[now.sectorno].sx2 < now.sx2)
				rend->sprq[now.sectorno].sx2 = now.sx2;
		}
		else
		{
			rend->sprq[now.sectorno].sx1 = now.sx1;
			rend->sprq[now.sectorno].sx2 = now.sx2;
		}
		rend->sprq[now.sectorno].visible = 1;
		s = -1;
		while (++s < WWIN)
			rend->sprq[now.sectorno].ytop[s] = ytop[s];
		s = -1;
		while (++s < WWIN)
			rend->sprq[now.sectorno].ybottom[s] = ybottom[s];
		if (++rend->tail == rend->queue + MAXQUEUE)
			rend->tail = rend->queue;
		if (renderedsect[now.sectorno] & 0x21)
			continue ;
		++renderedsect[now.sectorno];
		s = -1;
		rend->nowsect = &(env->sector[now.sectorno]);
		while (++s < (int)rend->nowsect->npoints)
		{
			rend->vx1 = rend->nowsect->vertex[s % rend->nowsect->npoints].x - env->player.where.x;
			rend->vy1 = rend->nowsect->vertex[s % rend->nowsect->npoints].y - env->player.where.y;
			rend->vx2 = rend->nowsect->vertex[(s + 1) % rend->nowsect->npoints].x - env->player.where.x;
			rend->vy2 = rend->nowsect->vertex[(s + 1) % rend->nowsect->npoints].y - env->player.where.y;
			rend->t1.x = rend->vx1 * env->player.sinang - rend->vy1 * env->player.cosang;
			rend->t1.y = rend->vx1 * env->player.cosang + rend->vy1 * env->player.sinang;
			rend->t2.x = rend->vx2 * env->player.sinang - rend->vy2 * env->player.cosang;
			rend->t2.y = rend->vx2 * env->player.cosang + rend->vy2 * env->player.sinang;
			if (rend->t1.y <= 0 && rend->t2.y <= 0)
				continue ;
			rend->u0 = 0;
			rend->u1 = (env->text[0]->w - 1);
			wallintersect(rend, env);
			if (rend->t1.y <= 0.5)
			{
			rend->t1.x = (0.5 - rend->t1.y) * (rend->t2.x - rend->t1.x) / (rend->t2.y - rend->t1.y) + rend->t1.x;
				rend->t1.y = 0.5;
			}
			rend->xscale1 = WWIN * HFOV / rend->t1.y; //WWIN!!!
			rend->yscale1 = HWIN * VFOV / rend->t1.y;
			rend->x1 = WWIN / 2 + (int)(- rend->t1.x * rend->xscale1);
			rend->xscale2 = WWIN * HFOV / rend->t2.y;
			rend->yscale2 = HWIN * VFOV / rend->t2.y;
			rend->x2 = WWIN / 2 + (int)(- rend->t2.x * rend->xscale2);
			// if (now.sectorno == (int)env->player.sector && s == 2)
			// 	printf("abs %f %f %f\n", rend->t1.y, rend->t1.x, rend->t2.x);
			if (rend->x1 >= rend->x2 || rend->x2 < now.sx1 || rend->x1 > now.sx2)
				continue;
			rend->yceil = rend->nowsect->ceiling - env->player.where.z;
			rend->yfloor = rend->nowsect->floor - env->player.where.z;
			if (rend->nowsect->neighbors[s] >= 0)
			{
				rend->nyceil = env->sector[rend->nowsect->neighbors[s]].ceiling - env->player.where.z;
				rend->nyfloor = env->sector[rend->nowsect->neighbors[s]].floor - env->player.where.z;
			}
			rend->y1a = HWIN / 2 - (int)(YAW(rend->yceil, rend->t1.y) * rend->yscale1);
			rend->y1b = HWIN / 2 - (int)(YAW(rend->yfloor, rend->t1.y) * rend->yscale1);
			rend->y2a = HWIN / 2 - (int)(YAW(rend->yceil, rend->t2.y) * rend->yscale2);
			rend->y2b = HWIN / 2 - (int)(YAW(rend->yfloor, rend->t2.y) * rend->yscale2);
			rend->ny1a = HWIN / 2 - (int)(YAW(rend->nyceil, rend->t1.y) * rend->yscale1);
			rend->ny1b = HWIN / 2 - (int)(YAW(rend->nyfloor, rend->t1.y) * rend->yscale1);
			rend->ny2a = HWIN / 2 - (int)(YAW(rend->nyceil, rend->t2.y) * rend->yscale2);
			rend->ny2b = HWIN / 2 - (int)(YAW(rend->nyfloor, rend->t2.y) * rend->yscale2);
			rend->beginx = MAX(rend->x1, now.sx1);
			rend->endx = MIN(rend->x2, now.sx2);
			rend->x = rend->beginx;
			rend->ya_int = (t_scaler)SCALER_INIT(rend->x1, rend->beginx, rend->x2, rend->y1a, rend->y2a);
			rend->yb_int = (t_scaler)SCALER_INIT(rend->x1, rend->beginx, rend->x2, rend->y1b, rend->y2b);
			while (rend->x <= rend->endx)
			{
				//rend->ya = (rend->x - rend->x1) * (rend->y2a - rend->y1a) / (rend->x2 - rend->x1) + rend->y1a;
				rend->ya = scaler_next(&rend->ya_int); //- не работает нормально?
				rend->cya = CLAMP(rend->ya, ytop[rend->x], ybottom[rend->x]);
				//rend->yb = (rend->x - rend->x1) * (rend->y2b - rend->y1b) / (rend->x2 - rend->x1) + rend->y1b;
				rend->yb = scaler_next(&rend->yb_int); //- не работает нормально??
				rend->cyb = CLAMP(rend->yb, ytop[rend->x], ybottom[rend->x]);
				rend->y  = ytop[rend->x] - 2;
				while (++rend->y <= ybottom[rend->x])
				{
					if (rend->y >= rend->cya && rend->y <= rend->cyb)
					{
						rend->y = rend->cyb;
						continue;
					}
					if (rend->y >= rend->cyb)
					{
					rend->hei = rend->y < rend->cya ? rend->yceil : rend->yfloor;
					TOMAPCCORD(rend->hei, rend->x, rend->y, rend->mapx, rend->mapz);
					rend->txtx = rend->mapx * rend->nowsect->text[0]->w / 12; // почему 256??
					rend->txtz = rend->mapz * rend->nowsect->text[0]->w / 12;
					//textset здесь применить нужную текстуру пола или потолка
					rend->pel = ((int*)rend->nowsect->text[0]->pixels)[abs(rend->txtz) % rend->nowsect->text[0]->h * rend->nowsect->text[0]->w + abs(rend->txtx) % rend->nowsect->text[0]->w]; //здесь скорее всего что то не так
					// rend->pel = ((int*)env->text[0]->pixels)[abs(rend->txtz) % env->text[0]->h * env->text[0]->w + abs(rend->txtx) % env->text[0]->w]; //здесь скорее всего что то не так
					// print = (unsigned char *)&rend->pel;
					// print[0] = (int)((double)print[0] / 100 * rend->nowsect->light);
					// print[1] = (int)((double)print[1] / 100 * rend->nowsect->light);
					// print[2] = (int)((double)print[2] / 100 * rend->nowsect->light);
					}
					if (rend->y < rend->cya)
					{
						if (rend->nowsect->sky != 1) 
						{
							rend->hei = rend->y < rend->cya ? rend->yceil : rend->yfloor;
							TOMAPCCORD(rend->hei, rend->x, rend->y, rend->mapx, rend->mapz);
							rend->txtx = rend->mapx * rend->nowsect->text[2]->w / 12; // почему 256??
							rend->txtz = rend->mapz * rend->nowsect->text[2]->w / 12;
							rend->pel = ((int*)rend->nowsect->text[2]->pixels)[abs(rend->txtz) % rend->nowsect->text[2]->h * rend->nowsect->text[2]->w + abs(rend->txtx) % rend->nowsect->text[2]->w]; //здесь скорее всего что то не так
						}
						else
							rend->pel = ((int *)(env->text[2]->pixels))[(int)(rend->y + 100 * (env->player.yaw + 3)) % env->text[2]->h * env->text[2]->w + + (int)(env->player.angle / 6.2 * env->text[2]->w + rend->x) % env->text[2]->w];
					}
					((int*)env->surface->pixels)[rend->y * WWIN + rend->x] = rend->pel;
				}
				//drawsky(env, rend, now.sectorno);
				rend->txtx = ((rend->u0 * ((rend->x2 - rend->x) * rend->t2.y) + rend->u1 * ((rend->x - rend->x1) * rend->t1.y))\
				/ ((rend->x2 - rend->x) * rend->t2.y + (rend->x - rend->x1) * rend->t1.y)) * (fabs(rend->vx2 - rend->vx1) + fabs(rend->vy2 - rend->vy1)) * 0.04;
				//vline(env, rend->x, now.ytop[rend->x], rend->cya - 1, 0x111111, 0x222222, 0x111111); //старые заглушки пола и потолка
				//vline(env, rend->x, rend->cyb - 1, now.ybottom[rend->x], 0x0000FF, 0x0000AA, 0x0000FF);
				if (rend->nowsect->neighbors[s] >= 0)
				{
					rend->nya = (rend->x - rend->x1) * (rend->ny2a - rend->ny1a) / (rend->x2 - rend->x1) + rend->ny1a;
					rend->ncya = CLAMP(rend->nya, ytop[rend->x], ybottom[rend->x]);
					rend->nyb = (rend->x - rend->x1) * (rend->ny2b - rend->ny1b) / (rend->x2 - rend->x1) + rend->ny1b;
					rend->ncyb = CLAMP(rend->nyb, ytop[rend->x], ybottom[rend->x]);
					vline2(env, rend, rend->cya, rend->ncya - 1, (t_scaler)SCALER_INIT(rend->ya, rend->cya, rend->yb, 0, (env->text[0]->w - 1)));
				//	vline(env, rend->x, rend->cya, rend->ncya - 1, 0, rend->x == rend->x1 || rend->x == rend->x2 ? 0 : 0xAAAAAA, 0);
					if (rend->nowsect->sky != 1)
						if (env->sector[rend->nowsect->neighbors[s]].sky == 1)
							ytop[rend->x] = CLAMP(rend->cya + 1, ytop[rend->x], HWIN - 1);
						else
							ytop[rend->x] = CLAMP(MAX(rend->cya, rend->ncya), ytop[rend->x], HWIN - 1);
					else
						if (env->sector[rend->nowsect->neighbors[s]].sky == 1)
							ytop[rend->x] = CLAMP(MIN(rend->cya, rend->ncya), ytop[rend->x], HWIN - 1);
						else
							ytop[rend->x] = CLAMP(rend->ncya, ytop[rend->x], HWIN - 1);
					vline2(env, rend, rend->ncyb + 1, rend->cyb, (t_scaler)SCALER_INIT(rend->ya, rend->ncyb + 1, rend->yb, 0, (env->text[0]->w - 1)));
				//	vline(env, rend->x, rend->ncyb + 1, rend->cyb, 0, rend->x == rend->x1 || rend->x == rend->x2 ? 0 : 0x7C00D9 , 0);
					ybottom[rend->x] = CLAMP(MIN(rend->cyb, rend->ncyb), 0, ybottom[rend->x]);
				}
				else
					vline2(env, rend, rend->cya, rend->cyb, (t_scaler)SCALER_INIT(rend->ya, rend->cya, rend->yb, 0, (env->text[0]->w - 1)));
				//	vline(env, rend->x, rend->cya, rend->cyb, 0, rend->x == rend->x1 || rend->x == rend->x2 ? 0 : 0xAAAAAA, 0);
				rend->x++;
			}
			if (rend->nowsect->neighbors[s] >= 0 && rend->endx >= rend->beginx && (rend->head + MAXQUEUE + 1 - rend->tail) % MAXQUEUE)
			{
				*(rend->head) = (t_now){rend->nowsect->neighbors[s], rend->beginx, rend->endx};
				if (++rend->head == rend->queue + MAXQUEUE)
					rend->head = rend->queue;
			}
		}
		++renderedsect[now.sectorno];
	}
}

void	mixtex(t_env *env, t_sprite *sprite)
{
	SDL_Surface *temp;

	env->jetpack = 0;
	if (sprite->type == 4 && sprite->hp <= 0)
		sprite->hp = 716;
	if (sprite->type == 1 && sprite->visible == 1)
	{
		temp = sprite->texture[0];
		sprite->texture[0] = sprite->texture[sprite->texnum % 7];
		sprite->texture[sprite->texnum % 7] = temp;
	}
	else if (sprite->type == 4 && sprite->hp > 666)
	{
		//SDL_FreeSurface(sprite->texture[0]);
		if ((sprite->hp - 676) % 10 == 0)
		{
			sprite->texture[0] = env->text[(sprite->hp - 676) / 10 + 3];
			sprite->height--;
		}
		sprite->hp--;
	}
	else if (sprite->type == 4 && sprite->hp == 666)
	{
		temp = sprite->texture[0];
		sprite->texture[0] = sprite->texture[7];
		sprite->texture[7] = temp;
		sprite->height = 5;
		sprite->hp--;
	}
	temp = NULL;
}

void	animation(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->sprcount)
	{
		if (env->sprite[i].movecount >= 5)
			{
				env->sprite[i].movecount = 0;
				env->sprite[i].texnum = env->sprite[i].texnum == 6 ? 0 : env->sprite[i].texnum + 1;
				mixtex(env, &env->sprite[i]);
			}
		if (env->sprite[i].type == 4 && env->sprite[i].hp != 665)
			mixtex(env, &env->sprite[i]);
	}
}

void	pistolrender(t_env *env)
{
	int *pix;
	int x;
	int	y;
	int a;
	int b;
	
	pix = (int *)(env->surface->pixels);
	y = 460;
	x = WWIN / 3 * 2;
	a = 0;
	b = 0;
	while (++y < HWIN)
	{
		x = WWIN / 3 * 2;
		while (++x < WWIN / 3 * 2 + 263)
		{
			if (((int *)(env->text[8 + env->shooting / 3]->pixels))
			[a % env->text[8 + env->shooting / 3]->h * (env->text[8 + env->shooting / 3]->w) + 
			b % env->text[8 + env->shooting / 3]->w] != -1)
				pix[y * WWIN + x] = ((int *)(env->text[8 + env->shooting / 3]->pixels))
			[a % env->text[8 + env->shooting / 3]->h * (env->text[8 + env->shooting / 3]->w) + 
			b % env->text[8 + env->shooting / 3]->w];
			b++;
		}
		a++;
	}
	if (env->shooting > 0)
		env->shooting--;
}

int		start_engine(t_env *env, SDL_Event *e, t_rend *rend)
{
	int		i;

	i = -1;
	
	while (++i < (int)env->nsectors)
		rend->sprq[i].visible = 0;
	SDL_LockSurface(env->surface);
	render_wall(env, rend);
	renderbutton(env, rend);
	rendersprite(env, rend);
	cross(env);
	animation(env);
	pistolrender(env);
	SDL_UnlockSurface(env->surface);
	//SDL_BlitSurface(env->text[8 + env->shooting / 5], NULL, env->surface, NULL);
	SDL_UpdateWindowSurface(env->window);
	handle_events(env, e);
	return (0);
}