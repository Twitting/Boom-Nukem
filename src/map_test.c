/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:25:09 by twitting          #+#    #+#             */
/*   Updated: 2019/03/21 15:09:03 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	neighborstosect(t_sector *sect, char *line, int i)
{
	int	count;

	count = 0;
	while (line[i] != '\0')
	{
		sect->neighbors[count] = ft_atoi(&line[i]);
		while (line[i] != ' ' && line[i] != '\0')
			i++;
		count++;
		if (line[i] == '\0')
			break ;
		i++;
	}
}

void	verttosect(t_env *env, t_sector *sect, char *line, int i)
{
	int	j;
	int count;

	count = 0;
	i++;
	j = i;
	sect->light = 1;
	sect->npoints = 1;
	while (line[j] != '\t')
	{
		if (line[j] == ' ')
			sect->npoints++;
		j++;
	}
	sect->neighbors = (int *)malloc(sizeof(int) * sect->npoints);
	sect->vertex = (t_xy *)malloc(sizeof(t_xy) * sect->npoints);
	while (line[i] != '\t')
	{
		sect->vertex[count] = env->vertex[ft_atoi(&line[i])];
		while (line[i] != ' ' && line[i] != '\t')
			i++;
		count++;
		i++;
	}
	neighborstosect(sect, line, i);
}

void	parseplayer(t_env *env, char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\t')
		i++;
	PWHERE.x = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	PWHERE.y = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	PANGLE = (ft_atoi(&line[i]) % 360) * M_PI / 180;
	while (line[i] != ' ')
		i++;
	PSECT = ft_atoi(&line[i]);
	ft_putnbr(PSECT);
	PVELOSITY.x = 0.0;
	PVELOSITY.y = 0.0;
	PVELOSITY.z = 0.0;
	env->player.yaw = 0.0;
	PWHERE.z = env->sector[PSECT].floor + EYEHEIGHT;
}

void	parsesectors(t_env *env, int fd)
{
	char	*line;
	int		count;
	int		i;

	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		if (line[0] == 's')
		{
			i += 7;
			env->sector[count].floor = ft_atoi(&line[i]);
			while (line[i] != ' ')
				i++;
			env->sector[count].ceiling = ft_atoi(&line[i]);
			while (line[i] != '\t')
				i++;
			verttosect(env ,&env->sector[count], line, i);
		}
		else if (line[0] == 'p')
			parseplayer(env, line);
		free(line);
		count++;
	}
}

void	parsevertexes(t_env *env,int fd)
{
	char	*line;
	int		count;
	int		i;

	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		if (line[0] == 'v')
		{
			i += 7;
			env->vertex[count].y = ft_atoi(&line[i]);
			while (line[i] != '\t')
				i++;
			env->vertex[count].x = ft_atoi(&line[i]);
		}
		else if (line[0] != 'v')
		{
			free(line);
			break ;
		}
		free(line);
		count++;
	}
}

void	getvertsectnums(t_env *env)
{
	int		fd;
	char	*line;
	
	env->nsectors = 0;
	env->nvertexes = 0;
	if ((fd = open("test.map", O_RDONLY)) < 0)
		ft_putstr("openerr\n");
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v')
			env->nvertexes++;
		else if (line[0] == 's')
			env->nsectors++;
		free(line);
	}
	close(fd);
	env->sector = (t_sector *)malloc(sizeof(t_sector) * (env->nsectors));
	env->vertex = (t_xy *)malloc(sizeof(t_xy) * env->nvertexes);
}

t_env	*structure_init(void)
{
	t_env			*env;
	int				fd;

	env = (t_env *)malloc(sizeof(t_env));
	if ((fd = open("test.map", O_RDONLY)) < 0)
		ft_putstr("openerr\n");
	getvertsectnums(env);
	parsevertexes(env, fd);
	parsesectors(env, fd);

	/*env->nsectors = 2;
	env->nvertexes = 6;
	env->sector = (t_sector *)malloc(sizeof(t_sector) * (env->nsectors));
	while (i < env->nsectors)
	{
		env->sector[i].vertex = (t_xy *)malloc(sizeof(t_xy) * 4);
		env->sector[i].floor = 0.0;
		env->sector[i].ceiling = 15.0;
		env->sector[i].npoints = 4;
		env->sector[i].light = 1;
		i++;
	}
	env->sector[1].ceiling = 1000.0;
	env->sector[1].floor = 2.0;

	env->sector[0].neighbors = (int *)malloc(sizeof(int) * 4);
	env->sector[0].neighbors[0] = -1;
	env->sector[0].neighbors[1] = -1;
	env->sector[0].neighbors[2] = 1;
	env->sector[0].neighbors[3] = -1;
	env->sector[1].neighbors = (int *)malloc(sizeof(int) * 4);
	env->sector[1].neighbors[0] = 0;
	env->sector[1].neighbors[1] = -1;
	env->sector[1].neighbors[2] = -1;
	env->sector[1].neighbors[3] = -1;
	i = 0;
	env->vertex = (t_xy *)malloc(sizeof(t_xy) * env->nvertexes);
	
	env->vertex[0].x = 5.0;
	env->vertex[0].y = 5.0;
	env->vertex[1].x = 50.0;
	env->vertex[1].y = 5.0;
	env->vertex[2].x = 5.0;
	env->vertex[2].y = 57.0;
	env->vertex[3].x = 5.0;
	env->vertex[3].y = 50.0;
	env->vertex[4].x = 50.0;
	env->vertex[4].y = 50.0;
	env->vertex[5].x = 50.0;
	env->vertex[5].y = 90.0;

	env->sector[0].vertex[0] = env->vertex[0];
	env->sector[0].vertex[1] = env->vertex[1];
	env->sector[0].vertex[2] = env->vertex[4];
	env->sector[0].vertex[3] = env->vertex[3];
	env->sector[1].vertex[0] = env->vertex[3];
	env->sector[1].vertex[1] = env->vertex[4];
	env->sector[1].vertex[2] = env->vertex[5];
	env->sector[1].vertex[3] = env->vertex[2];
	PWHERE.x = 20.0;
	PWHERE.y = 50.0;
	PVELOSITY.x = 0.0;
	PVELOSITY.y = 0.0;
	PVELOSITY.z = 0.0;
	PANGLE = 0.0;
	PSECT = 0;
	env->player.yaw = 0.0;
	PWHERE.z = env->sector[PSECT].floor + EYEHEIGHT;
*/

	return (env);
}