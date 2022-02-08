/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:52:43 by bcaffere          #+#    #+#             */
/*   Updated: 2022/01/26 19:16:57 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_sim	sim;
	t_phil	phil[200];
	int		wstatus;
	int		i;

	init_options(argc, argv, &sim);
	init_phil(&sim, phil);
	init_sems(&sim);
	phil_run(&sim, phil);
	i = -1;
	while (++i < sim.p_num)
	{
		waitpid(-1, &wstatus, 0);
		if (wstatus != 0)
		{
			i = -1;
			while (++i < sim.p_num)
				kill(phil[i].phil_pid, SIGTERM);
			break ;
		}
	}
	close_sems(&sim);
	return (0);
}
