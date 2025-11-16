/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:52:14 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/11/16 13:52:14 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	main(int argc, char **argv)
{
	t_data		data;
	int			i;
	pthread_t	monitor;

	i = 0;
	if (argc == 2)
	{
		char *args[6];
		int arg_count = 0;
		char *token = strtok(argv[1], " \t");
		while (token && arg_count < 5)
		{
			args[arg_count] = token;
			arg_count++;
			token = strtok(NULL, " \t");
		}
		if (arg_count < 4 || arg_count > 5)
			return (error());
		for (int j = 0; j < arg_count; j++)
			argv[j + 1] = args[j];
		argc = arg_count + 1;
	}
	if (argc != 5 && argc != 6)
		return (error());
	if (!verification(argv))
		return (error());
	init(&data, argv);
	if (fork_initialisation(&data))
		return (error());
	if (philos_initialisation(&data))
		return (error());
	if (start_threads(&data))
		return (error());
	pthread_create(&monitor, NULL, monitor_routine, &data);
	while (i < data.num_philos)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	clean_up(&data);
	return (0);
}*/

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;
	pthread_t	monitor;

	i = 0;
	if (argc != 5 && argc != 6)
		return (error());
	if (!verification(argv))
		return (error());
	init(&data, argv);
	if (fork_initialisation(&data))
		return (error());
	if (philos_initialisation(&data))
		return (error());
	if (start_threads(&data))
		return (error());
	pthread_create(&monitor, NULL, monitor_routine, &data);
	while (i < data.num_philos)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	clean_up(&data);
	return (0);
}
