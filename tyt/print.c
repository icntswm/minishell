# include "minishell.h"

void    list_pos_print(t_pos *list)
{
    t_pos *p;

    p = list;
    while (p != NULL)
    {
        printf("\nposition pipe: %d", p->pos);
        p = p->next;
    }
}

void    list_cmd_print(t_pipes *list)
{
    t_pipes *p;
    t_files *q;
    t_pos   *t;
    int i;

    p = list;
    while (p != NULL)
    {
        printf("---------------------------------------------------\n\n");
        printf("cmd: %s\n\n", p->cmd);
        i = 0;
        t = p->pos_outred;
        if (t)
        {
            printf("POSITION OUTFILE | > | >> | <> |\n");
            while(t != NULL)
            {
                printf("|%d|position file: %d redirect: %d\n", i, t->pos, t->redirect);
                t = t->next;
                i++;
            }
            printf("\n");
        }
        i = 0;
        q = p->outfile;
        if (q)
        {
            printf("OUTFILE | > | >> | <> |\n");
            while(q != NULL)
            {
                printf("|%d|filename: %s | redirect: %d\n", i, q->filename, q->mode);
                q = q->next;
                i++;
            }
            printf("\n");
        }
        i = 0;
        t = p->pos_inred;
        if (t)
        {
            printf("POSITION INFILE | < | << |\n");
            while(t != NULL)
            {
                printf("|%d|position file: %d redirect: %d\n", i, t->pos, t->redirect);
                t = t->next;
                i++;
            }
            printf("\n");
        }
        i = 0;
        q = p->infile;
        if (q)
        {
            printf("INFILE | < | << |\n");
            while(q != NULL)
            {
                printf("|%d|filename: %s | redirect: %d\n", i, q->filename, q->mode);
                q = q->next;
                i++;
            }
            printf("\n");
        }
        i = 0;
        if (p->cmd_argv)
        {
            printf("CMD_ARGV\n");
            while (p->cmd_argv[i])
            {
                printf("[%d]cmd_argv: %s\n", i, p->cmd_argv[i]);
                i++;
            }
        }
        p = p->next;
    }
}