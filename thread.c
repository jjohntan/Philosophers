/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:45:40 by jetan             #+#    #+#             */
/*   Updated: 2024/12/21 23:14:38 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_done_die(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_or_done_lock);
	if (*philo->done_or_die == 1)
	{
		pthread_mutex_unlock(philo->dead_or_done_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_or_done_lock);
	return (0);
}

void	routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->philo_id % 2 == 0)
		usleep_ms(3);
	while (philo_done_die(philo) == 0)
	{
		ft_eat(philo);
		ft_sleep(philo);
		print_message(philo, philo->philo_id, "is thinking");
	}
}

void	create_thread(t_data *data)
{
	pthread_t	check_philo;
	int			i;

	if (pthread_create(&check_philo, NULL, (void *)monitor,
			data->philo) != 0)
		destroy_all_mutex(data);
	i = 0;
	while (i < data->philo->num_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, (void *)routine,
				&data->philo[i]) != 0)
			destroy_all_mutex(data);
		i++;
	}
	if (pthread_join(check_philo, NULL) != 0)
		destroy_all_mutex(data);
	i = 0;
	while (i < data->philo->num_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			destroy_all_mutex(data);
		i++;
	}
}
