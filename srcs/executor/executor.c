/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:15:17 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/14 13:52:22 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	ms_pipe_exec(t_node *left, t_node *right, t_minishell *ms);
int	ms_bg_exec(t_node *left, t_node *right, t_minishell *ms);
int	ms_or_exec(t_node *left, t_node *right, t_minishell *ms);
int	ms_and_operator(t_node *left, t_node *right, t_minishell *ms);
int	ms_tofile_exec(t_node *left, t_minishell *ms, char *file);
int	ms_fromfile_exec(t_node *left, t_minishell *ms, char *file);
int	ms_heredoc_exec(t_node *left, t_minishell *ms, char *file);
int	ms_append_exec(t_node *left, t_minishell *ms, char *file);

int	ft_operator_exec(t_node *node, t_minishell *ms)
{
	int	status;

	status = 0;
	if (ft_strncmp(node->op, "|", ft_strlen(node->op)) == 0)
		status = ms_pipe_exec(node->left, node->right, ms);
	else if (ft_strncmp(node->op, "||", ft_strlen(node->op)) == 0)
		status = ms_or_exec(node->left, node->right, ms);
	else if (ft_strncmp(node->op, "&", ft_strlen(node->op)) == 0)
		status = ms_bg_exec(node->left, node->right, ms);
	else if (ft_strncmp(node->op, "&&", ft_strlen(node->op)) == 0)
		status = ms_and_operator(node->left, node->right, ms);
	return (status);
}

int	ft_redirection_exec(t_node *node, t_minishell *ms)
{
	int	status;

	status = 0;
	if (ft_strncmp(node->redir[0], ">", ft_strlen(node->redir[0])) == 0)
		status = ms_tofile_exec(node->left, ms, node->redir[1]);
	else if (ft_strncmp(node->redir[0], ">>", ft_strlen(node->redir[0])) == 0)
		status = ms_append_exec(node->left, ms, node->redir[1]);
	else if (ft_strncmp(node->redir[0], "<<", ft_strlen(node->redir[0])) == 0)
		status = ms_heredoc_exec(node->left, ms, node->redir[1]);
	else if (ft_strncmp(node->redir[0], "<", ft_strlen(node->redir[0])) == 0)
		status = ms_fromfile_exec(node->left, ms, node->redir[1]);
	return (status);
}

int	ms_extern(t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(node->cmd[0], node->cmd, environ);
		exit(-1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait(&g_sgl);
		if (WIFSIGNALED(g_sgl) && WTERMSIG(g_sgl) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (WIFSIGNALED(g_sgl) && WTERMSIG(g_sgl) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		g_sgl = WEXITSTATUS(g_sgl);
		return (g_sgl);
	}
}

int	ft_commmand_exec(t_node *node, t_minishell *ms)
{
	int	status;

	status = 0;
	if (ft_strncmp(node->cmd[0], "cd", ft_strlen(node->cmd[0])) == 0)
		status = ms_cd(node, ms);
	else if (ft_strncmp(node->cmd[0], "echo", ft_strlen(node->cmd[0])) == 0)
		status = ms_echo(node);
	else if (ft_strncmp(node->cmd[0], "pwd", ft_strlen(node->cmd[0])) == 0)
		status = ms_pwd(node);
	else if (ft_strncmp(node->cmd[0], "export", ft_strlen(node->cmd[0])) == 0)
		status = ms_export(node, ms);
	else if (ft_strncmp(node->cmd[0], "exit", ft_strlen(node->cmd[0])) == 0)
		ms_exit(ms, node->cmd[1]);
	else if (ft_strncmp(node->cmd[0], "unset", ft_strlen(node->cmd[0])) == 0)
		status = ms_unset(node, ms);
	else if (ft_strncmp(node->cmd[0], "env", ft_strlen(node->cmd[0])) == 0)
		status = ms_env(ms->envs);
	else
		status = ms_extern(node);
	return (status);
}

int	ms_executor(t_node *node, t_minishell *ms)
{
	int	status;

	status = 0;
	if (node->type == COMMAND)
		status = ft_commmand_exec(node, ms);
	else if (node->type == OPERATOR)
		status = ft_operator_exec(node, ms);
	else if (node->type == REDIRECTION)
		status = ft_redirection_exec(node, ms);
	ms->exit_status = g_sgl;
	return (status);
}
