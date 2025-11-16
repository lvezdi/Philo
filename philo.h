/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:50:11 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/11/16 13:50:11 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				left_f;
	int				right_f;
	long			last_meal;
	int				times_eaten;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_to_eat;
	int				stop;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	t_philo			*philos;
}	t_data;

long	ft_atoi(char *str);
int		ft_isnumeric(char *str);
int		verification(char **argv);
void	init(t_data *data, char **argv);
int		fork_initialisation(t_data *data);
int		philos_initialisation(t_data *data);
void	*philo_routine(void *arg);
void	clean_up(t_data *data);
void	print_message(t_philo *philo, char *msg);
int		error(void);
long	get_time(void);
void	*monitor_routine(void *arg);
int		start_threads(t_data *data);
int		handle_eating(t_philo *philo);

#endif
