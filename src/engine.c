/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:37:47 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/12 16:43:11 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
	int	xyab[4];

	pix = (int *)(env->surface->pixels);
	xyab[1] = 460;
	xyab[0] = WWIN / 3 * 2;
	xyab[2] = 0;
	xyab[3] = 0;
	while (++xyab[1] < HWIN)
	{
		xyab[0] = WWIN / 3 * 2;
		while (++xyab[0] < WWIN / 3 * 2 + 263)
		{
			if (((int *)(env->text[8 + env->shooting / 3]->pixels))
			[xyab[2] % env->text[8 + env->shooting / 3]->h * (env->text[8 + env->shooting / 3]->w) +
			xyab[3] % env->text[8 + env->shooting / 3]->w] != -1)
				pix[xyab[1] * WWIN + xyab[0]] = ((int *)(env->text[8 + env->shooting / 3]->pixels))
			[xyab[2] % env->text[8 + env->shooting / 3]->h * (env->text[8 + env->shooting / 3]->w) +
			xyab[3] % env->text[8 + env->shooting / 3]->w];
			xyab[3]++;
		}
		xyab[2]++;
	}
	if (env->shooting > 0)
		env->shooting--;
}

int		start_engine(t_env *env, SDL_Event *e, t_rend *rend)
{
	int		i;

	i = -1;
	ft_putchar('A');
	while (++i < (int)env->nsectors)
		rend->sprq[i].visible = 0;
	SDL_LockSurface(env->surface);
	render_wall(env, rend);
	ft_putchar('b');
	renderbutton(env, rend);
	ft_putchar('C');
	rendersprite(env, rend);
	ft_putchar('d');
	cross(env);
	ft_putchar('E');
	animation(env);
	ft_putchar('f');
	pistolrender(env);
	ft_putchar('G');
	SDL_UnlockSurface(env->surface);
	SDL_UpdateWindowSurface(env->window);
	ft_putchar('h');
	handle_events(env, e);
	ft_putchar('I');
	return (0);
}
