/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:33:42 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/16 02:26:16 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <AST.h>
# include <map.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_cmd_exec
{
	t_ast_node			*cmd;
	t_map_str_str		**env;
	int					*status;
	int					input_fd;
	int					output_fd;
	pid_t				*pids;
	t_ast_node			**cmds;
}						t_cmd_exec;

typedef struct s_pipeline
{
	t_ast_node			**cmds;
	int					count;
	t_map_str_str		**env;
	int					*status;
}						t_pipeline;

typedef struct s_fd_info
{
	int					*input_fd;
	int					*fd;
	int					i;
	int					count;
}						t_fd_info;

typedef struct s_list_str
{
	char				*str;
	struct s_list_str	*next;
}						t_list_str;

typedef struct s_exe_redir_var_list
{
	int					count;
	pid_t				pid;
	int					wstatus;
}						t_exe_redir_var_list;

typedef struct s_create_dup2_var_list
{
	t_ast_node			**redirs;
	int					*fds;
	int					count;
	t_ast_node			*curr;
}						t_create_dup2_var_list;

typedef struct s_io_fd
{
	int					input_fd;
	int					output_fd;
}						t_io_fd;

int						exec_ast(t_ast_node *node, t_map_str_str **env,
							t_global_vars *vars, int *status);

void					get_all_heredoc_content(t_ast_node *node);
int						exec_node(t_ast_node *node, t_map_str_str **env,
							t_global_vars *vars, int *status);

int						exec_command(t_ast_node *node, t_map_str_str **env,
							t_global_vars *vars, int *last_exit);

int						exec_redirect_out(t_ast_node *node);
int						exec_redirect_in(t_ast_node *node, t_map_str_str **env,
							t_global_vars *vars, int *status);

int						exec_redirect_pipe(t_ast_node *node);
int						exec_heredoc(t_ast_node *node, t_map_str_str **env,
							t_global_vars *vars, int *exit_status);

int						get_exit_status(int status);
int						is_builtin(const char *cmd);
pid_t					safe_fork(void);

void					setup_pipe_fds(int *fd, int *output_fd, int i,
							int count);
int						count_pipeline(t_ast_node *node);
void					collect_commands(t_ast_node *node, t_ast_node **cmds,
							int *idx);
int						exec_command_in_pipeline(t_cmd_exec *data,
							t_global_vars *vars);
void					close_and_update_fd(t_fd_info *info);
int						wait_all_processes(pid_t *pids, int count);
int						execute_commands_loop(t_pipeline *pipeline, pid_t *pids,
							t_global_vars *vars, t_ast_node **cmds);
int						exec_pipeline_commands(t_pipeline *pipeline,
							t_global_vars *vars, t_ast_node **cmds);
int						safe_open(enum e_node_type type, char *filename);
int						exec_redirect(t_ast_node *node, t_map_str_str **env,
							t_global_vars *vars, int *status);
int						exec_pipe(t_ast_node *node, t_map_str_str **env,
							t_global_vars *vars, int *status);
char					*get_heredoc_content(char *delimiter);
int						filter_empty_args(char **args);
char					*find_cmd_path(t_map_str_str *map, char *prog);
void					exe_redir_types(t_ast_node *redirs[1024], int i,
							int *error, int *fds);

// BUILT INS
int						run_builtin(t_ast_node *node, t_map_str_str **env,
							t_global_vars *vars, int *exit_stauts);
int						builtin_export(t_ast_node *node, t_map_str_str **env);
int						builtin_env(t_ast_node *node, t_map_str_str *env);
int						builtin_unset(t_ast_node *node, t_map_str_str **env);
int						builtin_pwd(t_map_str_str **env, t_global_vars *vars);
int						builtin_cd(t_ast_node *node, t_map_str_str **env,
							t_global_vars *vars);
int						builtin_exit(t_ast_node *node, t_map_str_str **env,
							t_global_vars *vars, int *exit_status);
int						builtin_echo(t_ast_node *node, t_map_str_str *env);
void					cleanup_and_exit(t_global_vars *vars,
							t_map_str_str **env, int exit_code);
void					find_path_and_exec(t_ast_node *node,
							t_global_vars *vars, t_map_str_str **env);
void					check_is_error(t_ast_node *node, t_global_vars *vars,
							t_map_str_str **env);
void					check_not_exec(t_ast_node *node, t_global_vars *vars,
							t_map_str_str **env);
#endif
