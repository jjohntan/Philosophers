/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:45:48 by jetan             #+#    #+#             */
/*   Updated: 2024/12/21 22:29:38 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dead_or_done_lock);
	pthread_mutex_destroy(&data->do_lock);
	while (i < data->philo->num_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
}

/**
 * improved version of sleep function
 */
int	usleep_ms(long time)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < time)
		usleep(500);
	return (0);
}

/**
 * Accurate time tracking in milliseconds
 */
long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * this function assign the time to the philo struct
 */
void	assign_time(t_philo *philo, char **av)
{
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (av[5] != NULL)
		philo->num_for_philo_eat = ft_atol(av[5]);
	else
		philo->num_for_philo_eat = -1;
}
