/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:00:56 by bcaffere          #+#    #+#             */
/*   Updated: 2022/01/25 23:01:23 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_dead(t_sim *sim, t_phil *phil, t_timeval current)
{
	if (time_in_ms(current) - time_in_ms(phil->last_eat)
		> (unsigned long)sim->time_to_die)
	{
		pthread_mutex_lock(&sim->speak);
		printf("%ld %d %s\n", get_cur_time(sim), phil->idx + 1, "died");
		return (1);
	}
	return (0);
}

void	observer(t_sim *sim, t_phil *phil)
{
	int			i;
	t_timeval	current;

	i = 0;
	usleep(200);
	while (1)
	{
		if (i == sim->p_num)
			i = 0;
		pthread_mutex_lock(&sim->breaker);
		gettimeofday(&current, NULL);
		if (check_dead(sim, &phil[i], current))
			break ;
		pthread_mutex_unlock(&sim->breaker);
		if (sim->fed_up == sim->p_num)
		{
			pthread_mutex_lock(&sim->speak);
			break ;
		}
		i++;
	}
}
