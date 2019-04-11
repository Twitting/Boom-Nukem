/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mobattack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:28:49 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/11 19:52:23 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

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
				{
					env->sprite[i].mobtimer = 0;
					env->player.hp -= 10;
					printf("%d\n", env->player.hp);
				}
			}
			else
			{
				env->sprite[i].mobtimer = 0;
			}
		}
	}
}
