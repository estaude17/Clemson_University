/*Elizabeth Stauder (estaude)
04/20/15
CPSC 1020-001
prototypes for rayfuns.c
rayfuns.h */


/* return the index of the target string in the   */
/* table of string pointers. return -1 on failure */
int getndx(char *idtab[], int  count, char *target);


/* int count is the number of attributes */
/* char *target is the candidate attribute name */
int getndxp(pparm_t *parsetab, int count, char *target);