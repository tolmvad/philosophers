/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:52:43 by bcaffere          #+#    #+#             */
/*   Updated: 2022/01/25 23:04:30 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_sim	sim;
	t_phil	phil[200];

	if (argc < 5 || argc > 6)
		return (err_msg(ERR_NUM));
	if (init_options(argc, argv, &sim))
		return (1);
	if (init_philo(&sim, phil) || init_mutex(&sim))
		return (1);
	if (philo_run(&sim, phil))
		return (1);
	observer(&sim, phil);
	return (0);
}
