/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:14:40 by odessein          #+#    #+#             */
/*   Updated: 2022/07/30 21:33:50 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "libft.h"

typedef struct s_info{
	t_list	*cmd;
	t_list	*opt;
	t_list	*path_cmd;
	char	*cmd_exec;
	char	*path;
	t_bool	infile;
	t_bool	here_doc;
	t_bool	ctrld;
	t_bool	end;
	int		fd[2];
	int		tmp_fd;
	int		ind;
	char	**arg;
}		t_info;
/*********************************************/
/*					Init					 */
/*********************************************/

t_bool	pp_handle_infile_here_doc(t_info *info, char **av);
t_bool	pp_heredoc(t_info *info, char *eof);
t_bool	pp_loop_here_doc(t_info *info, int fpipe[2], char *buffer, char *eof_n);

/*********************************************/
/*					Exec					 */
/*********************************************/
t_bool	pp_loop_cmd(t_info *info, char **envp);
t_bool	pp_exec(t_info *info, char **envp, int i);
t_bool	pp_exec_out(t_info *info, char **envp, int i);
t_bool	pp_exec_middle(t_info *info, char **envp, int i);
t_bool	pp_exec_start(t_info *info, char **envp, int i);
t_bool	pp_in_exec(t_info *info, char **envp, int fd[2], char **arg);
t_bool	pp_pipe_exec(t_info *info, char **envp, int fd[2], char **arg);
t_bool	pp_out_exec(t_info *info, char **envp, int fd[2], char **arg);
char	**pp_arg_for_exec(t_info *info, int i);
t_bool	pp_loop_exec(t_info *info, char **envp);

/*********************************************/
/*					parsing					 */
/*********************************************/

t_bool	pp_parse(int ac, char **av, t_info *info);
t_bool	pp_check_file(int ac, char **av, t_info *info);
t_bool	pp_check_cmd(int ac, char **av, t_info *info);
t_bool	pp_fill_lst(t_info *info, char *arg, char **cmd, char **option);
t_bool	pp_check_path(char **path_lst, char *cmd, t_bool *valid, t_info *info);
t_bool	pp_loop_arg(int ac, char **av, char **path_lst, t_info *info);

/*********************************************/
/*					getenv					 */
/*********************************************/

char	*pp_get_path(char **envp);

/*********************************************/
/*					utils					 */
/*********************************************/

void	pp_free_things(t_info *info);
void	pp_free_and_close(int pipe_fd[2], int *pid, t_info *info);
void	pp_free_double_arr(char **arr);
t_bool	pp_waitpid(int i, int *pid, t_info *info);
void	pp_close_pipe(int pipe[2]);
void	pp_check_end(t_info *info, int pipe_fd[2]);

#endif
