/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:15:49 by nel-yama          #+#    #+#             */
/*   Updated: 2025/09/05 17:15:49 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exit_error(t_arg *arg, char *msg, int i0, int i1)
{
	close_fds(arg, i0, i1);
	perror(msg);
	exit(1);
}

void	print_custom_error(int fd, const char *s1, const char *s2)
{
	char	*error_msg;
	char	*tmp;
	int		msg_len;

	if (!s1 || !s2)
		return ;
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return ;
	error_msg = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!error_msg)
		return ;
	msg_len = ft_strlen(error_msg);
	write(fd, error_msg, msg_len);
	free(error_msg);
}

void	free_and_exit(t_arg *arg)
{
	if (arg->fd_pipe)
	{
		free(arg->fd_pipe);
		arg->fd_pipe = NULL;
	}
	if (arg->pid)
	{
		free(arg->pid);
		arg->pid = NULL;
	}
	if (arg->status)
	{
		free(arg->status);
		arg->status = NULL;
	}
	exit_error(arg, "pipex: fork Failed for child process",
		arg->cmd_count - 2, arg->cmd_count - 2);
}

void	free_and_return(t_arg *arg)
{
	if (arg->fd_pipe)
	{
		free(arg->fd_pipe);
		arg->fd_pipe = NULL;
	}
	if (arg->pid)
	{
		free(arg->pid);
		arg->pid = NULL;
	}
	if (arg->status)
	{
		free(arg->status);
		arg->status = NULL;
	}
}
