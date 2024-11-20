/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:12:28 by jetan             #+#    #+#             */
/*   Updated: 2024/11/18 18:56:11 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_arg(int ac, char **av)
{
	int	arg;
	int	index;
	
	arg = 1;
	while (arg < ac)
	{
		index = 0;
		while (av[arg][index])
		{
			if (!ft_isdigit(av[arg][index]))
			{
				printf("Invalid argument\n");
				return (0);
			}
			index++;
		}
		arg++;
	}
	return (1);
}
