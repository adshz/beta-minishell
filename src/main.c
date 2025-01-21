/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:55:46 by szhong            #+#    #+#             */
/*   Updated: 2025/01/15 16:02:46 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./shell.h"

int	g_signal = 0;

static void	validate_args(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("argv[1]", STDERR_FILENO);
		ft_putendl_fd(": Input Many Arguments Before Program", STERR_FILENO);
		exit(127);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	shell;
	int		exit_status;

	validate_args(argc, argv);
	if (init_shell(&shell, argv, envp) != SUCESS)
	{
		ft_putendl_fd("Shell Initialisation Failure", STDERR_FILENO);
		return (ERROR);
	}
	interactive_loop(&shell);
	exist_status = shell.exit_status;
	rl_clear_history();
	cleanup_shell(&shell);
	return (exit_status);
}
