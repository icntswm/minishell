#include "minishell.h"

void	cleaning_position_pipe(t_pos *list)
{
	t_pos *p;
	void	*save;

	p = list;
	while (p != NULL)
	{
		save = p->next;
		free(p);
		p = save;
	}
}

void	cleaning_pipe(t_pipes *list)
{
	t_pipes *p;
	void	*save1;
	void	*save2;
	t_pos	*pos_red;
	t_files *file;

	p = list;
	while (p != NULL)
	{
		save1 = p->next;
		pos_red = p->pos_outred;
		if (pos_red)
		{
			while(pos_red != NULL)
			{
				save2 = pos_red->next;
				free(pos_red);
				pos_red = save2;
			}
		}
		file = p->outfile;
		if (file)
		{
			while(file != NULL)
			{
				save2 = file->next;
				free(file->filename);
				free(file);
				file = save2;
			}
		}
		pos_red = p->pos_inred;
		if (pos_red)
		{
			while(pos_red != NULL)
			{
				save2 = pos_red->next;
				free(pos_red);
				pos_red = save2;
			}
		}
		file = p->infile;
		if (file)
		{
			while(file != NULL)
			{
				save2 = file->next;
				free(file->filename);
				free(file);
				file = save2;
			}
		}
		free(p->cmd);
		free(p);
		p = save1;
	}
}