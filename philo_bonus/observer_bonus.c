/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:15:35 by bcaffere          #+#    #+#             */
/*   Updated: 2022/01/26 19:17:00 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*observer(void *arg)
{
	t_phil		*phil;
	t_sim		*sim;
	t_timeval	current;

	phil = (t_phil *)arg;
	sim = phil->sim;
	usleep(200);
	while (1)
	{
		sem_wait(sim->breaker);
		gettimeofday(&current, NULL);
		if (time_in_ms(current) - time_in_ms(phil->last_eat)
			> (unsigned long)sim->time_to_die)
		{
			sem_wait(sim->speak);
			printf("%ld %d %s\n", get_cur_time(sim), phil->idx + 1, "died");
			exit(1);
		}
		sem_post(sim->breaker);
	}
}

void	close_sems(t_sim *sim)
{
	sem_close(sim->forks);
	sem_close(sim->speak);
	sem_close(sim->breaker);
	sem_unlink("forks");
	sem_unlink("speak");
	sem_unlink("breaker");
}
