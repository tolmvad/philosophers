/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:13:23 by bcaffere          #+#    #+#             */
/*   Updated: 2022/01/29 16:51:49 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_options(t_sim *sim)
{
	if (sim->p_num < 1 || sim->time_to_die < 1 || sim->time_to_eat < 1
		|| sim->time_to_sleep < 1)
		err_msg(ERR_ARG);
	if (sim->p_num > 200)
		err_msg(ERR_CHK);
}

void	init_options(int argc, char *argv[], t_sim *sim)
{
	if (argc < 5 || argc > 6)
		err_msg(ERR_NUM);
	sim->p_num = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		sim->must_eat = ft_atoi(argv[5]);
		if (sim->must_eat < 1)
			err_msg(ERR_ARG);
	}
	else
		sim->must_eat = -1;
	check_options(sim);
}

void	init_phil(t_sim *sim, t_phil *phil)
{
	int	i;

	if (gettimeofday(&sim->start, NULL) != 0)
		err_msg(ERR_TIME);
	i = 0;
	while (i < sim->p_num)
	{
		phil[i].idx = i;
		phil[i].eat_count = 0;
		phil[i].sim = sim;
		phil[i].last_eat = sim->start;
		i++;
	}
}

void	init_sems(t_sim *sim)
{
	sem_unlink("forks");
	sem_unlink("speak");
	sem_unlink("breaker");
	sim->forks = sem_open("forks", O_CREAT, S_IRWXU, sim->p_num);
	if (sim->forks == SEM_FAILED)
		err_msg(ERR_SEM);
	sim->speak = sem_open("speak", O_CREAT, S_IRWXU, 1);
	if (sim->speak == SEM_FAILED)
		err_msg(ERR_SEM);
	sim->breaker = sem_open("breaker", O_CREAT, S_IRWXU, 1);
	if (sim->breaker == SEM_FAILED)
		err_msg(ERR_SEM);
}
