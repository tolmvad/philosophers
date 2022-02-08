/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:04:10 by bcaffere          #+#    #+#             */
/*   Updated: 2022/01/26 19:16:44 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	phil_speak(t_sim *sim, int idx, char *msg)
{
	sem_wait(sim->speak);
	printf("%lu %d %s\n", get_cur_time(sim), idx + 1, msg);
	sem_post(sim->speak);
}

static void	phil_do(int time)
{
	t_timeval		current;
	unsigned long	do_before;

	gettimeofday(&current, NULL);
	do_before = time_in_ms(current) + time;
	while (time_in_ms(current) < do_before)
	{
		gettimeofday(&current, NULL);
		usleep(200);
	}
}

static void	phil_eat(t_sim *sim, t_phil *phil)
{
	sem_wait(sim->forks);
	phil_speak(sim, phil->idx, "has taken a fork");
	sem_wait(sim->forks);
	phil_speak(sim, phil->idx, "has taken a fork");
	sem_wait(sim->breaker);
	phil_speak(sim, phil->idx, "is eating");
	phil->eat_count++;
	gettimeofday(&phil->last_eat, NULL);
	sem_post(sim->breaker);
	phil_do(sim->time_to_eat);
	sem_post(sim->forks);
	sem_post(sim->forks);
	if (sim->must_eat == phil->eat_count)
	{
		sem_post(sim->breaker);
		exit(0);
	}
}

static void	routine(t_sim *sim, t_phil *phil)
{
	if (pthread_create(&(phil->observ), NULL, observer,
			(void *)phil) != 0)
		err_msg(ERR_THR);
	if (pthread_detach(phil->observ) != 0)
		err_msg(ERR_DTC);
	if (phil->idx % 2 == 0)
		usleep(200);
	while (1)
	{
		phil_eat(sim, phil);
		phil_speak(sim, phil->idx, "is sleeping");
		phil_do(sim->time_to_sleep);
		phil_speak(sim, phil->idx, "is thinking");
	}
}

void	phil_run(t_sim *sim, t_phil *phil)
{
	int	i;

	i = 0;
	while (i < sim->p_num)
	{
		phil[i].phil_pid = fork();
		if (phil[i].phil_pid == -1)
			err_msg(ERR_FORK);
		if (phil[i].phil_pid == 0)
			routine(sim, &(phil[i]));
		i++;
	}
}
