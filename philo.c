/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:05:19 by jetan             #+#    #+#             */
/*   Updated: 2024/12/21 23:38:59 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * checks the num of philo is less than 200
 * checks the input is only digit and not negative or zero
 */
int	validate_arg(int ac, char **av)
{
	int	arg;

	if (ft_atol(av[1]) > 200)
	{
		write(2, "Invalid number of philosophers\n", 31);
		return (1);
	}
	arg = 1;
	while (arg < ac)
	{
		if (!ft_isdigit(av[arg]) || ft_atol(av[arg]) <= 0)
		{
			write(2, "Invalid argument\n", 17);
			return (1);
		}
		arg++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		write(2, "Wrong number of argument\n", 25);
		return (1);
	}
	if (validate_arg(ac, av) == 1)
		return (1);
	init_data(&data, av);
	init_fork(&data);
	init_philo(&data, av);
	create_thread(&data);
	destroy_all_mutex(&data);
	free(data.philo);
	free(data.fork);
}
