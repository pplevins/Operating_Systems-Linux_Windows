#include <stdio.h>
#include <stdlib.h>

struct node
{
	int val;
	struct node* next;
};

int main(int argc, char* argv[])
{
	struct node* head = NULL;
	struct node* curr = NULL;
	FILE* p_file;
	int size, x, i, status, n;;
	size = atoi(argv[1]);
	if (argc != 2)
	{
		printf("Please run with parameter of input size, i.e. project.exe 4");
		return 1;
	}
	status = sscanf(argv[1], "%d", &n);        /* attempt conversion */
	if (status != 1)
	{
		printf("ERROR");
		return 1;
	}
	/*if (isdigit(argv[1]))
	{
		printf("ERROR");
		return 1;
	}*/
	if (size <= 0)
	{
	/*	printf("Please run with parameter of input size greater than 0, i.e. project.exe 4");*/
	    printf("ERROR");
		return 1;
	}
	
	p_file = fopen("main.txt", "w");
	// if p_file is null pointer, file open failed
	if (p_file == NULL)
	{
		printf("File does not exist!");
		return 1;
	}
	i = 1;
	while(i < size + 1)
	{
		curr = (struct node*)malloc(sizeof(struct node));
		printf("Enter number %d\n", i);
		fprintf(p_file, "Enter number %d\n", i);
		scanf("%d", &x);
		curr->val = x;
		curr->next = head;
		head = curr;
		++i;
	}

	printf("List of numbers\n");
	fprintf(p_file, "List of numbers\n");
	while (size > 0)
	{
		printf("%d ", head->val);
		fprintf(p_file, "%d ", head->val);
		curr = head;
		head = head->next;
		if(curr != NULL)
			free(curr);
		--size;
	}
	fclose(p_file);

	return 0;
}