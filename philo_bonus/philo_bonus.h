/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:12:32 by bcaffere          #+#    #+#             */
/*   Updated: 2022/01/26 19:18:01 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* to memset */
# include <string.h>

/* to printf */
# include <stdio.h>

/* to malloc, free, exit*/
# include <stdlib.h>

/* to write, usleep, fork */
# include <unistd.h>

/* to gettimeofday */
# include <sys/time.h>

/* to threads and mutex */
# include <pthread.h>

/* to kill */
# include <signal.h>

/* to waitpid */
# include <sys/wait.h>

/* to semaphores */
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define ERR_NUM "wrong numbers of arguments"
# define ERR_ARG "used bad argument"
# define ERR_CHK "read check-list attentive"
# define ERR_MTX "mutex init failed"
# define ERR_THR "thread create failed"
# define ERR_DTC "detach failed"
# define ERR_TIME "time init failed"
# define ERR_SEM "semaphore init failed"
# define ERR_FORK "fork failed"

typedef struct timeval	t_timeval;

typedef struct s_sim
{
	int			p_num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	sem_t		*forks;
	sem_t		*breaker;
	sem_t		*speak;
	t_timeval	start;
}t_sim;

typedef struct s_phil
{
	pthread_t	observ;
	pid_t		phil_pid;
	int			idx;
	t_timeval	last_eat;
	int			eat_count;
	t_sim		*sim;
}t_phil;

int				ft_atoi(const char *s);
void			err_msg(char *str);
unsigned long	time_in_ms(t_timeval time);
unsigned long	get_cur_time(t_sim *sim);
void			init_options(int argc, char *argv[], t_sim *sim);
void			init_phil(t_sim *sim, t_phil *phil);
void			init_sems(t_sim *sim);
void			phil_run(t_sim *sim, t_phil *phil);
void			close_sems(t_sim *sim);
void			*observer(void *arg);
#endif
