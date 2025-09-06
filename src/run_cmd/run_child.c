/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:48:22 by nel-yama          #+#    #+#             */
/*   Updated: 2025/08/30 17:48:22 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	run_first_child(t_arg *arg, char **envp)
{
	if (arg->in_file < 0)
	{
		close_fds(arg, arg->cmd_count - 2, arg->cmd_count - 2);
		free_and_return(arg);
		exit(1);
	}
	dup2(arg->in_file, 0);
	dup2(arg->fd_pipe[0][1], 1);
	close_fds(arg, arg->cmd_count - 2, arg->cmd_count - 2);
	run_cmd(arg, arg->av[2], envp);
	free_and_return(arg);
	exit(arg->exit_code);
}

void	run_last_child(t_arg *arg, char **envp)
{
	if (arg->out_file < 0)
	{
		close_fds(arg, arg->cmd_count - 2, arg->cmd_count - 2);
		free_and_return(arg);
		exit(1);
	}
	dup2(arg->out_file, 1);
	dup2(arg->fd_pipe[arg->cmd_count - 2][0], 0);
	close_fds(arg, arg->cmd_count - 2, arg->cmd_count - 2);
	run_cmd(arg, arg->av[arg->ac - 2], envp);
	free_and_return(arg);
	exit(arg->exit_code);
}

void	run_mid_child(t_arg *arg, char **envp, int i)
{
	dup2(arg->fd_pipe[i - 1][0], 0);
	dup2(arg->fd_pipe[i][1], 1);
	close_fds(arg, i, i);
	run_cmd(arg, arg->cmds[i], envp);
	free_and_return(arg);
	exit(arg->exit_code);
}

void	run_children(t_arg *arg, char **envp)
{
	int	i;

	if (!arg->pid[0])
		run_first_child(arg, envp);
	i = 1;
	while (i < arg->cmd_count - 1)
	{
		if (arg->pid[i - 1] && !arg->pid[i])
			run_mid_child(arg, envp, i);
		i++;
	}
	if (arg->pid[arg->cmd_count - 2] && !arg->pid[arg->cmd_count - 1])
		run_last_child(arg, envp);
}
