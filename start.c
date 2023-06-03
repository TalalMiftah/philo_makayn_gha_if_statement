#include "philo.h"

t_est	*ft_lstlast(t_est *lst)
{
	t_est	*h;

	h = lst;
	while (1)
	{
		if (h->next == lst)
			break ;
		h = h->next;
	}
	return (h);
}

t_est	*lst_new(int n, t_philo *phi)
{
	t_est	*h;

	h = malloc(sizeof(t_est));
	if (!h)
		return (NULL);
	pthread_mutex_init(&h->fork_t, NULL);
	h->index = n;
	h->d = 0;
	h->eat_t = 0;
	h->last_meal = 0;
	h->next = h;
	h->prev = h;
	h->phi = phi;
	return (h);
}

void	ft_lstadd_back(t_est **l, t_est *new)
{
	t_est	*swap;
	t_est	*h;

	h = *l;
	if (!l || !new)
		return ;
	if (!*l)
	{
		*l = new;
		return ;
	}
	swap = ft_lstlast(h);
	swap->next = new;
	new->prev = swap;
	new->next = h;
	h->prev = new;
}

long long	current_time(void)
{
	struct timeval	taw9it;

	gettimeofday(&taw9it, NULL);
	return ((taw9it.tv_sec * 1000) + (taw9it.tv_usec / 1000));
}

int	u_sleep(long long r, t_est *philo)
{
	long long	current;

	current = current_time();
	while (current_time() < r + current)
	{
		if (yak_akhoya_marwan(philo) == 0)
			return (0);
		usleep(100);
	}
	return (1);
}

void	message_t(unsigned long long i, int index, char *str, t_est *philo)
{
	pthread_mutex_lock(&philo->phi->print);
	printf("%lld\t%d\t%s\n", current_time() - i, index, str);
	pthread_mutex_unlock(&philo->phi->print);
}

int	check(t_philo *philo)
{
	t_est	*h;

	h = philo->head;
	if (philo->ac == 6)
	{
		while (1)
		{
			if (h->eat_t < philo->time_op)
				return (0);
			h = h->next;
			if (h == philo->head)
				break ;
		}
		return (1);
	}
	return (0);
}

void	unlock(t_philo *philo, t_est *h)
{
	pthread_mutex_unlock(&philo->death);
	pthread_mutex_unlock(&h->fork_t);
	pthread_mutex_unlock(&h->next->fork_t);
}

int	yak_akhoya_marwan(t_est *philo)
{
	pthread_mutex_lock(&philo->phi->death);
	if (check(philo->phi))
	{
		unlock(philo->phi, philo);
		return (0);
	}
	if ((current_time() - philo->last_meal > philo->phi->time_to_die)
		&& philo->phi->d1 == 0)
	{
		philo->phi->d1 = 1;
		philo->d = 1;
		philo->phi->index = philo->index;
		unlock(philo->phi, philo);
		return (0);
	}
	if (philo->phi->d1 == 1)
	{
		philo->d = 1;
		unlock(philo->phi, philo);
		return (0);
	}
	pthread_mutex_unlock(&philo->phi->death);
	return (1);
}

void	*routine1(void *point)
{
	t_est *h;

	h = (t_est *)point;
	message_t(h->phi->start, h->index, "has take a fork", h);
	u_sleep(h->phi->time_to_die, h);
	h->phi->d1 = 1;
	h->phi->index = 1;
	return (NULL);
}

// int	norm(t_est *h)
// {
// 	pthread_mutex_lock(&h->fork_t);
// 	message_t(h->phi->start, h->index, "has take a fork", h);
// 	pthread_mutex_lock(&h->next->fork_t);
// 	message_t(h->phi->start, h->index, "has take a fork", h);
// 	message_t(h->phi->start, h->index, "is eating", h);
// 	pthread_mutex_lock(&h->phi->death);
// 	h->last_meal = current_time();
// 	h->eat_t++;
// 	pthread_mutex_unlock(&h->phi->death);
// 	if (u_sleep(h->phi->time_to_eat, h) == 0)
// 		return (1);
// 	pthread_mutex_unlock(&h->next->fork_t);
// 	pthread_mutex_unlock(&h->fork_t);
// 	message_t(h->phi->start, h->index, "is sleeping", h);
// 	if (u_sleep(h->phi->time_to_sleep, h) == 0)
// 		return (1);
// 	message_t(h->phi->start, h->index, "is thinking", h);
// 	return (0);
// }

void	*routine(void *point)
{
	t_est *h;

	h = (t_est *)point;
	if(h->index % 2 == 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&h->fork_t);
		message_t(h->phi->start, h->index, "has take a fork", h);
		pthread_mutex_lock(&h->next->fork_t);
		message_t(h->phi->start, h->index, "has take a fork", h);
		message_t(h->phi->start, h->index, "is eating", h);
		if (u_sleep(h->phi->time_to_eat, h) == 0)
			break ;
		pthread_mutex_lock(&h->phi->death);
		h->last_meal = current_time();
		h->eat_t++;
		pthread_mutex_unlock(&h->phi->death);
		pthread_mutex_unlock(&h->next->fork_t);
		pthread_mutex_unlock(&h->fork_t);
		message_t(h->phi->start, h->index, "is sleeping", h);
		if (u_sleep(h->phi->time_to_sleep, h) == 0)
			break ;
		message_t(h->phi->start, h->index, "is thinking", h);
	}
	return NULL;
}
