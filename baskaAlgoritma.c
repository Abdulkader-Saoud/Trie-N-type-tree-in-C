#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 10
#define MAX 20

/*
	Bu alogritma daha az yer kaplar ama daha yavas calisir.
	Bu nedenle 2. secenek olarak verdim.
*/
typedef struct NODE {
	int isEnd;
	char* data;
	int val;
	struct NODE* child;
	struct NODE* sib;
} NODE;


NODE* newNode(int val);
int getIntValue(char x);
void Insert(NODE* root,char str[MAX]);
void checkDict(NODE* root);
void search(NODE* root,char str[MAX]);
NODE* searchNODE(NODE* root,int x);

int main() {
	FILE* fptr;
	char str[MAX];
	NODE* root = newNode(0);
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
NODE* searchNODE2(NODE* root,int x){
	while (root  != NULL && root->val < x)
		root = root->sib;
	if (root != NULL && root->val != x)
		return NULL;
	return root;
}
void search(NODE* root,char str[MAX]) {
	int i = 0,tmp;
	while (str[i] != '\0' && root != NULL) {
		tmp = str[i] - '0';
		if (tmp > 9 || tmp < 0) {
			printf(" \n!*! Invalid input !");
			return;
		}
		root = searchNODE2(root->child,tmp);
		i++;
	}
	if (root == NULL || !root->isEnd) {
		printf(" \n!*! This word is not in the dict");
		return;
	}
	do {
		printf(" !->  %s\n",root->data);
		root = root->child;
	}while (root != NULL && root->val == 0);
}
NODE* newNode(int val) {
	NODE* tmp = (NODE*) malloc(sizeof(NODE));
	int i;
	tmp->isEnd = 0;
	tmp->child = NULL;
	tmp->sib = NULL;
	tmp->val = val;
	return tmp;
}

int getIntValue(char x) {
	const char* dict[N] = {"#", "1234", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	int i = 0,j;
	while (i < N) {
		j = 0;
		while (dict[i][j] != '\0') {
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
	NODE* tmp;
	printf("Added %s as : ",str);
	while (str[i] != '\0'){
		iVal = getIntValue(str[i]);
		printf("%d",iVal);
		if (iVal == -1)
			return;
		
		if (root->child == NULL){
			root->child = newNode(iVal);
			root = root->child;
		}
		else {
			root = root->child;
			if (root->val != iVal){
				root = searchNODE(root,iVal);
				if (root->sib == NULL || root->sib->val != iVal){
					tmp = root->sib;
					root->sib = newNode(iVal);
					root->sib->sib = tmp;
				}
				root = root->sib;
			}
		}
		i++;
	}
	while (root->isEnd) {
		if (root->child == NULL)
			root->child = newNode(0);	
		else if (root->child->val != 0){
			root->child = newNode(0);
			root->child->sib = tmp;
		}
		root = root->child;
	}
	root->data = strdup(str);
	root->isEnd = 1;
}
NODE* searchNODE(NODE* root,int x){
	while (root->sib  != NULL && root->sib->val < x)
		root = root->sib;
	
	return root;
}
