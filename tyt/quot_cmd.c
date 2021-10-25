#include "minishell.h"

void    quot_file(t_pipes *list, t_data *data, char redrct)
{
    t_files *q;
    char *save;

    save = NULL;
    if (redrct == '<')
        q = list->infile;
    else if (redrct == '>')
        q = list->outfile;
    while (q != NULL)
    {
        save = q->filename;
        q->filename = ft_quot(&(*data), save);
        q = q->next;
    }
}

void    handling_quotes_and_dollar(t_data *data)
{
    t_pipes *p;
    char *save;

    save = NULL;
    p = data->pipes;
    while (p != NULL)
    {
        save = p->cmd;
        p->cmd = ft_quot(&(*data), save);
        if (p->infile)
            quot_file(p, &(*data), '<');
        if (p->outfile)
            quot_file(p, &(*data), '>');
        p = p->next;
    }
}