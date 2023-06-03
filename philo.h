/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:11:43 by tmiftah           #+#    #+#             */
/*   Updated: 2023/05/17 19:35:42 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct test
{
	pthread_t			philo_id;
	pthread_mutex_t		fork_t;
	int					index;
	int					eat_t;
	unsigned int		d;
	long long			last_meal;
	struct test			*next;
	struct test			*prev;
	struct philo		*phi;
}						t_est;

typedef struct philo
{
	int						ac;
	int						i;
	int						number_of_philos;
	int						index;
	t_est					*head;
	unsigned int			d1;
	long long				start;
	long long				time_to_die;
	long long				time_to_sleep;
	long long				time_to_eat;
	long long				time_op;
	pthread_mutex_t			death;
	pthread_mutex_t			eat;
	pthread_mutex_t			print;
	struct timeval			time;
}							t_philo;

int			initial(t_philo *philo, char **str, int ac);
int			start(t_philo *philo);
int			ft_atoi(const char *str);
int			yak_akhoya_marwan(t_est *philo);
int			ft_parsing(char **av, t_philo *philo);
void		ft_lstadd_back(t_est **l, t_est *new);
t_est		*lst_new(int n, t_philo *phi);
t_est		*ft_lstlast(t_est *lst);
void		*routine(void *point);
void		*routine1(void *point);
long long	current_time(void);
int			u_sleep(long long r, t_est *philo);
void		message_t(unsigned long long i, int index, char *str, t_est *philo);

#endif