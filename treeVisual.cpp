#include<stdio.h>
#include<stdlib.h>
#define N 32


typedef struct nodo{
	int dato;
	nodo * left;
	nodo * right;
}Nodo;
typedef Nodo * Tree;

Tree append(Tree T, int v);
int firstVoid(Tree T, int depth);
Tree build(int v);
Tree addToTree(Tree T, int v, int depth, int maxDepth);
void showTree(Tree T, int depth, int mdepth, int maxDepth);

int maxDepth(Tree T);
void printT(Tree T);
void printLines(int n, int md);
int pow(int b, int e);

int main(){
	Tree T = NULL;
	for(int i=0; i<N; i++) T = append(T, i);
	printT(T);
	return 0;
}

//FUNZIONI DI APPEND//
Tree build(int v){
	Tree temp = (Tree) malloc(sizeof(Nodo));
	temp->dato = v;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

int firstVoid(Tree T, int depth){
	if(T==NULL) return 0;
	if(T->left == NULL || T->right == NULL) return depth+1;
	else{
		int minLeft = firstVoid(T->left, depth+1);
		int minRight = firstVoid(T->right, depth+1);
		return minLeft < minRight? minLeft: minRight;
	}	
}

Tree append(Tree T, int v){
	if(T==NULL) return build(v);
	return addToTree(T, v, 0, firstVoid(T, 0));
}

Tree addToTree(Tree T, int v, int depth, int maxDepth){
	if(depth>=maxDepth) return NULL;
	if(T->left == NULL || T->right == NULL){
		if(T->left == NULL) T->left = build(v);
		else T->right = build(v);
		return T;
	}else{
		if(addToTree(T->left, v, depth+1, maxDepth)!=NULL) return T;
		else if(addToTree(T->right, v, depth+1, maxDepth)!=NULL) return T;
		return NULL;
	}
}
//FINE FUNZIONI DI APPEND//


//Non modificare nulla da qui in poi//
const int SPACE = 1;
const int NS = 3;

int pow(int b, int e){
	int prod = 1;
	for(int i=1; i<e; i++){
		prod *= b;
	}
	return prod;
}

int maxDepth(Tree T){
	if(T==NULL) return 0;
	else{
		int maxl = maxDepth(T->left);
		int maxr = maxDepth(T->right);
		return 1 + (maxl > maxr? maxl: maxr); 
	}
}

void showTree(Tree T, int depth, int mdepth, int maxDepth){
	if(depth > mdepth) return;
	if(T == NULL){
		for(int i=0; i<NS; i++) printf("/");
		if(depth+1!=maxDepth){
				for(int j=0; j<pow(2, maxDepth-depth-1)*NS+(pow(2, maxDepth-depth-1)-1)*SPACE-1; j++) printf(" ");
				for(int j=0; j<pow(2, maxDepth-depth-1)*NS+(pow(2, maxDepth-depth-1)-1)*SPACE-1; j++) printf(" ");
			}
		for(int j=0; j<SPACE; j++) printf(" ");
	}else{
		showTree(T->left, depth+1, mdepth, maxDepth);
		showTree(T->right, depth+1, mdepth, maxDepth);
		if(depth==mdepth){
			int p = pow(2, maxDepth-depth);
			printf("%3d", T->dato);
			if(depth+1!=maxDepth){
				for(int j=0; j<pow(2, maxDepth-depth-1)*NS+(pow(2, maxDepth-depth-1)-1)*SPACE-1; j++) printf(" ");
				for(int j=0; j<pow(2, maxDepth-depth-1)*NS+(pow(2, maxDepth-depth-1)-1)*SPACE-1; j++) printf(" ");
			}
			for(int j=0; j<SPACE; j++) printf(" ");
			
		}
	}
	
}

void printLines(int n, int md){
	int p1 = pow(2, n);
	for(int i=0; i<p1; i++){
		int sp;
		if(n+1!=md){
			sp = pow(2, md-n-1)*NS+(pow(2, md-n-1)-1)*SPACE-1;
			printf("%c",218);
			for(int j=0; j<sp+1; j++) printf("%c", 196);
			printf("%c", 193);
		}else{
			printf("%c", 218);
			printf("%c", 196);
			printf("%c", 193);
		}
		
		if(n+1!=md){
			for(int j=0; j<sp+1; j++) printf("%c", 196);
			printf("%c", 191);
			if(i+1!=p1) for(int j=0; j<2*(sp)+1; j++) printf(" ");
			
		}else{
			printf("%c", 196);
			printf("%c", 191);
			printf(" ");
		}
		
		if(i+1!=p1) for(int j=0; j<2*(NS-2); j++) printf(" ");
	}
}

void printT(Tree T){
	int md = maxDepth(T);
	for(int i=0; i<md; i++){
		if(i+1!=md) for(int j=0; j<pow(2, md-i-1)*NS+(pow(2, md-i-1)-1)*SPACE-1; j++) printf(" ");
		showTree(T, 0, i, md);
		printf("\n");
		if(i+1!=md){
			if(i+2!=md) for(int j=0; j<pow(2, md-i-2)*NS+(pow(2, md-i-2)-1)*SPACE-1; j++) printf(" ");
			for(int j=0; j<NS-2; j++) printf(" ");
			printLines(i+1, md);
		}
		printf("\n");
	}
}
