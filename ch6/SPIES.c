#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	char* question;
	struct node *no;
	struct node *yes
} node;

int yes_no(char* question)
{
	char answer[3];
	printf("%s? (y/n): ", question);
	fgets(answer, 3, stdin);
	return answer[0] == 'y';
}

node* create(char *question)
{
	node *n = malloc(sizeof(node));
	n->question = strdup(question);
	n->no = NULL;
	n->yes = NULL;
	return n;
}

void release(node *n)
{
	if (n) {
		if (n->no)
			release(n->no);
		if (n->yes)
			release(n->yes);
		if (n->question)
			free(n->question);
		free(n);
	}
}

int main(int argc, char const *argv[])
{
	char question[80];
	char suspect[20];
	node *start_node = create("Does suspect hava a mustache");
	start_node->no = create("Loretta Barnsworth");
	start_node->yes = create("Vinny the Spoon");

	node* current;
	do {
		current = start_node;
		while (1) {
			if (yes_no(current->question))
			{
				if (current->yes) {
					current = current->yes;
				} else {
					printf("SUSPECT IDENTIFIED\n");
					break;
				}
			} else if (current->no) {
				current = current->no;
			} else {
				/* Make the yes-node the new suspect name */
				printf("Who's the suspect? ");
				fgets(suspect, 20, stdin);
				node *yes_node = create(suspect);
				current->yes = yes_node;

				/* Make the no-node a copy of this question */
				node *no_node = create(current->question);
				current->no = no_node;

				/* Then replace this question with the new question */
				printf("Give me a question that is TRUE for %s but not for %s? ", suspect, current->question);
				fgets(question, 80, stdin);
				// 堆上泄漏的数据: Loretta Barnsworth 18个字符加字符串终结符'\0'
				// free(current->question); 
				//这行导致了内存泄漏,current->question已经指向了堆上的某个question,因此在分配新的question前要先释放它 前面要加 free(current->question); 
				current->question = strdup(question);

				break;
			}
		}
	} while (yes_no("Run again"));
	release(start_node);

	return 0;
}


/*
kolya@asusn43sl ~/src/HeadFirstC/ch6
$ gcc -o spies SPIES.c && ./spies
SPIES.c:10:1: 警告：结构或联合后没有分号
 } node;
 ^
Does suspect hava a mustache? (y/n): n
Loretta Barnsworth? (y/n): n
Who's the suspect? Hayden Fantucci
Give me a question that is TRUE for Hayden Fantucci
 but not for Loretta Barnsworth? Has a facial scar
Run again? (y/n): y
Does suspect hava a mustache? (y/n): n
Has a facial scar
? (y/n): y
Hayden Fantucci
? (y/n): y
SUSPECT IDENTIFIED
Run again? (y/n): n

*/