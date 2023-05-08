#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#define SIZEX 110
#define SIZEY 30
#define N 4


typedef struct{
	int x, y, vx, vy;
}ball;


int main(){
	system("cls");
	srand(time(NULL));
	
	//char toPrint[(SIZEX+1)*(SIZEY)+1] = {""};
	int intensity[7] = {30, 35, 95, 34, 94, 31, 91};
	int len = 7;
	
	int index;
	float val = 0;
	float dist = 0;
	
	float grid[SIZEY][SIZEX];
	for(int i=0; i<SIZEX*SIZEY; i++){
		grid[i/SIZEX][i%SIZEX] = 0;
	}
	
	ball b[N];
	
	for(int i=0; i<N; i++){
		b[i].x = rand() % (SIZEX-2)+1;
		b[i].y = rand() % (SIZEY-2)+1;
		if(rand()%2%2==0)b[i].vx=1;
		else b[i].vx=-1;
		if(rand()%2%2==0)b[i].vy=1;
		else b[i].vy=-1;
	}
	
	while(1){
		
		for(int i=0; i<N; i++){
	
			if(b[i].x==SIZEX-1||b[i].x==0) b[i].vx*=-1;
			if(b[i].y==SIZEY-1||b[i].y==0) b[i].vy*=-1;
			
			b[i].x += b[i].vx;
			b[i].y += b[i].vy;
			
			grid[b[i].y][b[i].x] = 1;
		}
		
		for(int y=0; y<SIZEY; y++){
			for(int x=0; x<SIZEX; x++){	
			
				val = 0;
				dist = 0;
			
				for(int i=0; i<N; i++){
					dist = sqrt((pow(b[i].x-x, 2) + pow(b[i].y-y, 2)));
					if(dist != 0){
						grid[y][x] += 1/(dist);
					}
				}				
			}
		}
		
		for(int y=0; y<SIZEY; y++){
			for(int x=0; x<SIZEX; x++){	
			 		index = (int)((0.8*grid[y][x])*9);
			 		if(index >= len) index=len-1;
			 		printf("\033[0;%dm%c\033[0m", intensity[index], 219);
			 		/*char perdio[2] = {intensity[index], '\0'};
					strcat(toPrint, perdio);*/
			 		grid[y][x] = 0;
			}
			//strcat(toPrint, "\n");
			printf("\n");
		}
		
			
		//printf(toPrint);
		Sleep(100);
		//strcpy(toPrint, "");
		system("cls");
	}
	return 0;
}
