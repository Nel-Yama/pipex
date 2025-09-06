/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:56:40 by nel-yama          #+#    #+#             */
/*   Updated: 2025/08/30 16:56:40 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	create_pipes(t_arg *arg)
{
	int	i;

	arg->fd_pipe = (int (*)[2])malloc((arg->cmd_count - 1) * sizeof(int [2]));
	if (!arg->fd_pipe)
	{
		free_and_return(arg);
		exit_error(arg, "piepex: malloc failed", -1, -1);
	}
	i = 0;
	while (i < arg->cmd_count - 1)
	{
		if (pipe(arg->fd_pipe[i]) == -1)
		{
			free_and_return(arg);
			exit_error(arg, "pipex: Failed to create pipe",
				i - 1, i - 1);
		}
		i++;
	}
}

int	create_child_process(t_arg *arg)
{
	int	i;

	create_pipes(arg);
	arg->pid = (int *)ft_calloc(arg->cmd_count, sizeof(int));
	if (!arg->pid)
		free_and_exit(arg);
	arg->pid[0] = fork();
	if (arg->pid[0] == -1)
		free_and_exit(arg);
	i = 1;
	while (i < arg->cmd_count)
	{
		if (arg->pid[i - 1] > 0)
		{
			arg->pid[i] = fork();
			if (arg->pid[i] == -1)
				free_and_exit(arg);
		}
		i++;
	}
	return (0);
}
/*
** ****************************************************************************
** FUNCTION: create_child_process
**
** PURPOSE:
**   Sequentially creates child processes for a pipeline of commands.
**   Ensures that only the parent process forks new children.
**
** LOGIC:
**   - Allocate memory for an array of PIDs (arg->pid), initialized to 0.
**   - Create pipes for inter-process communication.
**   - Fork the first child:
**       - If fork fails, exit with error.
**   - For each subsequent command (i = 1 to cmd_count-1):
**       - Only the parent process (arg->pid[i-1] > 0) forks a new child.
**       - Children do not fork further.
**       - If fork fails, exit with error.
**
** PID EXECUTION DIAGRAM (cmd_count = 3):
**
**   Parent Process (PID p0)          Child1 (PID c1)          Child2 (PID c2)
**   -------------------------------------------------------------------------
**   fork() -> c1 created                     -                           -
**   fork next only if previous pid > 0 <== only parent forks   child skip loop
**   fork() -> c2 created                     -                           -
**   parent continues or exits main loop      -                           -
**
** NOTE:
**   - arg->pid[i] stores the PID returned by fork()
**   - Children see arg->pid[i-1] == 0, so they do NOT create further children.
**   - Memory for arg->pid must be freed later.
**
** PARAMETERS:
**   t_arg *arg : structure holding cmd_count, pipes, and pid array.
**
** RETURNS:
**   int : 0 on success. Errors handled internally via exit_error().
**
** ****************************************************************************
*/
