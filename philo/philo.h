/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:52:29 by bcaffere          #+#    #+#             */
/*   Updated: 2022/01/26 19:11:36 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* to memset */
# include <string.h>

/* to printf */
# include <stdio.h>

/* to malloc, free */
# include <stdlib.h>

/* to write, usleep */
# include <unistd.h>

/* to gettimeofday */
# include <sys/time.h>

/* to threads and mutex */
# include <pthread.h>

# define ERR_NUM "wrong numbers of arguments"
# define ERR_ARG "used bad argument"
# define ERR_CHK "read check-list attentive"
# define ERR_MTX "mutex init failed"
# define ERR_THR "thread create failed"
# define ERR_DTC "detach failed"

typedef struct timeval	t_timeval;

typedef struct s_sim
{
	int				p_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				fed_up;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	breaker;
	pthread_mutex_t	speak;
	t_timeval		start;
}t_sim;

typedef struct s_phil
{
	pthread_t	thread;
	int			idx;
	int			left_fork;
	int			right_fork;
	t_timeval	last_eat;
	int			eat_count;
	t_sim		*sim;
}t_phil;

int				init_options(int argc, char *argv[], t_sim *sim);
int				init_mutex(t_sim *sim);
int				init_philo(t_sim *sim, t_phil *phil);
int				ft_atoi(const char *s);
int				err_msg(char *str);
unsigned long	time_in_ms(t_timeval time);
unsigned long	get_cur_time(t_sim *sim);
void			observer(t_sim *sim, t_phil *phil);
void			*routine(void *arg);
int				philo_run(t_sim *sim, t_phil *phil);

#endif
