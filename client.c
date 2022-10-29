/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 20:57:35 by mbardett          #+#    #+#             */
/*   Updated: 2022/08/15 18:29:32 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static void	ft_handler(int signum)
{
	static int	i = 0;

	if (signum == SIGUSR1)
	{
		ft_putstr_fd("Roger!\n", 1);
		i++;
	}
	else
	{
		ft_putstr_fd("All the eagles returned to their nests\n", 1);
		exit(0);
	}
}

static void	ft_whispers(pid_t pid, char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

static void	ft_feed(pid_t pid, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_whispers(pid, str[i]);
		usleep(100);
		i++;
		if (str[i] == '\0')
		{
			ft_whispers(pid, str[i]);
			usleep(100);
		}
	}
}

//check the number of args and the existence of a message to send;
//then convert the(Server's PID)from *char to int using ft_atoi then send
//signals to ft_handler; the "while,pause()"is in order to wait for signals from
//clients
int	main(int argc, char **argv)
{
	pid_t	ser_pid;

	if (argc != 3)
	{
		ft_putstr_fd("Error: expected 2 arguments after program name", 2);
		return (0);
	}
	if (ft_strlen(argv[2]) == 0)
	{
		ft_putstr_fd("The sound of silence...\n", 2);
		return (0);
	}
	ser_pid = ft_atoi_mini(argv[1]);
	signal(SIGUSR2, ft_handler);
	signal(SIGUSR1, ft_handler);
	ft_feed(ser_pid, argv[2]);
	while (1)
	{
		pause();
	}
	return (0);
}
