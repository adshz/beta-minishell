/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_cmd_cleanup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:06:44 by szhong            #+#    #+#             */
/*   Updated: 2025/03/04 16:06:47 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "memory_collector/memory_collector.h"
#include "utils/utils.h"

void	extern_cleanup_resources(char *cmd_path, char **env_array)
{
	if (cmd_path)
		free(cmd_path);
	if (env_array)
		ft_free_array(env_array);
}

void	cleanup_and_exit_external(t_shell *shell, int status)
{
	cleanup_shell(shell);
	ft_heredoc_memory_collector(NULL, true);
	ft_hash_memory_collector(NULL, true);
	exit(status);
}

int	extern_handle_fork_error(char *cmd_path, char **env_array)
{
	extern_cleanup_resources(cmd_path, env_array);
	return (1);
}
