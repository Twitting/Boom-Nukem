/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:20:03 by twitting          #+#    #+#             */
/*   Updated: 2019/03/06 18:00:37 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int main(void)
{
    t_env *env;

	env = structure_init();
    start_engine(env);
	printf("%lf", env->player.where.x);
}