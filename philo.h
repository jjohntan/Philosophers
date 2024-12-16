#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo
{
	int	num_of_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int	num_of_times_to_eat;
	int	id;
	int	eating;
	int	meals_eaten;// num of time eating
	size_t	last_meal;
	size_t	start_time;
	int	*done_or_dead;
	pthread_t	thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_data
{
	int	num_of_philo;
	int	dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_data;

int	validate_arg(int ac, char **av);
void	init_arg(t_philo *philo, int ac, char **av);
void	init_data(t_data *data, t_philo *philo);
void	init_fork(t_data *data, t_philo *philo);
void	init_philo(t_philo *philo, t_data *data);
void	create_thread(t_philo *philo);
void	*philo_routine(void *philo);

int	ft_isdigit(const char *str);
int	ft_atoi(const char *str);
size_t	get_current_time(void);
void	print_status(t_philo *philo, int id, char *str);
void	destroy_all(t_data *data);

void	ft_eat(t_philo *philo);
int	ft_usleep(size_t milliseconds);
void	ft_sleep(t_philo *philo);
int	done_loop(t_philo *philo);

#endif
