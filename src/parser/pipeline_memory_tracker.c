#include "parser/parser.h"

static t_list **get_pipeline_mem_list(void)
{
    static t_list *pipeline_mem_list = NULL;
    return (&pipeline_mem_list);
}

t_ast_node *track_pipeline_node(t_ast_node *node)
{
    t_list **pipeline_mem_list;
    t_list *current;

    if (!node)
        return (NULL);
    pipeline_mem_list = get_pipeline_mem_list();
    current = *pipeline_mem_list;
    while (current)
    {
        if (current->content == node)
            return (node);
        current = current->next;
    }
    ft_lstadd_back(pipeline_mem_list, ft_lstnew(node));
    return (node);
}

void cleanup_pipeline_nodes(void)
{
    t_list **pipeline_mem_list;
    t_list *current;
    t_list *next;

    pipeline_mem_list = get_pipeline_mem_list();
    current = *pipeline_mem_list;
    while (current)
    {
        next = current->next;
        if (current->content)
            free_ast(current->content);
        free(current);
        current = next;
    }
    *pipeline_mem_list = NULL;
} 