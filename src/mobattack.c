/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mobattack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:28:49 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 12:37:18 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	mobcrushesface(t_env *env, int i)
{
	env->sprite[i].mobtimer = 0;
	if (env->player.hp > 50)
		Mix_PlayChannel(-1, env->sound[3], 0);
	else
		Mix_PlayChannel(-1, env->sound[4], 0);
	env->blood = 150;
	env->player.hp -= 10;
	if (env->player.hp <= 0)
		env->state = 6;
}

void	mob_attack(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->sprcount)
	{
		if (env->sprite[i].type == 1)
		{
			if (env->sprite[i].spritedist <= 5)
			{
				env->sprite[i].mobtimer += (clock() - env->frame) /
											CLOCKS_PER_SEC;
				if (env->sprite[i].mobtimer >= 0.5)
					mobcrushesface(env, i);
			}
			else
				env->sprite[i].mobtimer = 0;
		}
	}
}
