/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 23:36:55 by jetan             #+#    #+#             */
/*   Updated: 2024/12/21 22:17:07 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo)
{
	print_message(philo, philo->philo_id, "is sleeping");
	usleep_ms(philo->time_to_sleep);
}

void	ft_eat(t_philo *philo)
{
	if (philo->num_philo == 1)
	{
		usleep_ms(philo->time_to_die);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, philo->philo_id, "has taken a fork");
	print_message(philo, philo->philo_id, "has taken a fork");
	print_message(philo, philo->philo_id, "is eating");
	pthread_mutex_lock(philo->do_lock);
	philo->eating = 1;
	philo->last_meal = get_time_ms();
	philo->num_meal++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->do_lock);
	usleep_ms(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
