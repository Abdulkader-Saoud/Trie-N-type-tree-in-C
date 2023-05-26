#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define N 10
#define MAX 20

typedef struct NODE {
	int isEnd;
	char* data;
	struct NODE* childs[N];
} NODE;


NODE* newNode();
int getIntValue(char x);
void Insert(NODE* root,char str[MAX]);
void checkDict(NODE* root);
void search(NODE* root,char str[MAX]);


int main() {
	FILE* fptr;
	char str[MAX];
	NODE* root = newNode();
	setlocale(LC_ALL, "turkish");
	int i;
	
	
	fptr = fopen("dict.txt", "r");
	if (fptr == NULL){
		printf("\n Error Reading dic.txt");
		return 1;	
	}
	while (fgets(str, 20, fptr)){
		Insert(root,str);
	}
	checkDict(root);
	fclose(fptr);
	return 0;
}

void checkDict(NODE* root) {
	char str[MAX];
	printf("\n To leave enter q:");
	printf("\n Enter the number :");
	scanf("%s",str);
	while (strcmp(str,"q") != 0) {
		search(root,str);
		printf("\n Enter the number :");
		scanf("%s",str);
	}
}
void search(NODE* root,char str[MAX]) {
	int i = 0,tmp;
	while (str[i] != '\0' && root != NULL) {
		tmp = str[i] - '0';
		if (tmp > 9 || tmp < 0) {
			printf(" \n!*! Invalid input !");
			return;
		}
		root = root->childs[tmp];
		i++;
	}
	if (root == NULL || !root->isEnd) {
		printf(" \n!*! This word is not in the dict");
		return;
	}
	while (root != NULL && root->isEnd ) {
		printf(" !->  %s\n",root->data);
		root = root->childs[0];
	}
}
NODE* newNode() {
	NODE* tmp = (NODE*) malloc(sizeof(NODE));
	int i;
	tmp->isEnd = 0;

	for (i = 0; i < N; i++)
		tmp->childs[i] = NULL;

	return tmp;
}

int getIntValue(char x) {
	const char* dict[10] = {"#", "çğüş", "abc", "def", "ghı", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	int i = 0,j;
	while (i < 10) {
		j = 0;
		while (dict[i][j] != '\0' ) {
			if (dict[i][j] == x)
				return i;
			j++;
		}
		i++;
	}

	printf("\n !*! This char is not in the Dict");
	return -1;
}

void Insert(NODE* root,char str[MAX]) {
	int i = 0,iVal;
	printf("\nAdded %s as :",str);
	while (str[i] != '\0' && str[i] != 10){
		iVal = getIntValue(str[i]);
		printf("%d",iVal);
		if (!root->childs[iVal])
			root->childs[iVal] = newNode();

		root = root->childs[iVal];
		i++;
	}
	while (root->isEnd) {
		if (!root->childs[0])
			root->childs[0] = newNode();
		root = root->childs[0];
	}
	root->data = strdup(str);
	root->isEnd = 1;
}