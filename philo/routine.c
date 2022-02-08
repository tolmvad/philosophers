/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:04:10 by bcaffere          #+#    #+#             */
/*   Updated: 2022/01/25 23:06:46 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	phil_speak(t_sim *sim, int idx, char *msg)
{
	pthread_mutex_lock(&sim->speak);
	printf("%lu %d %s\n", get_cur_time(sim), idx + 1, msg);
	pthread_mutex_unlock(&sim->speak);
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
	pthread_mutex_lock(&sim->forks[phil->right_fork]);
	phil_speak(sim, phil->idx, "has taken a fork");
	pthread_mutex_lock(&sim->forks[phil->left_fork]);
	phil_speak(sim, phil->idx, "has taken a fork");
	pthread_mutex_lock(&sim->breaker);
	phil_speak(sim, phil->idx, "is eating");
	phil->eat_count++;
	gettimeofday(&phil->last_eat, NULL);
	if (phil->eat_count == sim->must_eat)
		sim->fed_up++;
	pthread_mutex_unlock(&sim->breaker);
	phil_do(sim->time_to_eat);
	pthread_mutex_unlock(&sim->forks[phil->right_fork]);
	pthread_mutex_unlock(&sim->forks[phil->left_fork]);
}

void	*routine(void *arg)
{
	t_sim	*sim;
	t_phil	*phil;

	phil = (t_phil *)arg;
	sim = phil->sim;
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

int	philo_run(t_sim *sim, t_phil *phil)
{
	int	i;

	i = 0;
	while (i < sim->p_num)
	{
		if (pthread_create(&phil[i].thread, NULL, routine,
				(void *)(&phil[i])) != 0)
			return (err_msg(ERR_MTX));
		if (pthread_detach(phil[i].thread) != 0)
			return (err_msg(ERR_DTC));
		i++;
	}
	return (0);
}
