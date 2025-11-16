/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:31:28 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/11/16 13:45:15 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*static int	handle_eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork\n");
		pthread_mutex_unlock(philo->left_fork);
		usleep(philo->data->time_to_die * 1000);
		return (0);
	}
	first_fork = philo->left_f < philo->right_f ? philo->left_fork : philo->right_fork;
	second_fork = philo->left_f < philo->right_f ? philo->right_fork : philo->left_fork;
	pthread_mutex_lock(first_fork);
	print_message(philo, "has taken a fork\n");
	pthread_mutex_lock(second_fork);
	print_message(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_message(philo, "is eating\n");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!handle_eating(philo))
			break ;
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
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
	}
	return (NULL);
}*/

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (handle_eating(philo))
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
