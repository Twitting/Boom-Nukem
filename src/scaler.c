/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:58:04 by ebednar           #+#    #+#             */
/*   Updated: 2019/03/28 13:07:57 by ebednar          ###   ########.fr       */
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
	return(sc->result);
}
