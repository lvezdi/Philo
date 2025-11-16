/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:51:15 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/11/16 13:51:15 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_data *data, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_to_eat = -1;
	if (argv[5])
		data->num_to_eat = ft_atoi(argv[5]);
	data->stop = 0;
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->start_time = get_time();
}

int	fork_initialisation(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (data->forks == NULL)
		return (1);
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	philos_initialisation(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (data->philos == NULL)
		return (1);
	memset(data->philos, 0, sizeof(t_philo) * data->num_philos);
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].left_f = i;
		data->philos[i].right_f = (i + 1) % data->num_philos;
		data->philos[i].left_fork = &data->forks[data->philos[i].left_f];
		data->philos[i].right_fork = &data->forks[data->philos[i].right_f];
		data->philos[i].last_meal = data->start_time;
		data->philos[i].times_eaten = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
