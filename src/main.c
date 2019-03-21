/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:20:03 by twitting          #+#    #+#             */
/*   Updated: 2019/03/21 15:09:03 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	ft_error(int errnum)
{
	if (errnum == 1)
		ft_putendl_fd("FFFFFFFFFreeeee", 2);
	if (errnum == 2)
		ft_putendl_fd("Memory allocation error, aborting...", 2);
	if (errnum == 3)
		ft_putendl_fd("Something wrong with map file, aborting...", 2);
	if (errnum == 4)
		ft_putendl_fd("SDL initialization has failed, aborting...", 2);
	exit(errnum);
}

int main(void)
{
    t_env	*env;
	SDL_Event	e;

	env = structure_init();
	init(env);
	SDL_ShowCursor(SDL_DISABLE);
	while (!(env->quit))
		start_engine(env, &e);
	printf("%lf\n", PANGLE);
	SDL_DestroyWindow(env->window);
	SDL_Quit();
	return (0);
}