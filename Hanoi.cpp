#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> 

#define N 12
#define SLEEP_TIME 10

int count=0;

int dist(int n1, int n2){
	return n1 > n2 ? n1-n2 : n2-n1;
}


int pow(int base, int exp){
	int p=1;
	for(int i=0; i<exp; i++){
		p*=base;
	}
	return p;
}

void auxbuild(int col[N], int i){// costruisci un istogramma
	for(int j=0; j<N; j++){
		if(col[i]>j) printf("#");
		else if(j==0) printf("|");
		else printf(" ");
	}
	printf("  ");
}


void auxbuild2(int col[N], int i){// costruisci una torre
	
	for(int j = 0; j < (N-1)*2 + 1; j++){
		if(dist(j, N-1) < col[i]) printf("%c", 220);
		else if(j == N-1) printf("%c", 186);
		else printf(" ");
	}
	printf("  ");
}


void buildStacks(int colA[N], int colB[N], int colC[N], int tot){
	system("cls");
	for(int i=0; i<N; i++){
		printf("%3d: ", i+1);
		auxbuild2(colA, i);
		auxbuild2(colB, i);
		auxbuild2(colC, i);	
		printf("\n");		
	}
	printf("\n");
	printf("Numero di iterazioni compiute: %15d\n", count);
	printf("Numero di iterazioni totali:   %15d\n", tot);
	printf("Percentuale di completamento:  %14.2f%c\n", (float)count / (float)tot * 100, 37);
	Sleep(SLEEP_TIME);
}

void swap(int from[N], int to[N]){
	
	int id1=-1, id2=-1, j=0, k=N-1;
	while(id1<0){
		if(from[j] != 0 && id1 < 0) id1 = j;
		j++;
	}
	
	while(id2 < 0){
		if(to[k]==0) id2 = k;
		k--;
	}
	
	to[id2] = from[id1];
	from[id1] = 0;
	count++;
}

void hanoi(int n, int from[N], int to[N], int aux[N], int *a, int *b, int*c, int tot){
	if(n!=0){
		hanoi(n-1, from, aux, to, a, b, c, tot);
		swap(from, to);
		buildStacks(a, b, c, tot);
		hanoi(n-1, aux, to, from, a, b, c, tot);
	}
	
}

int main(){	
	int colA[N], colB[N], colC[N], p=pow(2, N)-1;
	for(int i=0; i<N; i++){
		colA[i] = i+1;
		colB[i] = 0;
		colC[i] = 0;
	}
	buildStacks(colA, colB, colC, p);
	hanoi(N, colA, colC, colB, colA, colB, colC, p);
}