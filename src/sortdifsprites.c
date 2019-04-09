/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortdifsprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:22:27 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/07 20:40:33 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	sortstobj(t_env *env, int i)
{
	
}

void	sortenemy(t_env *env, int i)
{
	
}

void	sorttrobj(t_env *env, int i)
{
	
}

void	sortdifsprites(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->sprcount)
	{
		if (env->sprite[i].type == 0)
			sortstobj(env, i);
		if (env->sprite[i].type == 1)
			sortenemy(env, i);
		if (env->sprite[i].type == 2)
			sorttrobj(env, i);
	}
}