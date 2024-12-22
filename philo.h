/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:48:58 by jetan             #+#    #+#             */
/*   Updated: 2024/12/20 23:21:02 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				num_philo;
	int				philo_id;
	int				eating;
	int				num_meal;
	long			last_meal;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			time_start_eat;
	int				num_for_philo_eat;
	int				*done_or_die;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*dead_or_done_lock;
	pthread_mutex_t	*do_lock;
	pthread_mutex_t	*message_lock;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				done_or_die;
	pthread_mutex_t	dead_or_done_lock;
	pthread_mutex_t	do_lock;
	pthread_mutex_t	message_lock;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_data;

int		validate_arg(int ac, char **av);
//init
void	init_fork(t_data *data);
void	init_philo(t_data *data, char **av);
void	init_data(t_data *data, char **av);
//utils
long	ft_atol(const char *str);
int		ft_isdigit(const char *str);
long	get_time_ms(void);
void	assign_time(t_philo *philo, char **av);
int		usleep_ms(long time);
void	destroy_all_mutex(t_data *data);
//thread
void	create_thread(t_data *data);
void	routine(void *arg);
int		philo_done_die(t_philo *philo);
//monitor
void	print_message(t_philo *philo, int id, char *str);
int		check_dead(t_philo *philo);
int		check_done_eating(t_philo *philo);
void	monitor(void *arg);
int		philo_die(t_philo *philo, int time_to_die);
//routine
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);

#endif
