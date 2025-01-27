/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:16:12 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 16:41:18 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include "core.h"
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

int	g_signal;

static void	disable_ctrl_char_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~RCHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	handle_sigint(int signum)
{
	g_signal = signum;
	write(STDOUT_FILENO, "\n", 1);
	if (isatty(STDIN_FILENO))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	struct sigaction	sa;

	g_signal = 0;
	disable_ctrl_char_echo();
	sa.sa_handler = handle_signit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
