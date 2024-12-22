/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 23:30:36 by jetan             #+#    #+#             */
/*   Updated: 2024/12/21 18:25:48 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, int id, char *str)
{
	int	time;

	pthread_mutex_lock(philo->message_lock);
	time = get_time_ms() - philo->time_start_eat;
	if (philo_done_die(philo) == 0)
	{
		printf("%d %d %s\n", time, id, str);
	}
	pthread_mutex_unlock(philo->message_lock);
}

/**
 * check more than time to die and is not eating
 */
int	philo_die(t_philo *philo, int time_to_die)
{
	pthread_mutex_lock(philo->do_lock);
	if ((get_time_ms() - philo->last_meal) >= time_to_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->do_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->do_lock);
	return (0);
}

int	check_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		if (philo_die(&philo[i], philo[i].time_to_die) == 1)
		{
			print_message(&philo[i], philo[i].philo_id, "died");
			pthread_mutex_lock(philo->dead_or_done_lock);
			*philo->done_or_die = 1;
			pthread_mutex_unlock(philo->dead_or_done_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_done_eating(t_philo *philo)
{
	int	finish_eating;
	int	i;

	i = 0;
	finish_eating = 0;
	if (philo->num_for_philo_eat == -1)
		return (0);
	while (i < philo->num_philo)
	{
		pthread_mutex_lock(philo->do_lock);
		if (philo[i].num_meal >= philo[i].num_for_philo_eat)
			finish_eating++;
		pthread_mutex_unlock(philo->do_lock);
		i++;
	}
	if (finish_eating == philo->num_philo)
	{
		pthread_mutex_lock(philo->dead_or_done_lock);
		*philo->done_or_die = 1;
		pthread_mutex_unlock(philo->dead_or_done_lock);
		return (1);
	}
	return (0);
}

void	monitor(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
		if (check_dead(philo) == 1 || check_done_eating(philo) == 1)
			break ;
}
