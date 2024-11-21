/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:00:42 by jetan             #+#    #+#             */
/*   Updated: 2024/11/21 17:43:27 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_philo *data, int ac, const char *av[])
{
	if (ac == 6)
		data->num_of_times_to_eat = ft_atoi(av[5]);
	else
	{
		data->num_of_philo = ft_atoi(av[1]);
		data->time_to_die = ft_atoi(av[2]);
		data->time_to_eat = ft_atoi(av[3]);
		data->time_to_sleep = ft_atoi(av[4]);
		pthread_mutex_init(&data->write_lock, NULL);
	}
}

void	create_thread(t_philo *data)
{

}

int main(int ac, const char *av[])
{
	t_philo	data;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of argument\n");
		return (1);
	}
	if (validate_arg(ac, av) == 0)
		return (1);
	init(&data, ac, av);
}
