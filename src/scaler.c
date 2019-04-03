/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:58:04 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/03 14:14:46 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

int	scaler_next(t_scaler *sc)
{
	sc->cache += sc->fd;
	while (sc->cache >= sc->ca)
	{
		sc->result += sc->bop;
		sc->cache -= sc->ca;
	}
	return (sc->result);
}
