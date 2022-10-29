/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopopa <sopopa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:41:14 by mbardett          #+#    #+#             */
/*   Updated: 2022/10/29 18:23:21 by sopopa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
/*The (siginfo_t) *info is a struct that contains several informations,
in our case we want to fetch the Client process's ID(PID), so that the Server
will be able to reply with its own signal(bonus assignment);
We are going to use an unsigned char because:"Unsigned char is guaranteed
never to have trap values, and its values are pure binary notation.
You access any object as an array of unsigned char to view its value
representation-Brian Rodenborn"[quoting Default User
@https://bytes.com/topic/c/answers/61480-why-use-unsigned-char-ever]

"c |= (sig == SIGUSR1);" is the the same as
"if (signum == SIGUSR1)
		c |= 1;
 if (signum == SIGUSR2)
		c |= 0;"

(because the subject for this project demands to use SIGUSR1 and SIGUSR2);
less intuitive but it's shorter and waaay more elegant, thx Shadowaker!
https://github.com/Shadowaker/42_Minitalk/blob/master/server_bonus.c
Even though we call it ft_handler, it actually replicates
the sigaction prototype*/

void	ft_who_says_what(pid_t pid, int *flag)
{
	if (*flag == 0)
	{
		ft_putstr_fd("Client ", 1);
		ft_putnbr_fd(pid, 1);
		ft_putstr_fd(" says: ", 1);
		*flag = 1;
	}
}

void	ft_handler(int signum, siginfo_t *info, void *ucontext)
{
	static unsigned char	c = 0;
	static int				i = 0;
	pid_t					client_pid;
	static int				flag = 0;

	c |= (signum == SIGUSR1);
	(void)ucontext;
	client_pid = info->si_pid;
	ft_who_says_what(client_pid, &flag);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(client_pid, SIGUSR2);
			ft_putstr_fd("\nEnd of transmission\n", 1);
			flag = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	else
		c <<= 1;
}

static void	ft_show_pid(pid_t pid)
{
	ft_putstr_fd("Current PID is: ", 1);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
}

/* Since we are going to handle signals, we must init the sigaction struct;
such struct will allow us to specify certain behaviours, as it contains
pointers to functions and flags;by default, to handle signals, the function
void(*sa_handler)(int)would be used but it takes only one argument.
/we want to define our behaviour using more than one argument(we need 2
args in this case, one is the signal to "catch" and the other is the pid of
the process we are receiving the signal from);"switching on"the SA_SIGINFO
flag(tbh it's a struct) allows to use sa_sigaction, which is an ass-kicking
version of sa_handler, as it takes three args and therefore fulfills our scope */
int	main(void)
{
	struct sigaction	sa;
	pid_t				ser_pid;

	ser_pid = getpid();
	ft_show_pid(ser_pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
	{
		pause();
	}
	return (0);
}
