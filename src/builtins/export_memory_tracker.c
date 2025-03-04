#include "builtins/builtins.h"

static t_list **get_export_mem_list(void)
{
    static t_list *export_mem_list = NULL;
    return (&export_mem_list);
}

char *track_export_value(char *value)
{
    t_list **export_mem_list;
    t_list *current;

    if (!value)
        return (NULL);
    export_mem_list = get_export_mem_list();
    current = *export_mem_list;
    while (current)
    {
        if (current->content == value)
            return (value);
        current = current->next;
    }
    ft_lstadd_back(export_mem_list, tracked_lstnew(value));
    return (value);
}

void cleanup_export_values(void)
{
    t_list **export_mem_list;
    t_list *current;
    t_list *next;

    export_mem_list = get_export_mem_list();
    current = *export_mem_list;
    while (current)
    {
        next = current->next;
        if (current->content)
            free(current->content);
        free(current);
        current = next;
    }
    *export_mem_list = NULL;
} 