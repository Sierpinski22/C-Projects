#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 9

typedef struct nodet{
	int val;
	nodet* left;
	nodet* right;
}NodeT;
typedef NodeT* tree;

typedef struct nodel{
	int val;
	nodel* next;
}NodeL;
typedef NodeL* list;


list buildList(list l);
list sortList(list l);
tree auxInsert(list l, int start, int end);
tree insertInTree(list l);
void printL(list l);
int lenghtList(list l);
int get(list l, int index);

void print(tree t){
       if(t==NULL)return;       
       else{printf(" (");print(t->left);printf(" %d ",t->val);print(t->right);printf(") ");}       
}

void stampa(tree T){print(T);printf("\n");}

int main(){
	srand(time(0));
	tree t = NULL;
	list l = NULL;
	l = buildList(l);
	t = insertInTree(l);
	stampa(t);
	return 0;
}


list sortList(list l){
	if(l == NULL || l->next == NULL) return l;
	
	int done = 0;
	list now = l, nx = l->next;
	
	while(!done){
		done = 1;
		while(nx != NULL){
			if(now->val > nx->val){
				done = 0;
				int temp = now->val;
				now->val = nx->val;
				nx->val = temp;
			}
			now = nx;
			nx = nx->next;
		}
		now = l;
		nx = l->next;
	}
	return l;
}

list buildList(list l){
	l = (list) malloc(sizeof(NodeL));
	l->val = 0;
	list prox = l;
	for(int i=1; i<N; i++){
		prox->next = (list) malloc(sizeof(NodeL));
		prox->next->val = i;
		prox->next->next = NULL;
		prox = prox->next;
	}
	return l;
}

void printL(list l){
	list punt = l;
	while(punt!=NULL){
		printf("%d --> ", punt->val);
		punt = punt->next;
	}
	printf("--|\n");
}

int lenghtList(list l){
	list punt = l;
	int c = 0;
	while(punt!=NULL){
		c++;
		punt = punt->next;
	}
	return c;
}

int get(list l, int index){
	int c = 0;
	list punt = l;
	while(punt != NULL){
		if(c==index) return punt->val;
		else{
			punt = punt->next;
			c++;
		}
	}
	return -1; 
}

tree auxInsert(list l, int start, int end){
	tree t = (tree) malloc(sizeof(NodeT));
	
	if(end-start <= 1){
		t->val = get(l, start);
		t->left = NULL;
		//printf("%d", t->val);
		if(end == start) t->right = NULL;
		else{
			t->right = (tree) malloc(sizeof(NodeT));
			t->right->val = get(l, end);
			t->right->left = NULL;
			t->right->right = NULL;
			//printf("%d ", t->right->val);
		}	 
	}else{
		int half = (start + end) / 2;
		tree leftTree = auxInsert(l, start, half);
		tree rightTree = auxInsert(l, half+1, end);
		
		//cerca e distuggi
		tree punt = leftTree;
		while(punt->right->right != NULL) punt = punt->right;
		int maxLeft = punt->right->val;
		free(punt->right);
		punt->right = NULL;
		
		//merge
		t->val = maxLeft;
		t->left = leftTree;
		t->right = rightTree;
	}
	//printf("%d, %d\n", start, end);
	return t;
}

tree insertInTree(list l){
	tree t = NULL;
	l = sortList(l);
	t = auxInsert(l, 0, lenghtList(l)-1);
	return t;
}