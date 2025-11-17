#ifndef MINI_EXECUTION_H
#define MINI_EXECUTION_H

#include <AST.h>

int     exec_ast(t_ast_node *node);

void    get_all_heredoc_content(t_ast_node *node);
int     exec_node(t_ast_node *node);

int     exec_command(t_ast_node *node);
int     exec_redirect_out(t_ast_node *node);
int     exec_redirect_in(t_ast_node *node);
int     exec_redirect_pipe(t_ast_node *node);
int     exec_heredoc(t_ast_node *node);


#endif
