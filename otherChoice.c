#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 10
#define MAX 20  // word max length

typedef struct LEAF
{
	char data[MAX];
	struct LEAF* next;
}LEAF;


typedef struct NODE {
	struct LEAF* leaf;
	struct NODE* childs[N];
} NODE;


NODE* newNode();
LEAF* newLeaf(char str[MAX]);
int getIntValue(char x);
void Insert(NODE* root,char str[MAX]);
void checkDict(NODE* root);
void search(NODE* root,char str[MAX]);


int main() {
	FILE* fptr;
	char str[MAX];
	NODE* root = newNode();
	int i;
	
	fptr = fopen("dict.txt", "r");
	if (fptr == NULL){
		printf("\n Error Reading dic.txt");
		return 1;	
	}
	while (fgets(str, 20, fptr)){
		sscanf(str,"%s\n",str);
		Insert(root,str);
		printf("\n");
	}
	checkDict(root);
	fclose(fptr);
	return 0;
}
LEAF* newLeaf(char str[MAX]){
	LEAF* tmp = (LEAF*) malloc(sizeof(LEAF));
	strcpy(tmp->data,str);
	return tmp;
}
NODE* newNode() {
	NODE* tmp = (NODE*) malloc(sizeof(NODE));
	int i;
	tmp->leaf = NULL;

	for (i = 0; i < N; i++)
		tmp->childs[i] = NULL;
	
	return tmp;
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
	LEAF* leaf;
	while (str[i] != '\0' && root != NULL) {
		tmp = str[i] - '0';
		if (tmp > 9 || tmp < 0) {
			printf(" \n!*! Invalid input !");
			return;
		}
		root = root->childs[tmp];
		i++;
	}
	if (root == NULL || root->leaf == NULL) {
		printf(" \n!*! This word is not in the dict");
		return;
	}
	leaf = root->leaf;
	while (leaf != NULL ) {
		printf(" !->  %s\n",leaf->data);
		leaf = leaf->next;
	}
}


int getIntValue(char x) {
	const char* dict[N] = {"#", "1234", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	int i = 0,j;
	while (i < N) {
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
	LEAF* leaf;
	printf("Added %s as :",str);
	while (str[i] != '\0' && str[i] != 10){
		iVal = getIntValue(str[i]);
		printf("%d",iVal);
		if (!root->childs[iVal])
			root->childs[iVal] = newNode();

		root = root->childs[iVal];
		i++;
	}

	leaf = newLeaf(str);
	leaf->next = root->leaf;
	root->leaf = leaf;
}