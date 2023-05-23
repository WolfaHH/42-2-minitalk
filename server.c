/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngodard <ngodard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:18:29 by ngodard           #+#    #+#             */
/*   Updated: 2023/05/18 17:18:29 by ngodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minitalk.h"

static	void	signal_handler(int sig, siginfo_t *info, void *ctx)
{
	static int				bit_count = 0;
	static pid_t			sender_pid = 0;
	static unsigned char	character = 0;

	(void)ctx;
	if (!sender_pid)
		sender_pid = info->si_pid;
	character |= (sig == SIGUSR2);
	if (++bit_count == 8)
	{
		bit_count = 0;
		if (!character)
		{
			kill(sender_pid, SIGUSR2);
			sender_pid = 0;
			return ;
		}
		ft_printf("%c", character);
		character = 0;
		kill(sender_pid, SIGUSR1);
	}
	else
		character <<= 1;
}

int	main(void)
{
	struct sigaction	sig_act;

	ft_printf("Hello my dear ! 🇨🇭 \n");
	ft_printf("Welcome to the best project in the world ! \n");
	ft_printf("  Server PID is : %d\n", getpid());
	sig_act.sa_sigaction = signal_handler;
	sig_act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig_act, 0);
	sigaction(SIGUSR2, &sig_act, 0);
	while (1)
		pause();
	return (0);
}
