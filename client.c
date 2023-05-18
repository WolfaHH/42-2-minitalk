#include "minitalk.h"

static void	handle_signal(int signal_type)
{
	static int	msg_count = 0;

	if (signal_type == SIGUSR1)
		++msg_count;
	else
	{
		ft_printf("%d\n", msg_count);
		exit(0);
	}
}

static void	send_signals(int target_pid, char *msg)
{
	int		bit_pos;
	char	current_char;

	while (*msg)
	{
		bit_pos = 8;
		current_char = *msg++;
		while (bit_pos--)
		{
			if (current_char >> bit_pos & 1)
				kill(target_pid, SIGUSR2);
			else
				kill(target_pid, SIGUSR1);
			usleep(100);
		}
	}
	bit_pos = 8;
	while (bit_pos--)
	{
		kill(target_pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int arg_count, char **args)
{
	if (arg_count != 3 || !ft_strlen(args[2]))
		return (1);
	ft_printf("envoyés: %ld\n", ft_strlen(args[2]));
	ft_printf("reçu: ");
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	send_signals(ft_atoi(args[1]), args[2]);
	while (1)
		pause();
	return (0);
}
