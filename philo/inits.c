/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:13:26 by bcaffere          #+#    #+#             */
/*   Updated: 2022/01/29 16:33:48 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_options(t_sim *sim)
{
	if (sim->p_num < 1 || sim->time_to_die < 1 || sim->time_to_eat < 1
		|| sim->time_to_sleep < 1)
		return (err_msg(ERR_ARG));
	if (sim->p_num > 200)
		return (err_msg(ERR_CHK));
	return (0);
}

int	init_options(int argc, char *argv[], t_sim *sim)
{
	sim->p_num = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		sim->must_eat = ft_atoi(argv[5]);
		if (sim->must_eat < 1)
			return (err_msg(ERR_ARG));
	}
	else
		sim->must_eat = -1;
	sim->fed_up = 0;
	return (check_options(sim));
}

int	init_mutex(t_sim *sim)
{
	int	i;

	if (pthread_mutex_init(&(sim->breaker), NULL) != 0)
		return (err_msg(ERR_MTX));
	if (pthread_mutex_init(&(sim->speak), NULL) != 0)
		return (err_msg(ERR_MTX));
	i = -1;
	while (++i < sim->p_num)
		if (pthread_mutex_init(&(sim->forks[i]), NULL) != 0)
			return (err_msg(ERR_MTX));
	return (0);
}

int	init_philo(t_sim *sim, t_phil *phil)
{
	int	i;

	if (gettimeofday(&sim->start, NULL) != 0)
		return (1);
	i = 0;
	while (i < sim->p_num)
	{
		phil[i].idx = i;
		phil[i].left_fork = (i + 1) % sim->p_num;
		phil[i].right_fork = i;
		phil[i].eat_count = 0;
		phil[i].sim = sim;
		phil[i].last_eat = sim->start;
		i++;
	}
	return (0);
}
