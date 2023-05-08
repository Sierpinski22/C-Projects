#include <stdio.h>

int main(){
	int n, SIZE=3;
	printf("Inserire numero di iterazioni: ");
	scanf("%d", &n);
	for(int i=1; i<n; i++)
		SIZE*=3;
	
	char empty[3] = "  ", filled[3] = "[]";
	int mat[SIZE][SIZE], side=SIZE;
	
	for(int y=0; y<SIZE; y++){
		for(int x=0; x<SIZE; x++){
				mat[y][x] = 0;
		}
	}
	
	
	while(side/3!=0){
		side /= 3;
		for(int y=0; y<SIZE; y++){
			for(int x=0; x<SIZE; x++){
				if((y/side)%3==1 && (x/side)%3==1){
					mat[y][x]=1;
				}
			}
		}
	}
	
	for(int y=0; y<SIZE; y++){
		for(int x=0; x<SIZE; x++){
			if(mat[y][x]) printf("%s", filled);
			else printf("%s", empty);
		}
		printf("\n");
	}
}
