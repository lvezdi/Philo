/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:59:31 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/09/15 17:59:31 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>


/*typedef struct s_data
{
    int     num_philos;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    num_to_eat;
    pthread_mutex_t    *forks;
    pthread_mutex_t     print_mutex;
    struct t_philo  *philos;
    int             stop;
    pthread_mutex_t stop_mutex;
    long            start_time;
}       t_data;

typedef struct s_philo
{
    int id;
    int left_f;
    int right_f;
    pthread_mutex_t    *left_fork;
    pthread_mutex_t    *right_fork;
    pthread_t           thread;
    long            last_meal;
    int             meals_eaten;
    struct t_data  *data;
}       t_philo;*/

typedef struct s_data t_data;

typedef struct s_philo
{
    int             id;
    int             left_f;
    int             right_f;
    long            last_meal;
    int             times_eaten;
    int             meals_eaten;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data          *data;
}   t_philo;

typedef struct s_data
{
    int             num_philos;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             num_to_eat;
    int             stop;
    long            start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t stop_mutex;
    t_philo         *philos;
}   t_data;

long    ft_atoi(char *str);
int     ft_isnumeric(char *str);
int     verification(char **argv);
void    init(t_data *data, char **argv);
int     fork_initialisation(t_data *data);
int     philos_initialisation(t_data *data);
void    *philo_routine(void *arg);
void    clean_up(t_data *data);
void    print_message(t_philo *philo, char *msg);
int error(void);
long    get_time(void);
void    *monitor_routine(void *arg);
int start_threads(t_data *data);

# endif
