#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define N 10

typedef struct NODE {
    int isEnd;
    char* data; 
    struct NODE* childs[N];
}NODE;


NODE* newNode();
int getIntValue(char x);
void Insert(NODE* root,char* str);

int main(){
    setlocale(LC_ALL, "Turkish");
    NODE* root = newNode();
    char* dict[16] = {"az", "gala", "hala", "kar", "kaz", "kaya", "kaza", "kazı", "kazan", "tek", "tel", "tela", "ter", 
    "yama", "yoga", "zona"};
    int i;
    for (i = 0; i< 16;i++){
		Insert(root,dict[i]);
    }
    return 0;
}
NODE* newNode(){
    NODE* tmp = (NODE*) malloc(sizeof(NODE));
    int i;
    tmp->isEnd = 0;

    for (i = 0; i < N; i++)
        tmp->childs[i] = NULL;
 
    return tmp;
}

int getIntValue(char x){
    const char* dict[10] = {"#", "çğüş", "abc", "def", "ghı", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int i = 0,j;
    while (i < 10){
        j = 0;
		while (dict[i][j] != '\0'){
            if (dict[i][j] == x)
                return i;
            j++;
        }
        i++;
    }
    printf("\n !*! This char is not in the Dict\n");
    return -1;
}

void Insert(NODE* root,char* str){
    int i = 0,iVal;
    while (str[i] != '\0'){
        iVal = getIntValue(str[i]);
        if (!root->childs[iVal])
            root->childs[iVal] = newNode();
        
        root = root->childs[iVal];
        i++;
    }
    while (root->isEnd){
        if (!root->childs[0])
            root->childs[0] = newNode();
        root = root->childs[0];
    }
    printf("%s\n",str);
    root->data = strdup(str);
    root->isEnd = 1;
}