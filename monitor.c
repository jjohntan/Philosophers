/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:57:17 by jetan             #+#    #+#             */
/*   Updated: 2024/12/17 15:22:31 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (*philo->done_or_dead == 1)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_ate(t_philo *philo)
{
	int	finished_eating;
	int	i;

	i = 0;
	finished_eating = 0;
	if (philo[0].num_of_times_to_eat == -1)
		return (0);
	while (i < philo[0].num_of_philo)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[i].num_of_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (finished_eating == philo[0].num_of_philo)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->done_or_dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

int	check_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philo)
	{
		if (philo_dead(&philo[i]))
		{
			print_status(&philo[i], philo[i].id, "died");
			pthread_mutex_lock(philo[0].dead_lock);
			*philo->done_or_dead = 1;
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (check_dead(philo) == 1 || check_ate(philo) == 1)
			break ;
	}
	return (data);
}
