/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:23:15 by nel-yama          #+#    #+#             */
/*   Updated: 2025/08/30 16:23:15 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	close_fds(t_arg *arg, int in_pipe, int out_pipe)
{
	if (arg->in_file >= 0)
		close(arg->in_file);
	if (arg->out_file >= 0)
		close(arg->out_file);
	while (in_pipe >= 0)
	{
		close(arg->fd_pipe[in_pipe][0]);
		in_pipe--;
	}
	while (out_pipe >= 0)
	{
		close(arg->fd_pipe[out_pipe][1]);
		out_pipe--;
	}
}

/**
 * Normal exit: low 7 bits = 0, Killed by signal: low 7 bits != 0
 * [ high byte (status >> 8) ] → exit code if normal exit
 * [ low 7 bits (status & 0x7F) ] → signal number if killed
 * [ bit 7 of low byte ] → core dump flag (ignored for pipex)
 * Adding 128 for signals follows shell convention (kill -9 → exit 137
**/
int	end_main(t_arg *arg)
{
	int	i;

	close_fds(arg, arg->cmd_count - 2, arg->cmd_count - 2);
	arg->status = (int *)malloc(arg->cmd_count * sizeof(int));
	if (!arg->status)
		free_and_exit(arg);
	i = 0;
	while (i < arg->cmd_count)
	{
		waitpid(arg->pid[i], &arg->status[i], 0);
		i++;
	}
	if ((arg->status[arg->cmd_count - 1] & (0x7F)) == 0)
		arg->exit_code = arg->status[arg->cmd_count - 1] >> 8;
	else
		arg->exit_code = (arg->status[arg->cmd_count - 1] & (0x7F)) + 128;
	free_and_return(arg);
	return (arg->exit_code);
}
