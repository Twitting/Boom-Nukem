/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mobattack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:28:49 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 20:12:32 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	mobcrushesface(t_env *env, int i)
{
	ESPRI.mobtimer = 0;
	if (env->player.hp > 50)
		Mix_PlayChannel(-1, env->sound[3], 0);
	else
		Mix_PlayChannel(-1, env->sound[4], 0);
	env->blood = 150;
	env->player.hp -= 10;
	if (env->player.hp <= 0)
	{
		Mix_HaltMusic();
		Mix_PlayChannel(-1, env->sound[13], 0);
		env->state = 6;
	}
}

void	mob_attack(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->sprcount)
	{
		if (ESPRI.type == 1)
		{
			if (ESPRI.spritedist <= 9)
			{
				ESPRI.mobtimer += (clock() - env->frame) /
											CLOCKS_PER_SEC;
				if (ESPRI.mobtimer >= 0.2)
					mobcrushesface(env, i);
			}
			else
				ESPRI.mobtimer = 0;
		}
	}
}
