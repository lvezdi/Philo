/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:31:28 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/11/16 17:48:38 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!handle_eating(philo))
			break ;
		print_message(philo, "is sleeping\n");
		usleep(philo->data->time_to_sleep * 1000);
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		print_message(philo, "is thinking\n");
		usleep(5000);
	}
	return (NULL);
}

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos)
		free(data->philos);
	if (data->forks)
	{
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
}

void	print_message(t_philo *philo, char *msg)
{
	long	timestamp;

	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (!philo->data->stop)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d %s", timestamp, philo->id, msg);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
}

int	error(void)
{
	printf("Error: something went wrong\n");
	return (1);
}
