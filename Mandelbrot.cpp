#include <stdio.h>
#include <math.h>
#define SIZEY 82 //82
#define SIZEX 164 //164


typedef struct{
	float re;
	float im;
}complex;

int map(int x, int m0, int m1, int min, int max){
	float p = (float)(x-m0) / (m1-m0);
	//printf("%d", (int)p);
	return round((p * (max-min) + min));
}

complex mult(complex a, complex b){
	complex prod;
	prod.re = a.re*b.re - a.im*b.im;
	prod.im = a.re*b.im + a.im*b.re; 
	return prod;
}

float mod(complex z){
	return sqrt(pow(z.re, 2) + pow(z.im, 2));
}

void reset(complex z){
	z.re = 0;
	z.im = 0;
}

int main(){
	complex z, c, op;
	float LEFT=-1.5, RIGHT=0.5, UP=1., DOWN=-1.;	
	float incx = (RIGHT - LEFT) / SIZEX, incy = (UP - DOWN) / SIZEY;
	float maxmod = 2;
	int maxiter = 20, iter;
	int black = 30, index, cmap[]={34, 35, 36, 94, 95, 96};
	
	system("cls");
	
	for(int i=0; i<SIZEY; i++){
		for(int r=0; r<SIZEX; r++){
			z.re = 0;
			z.im = 0;
			c.re = LEFT + r*incx;
			c.im = (DOWN + i*incy);
			iter = 0; 
			
			while(mod(z) < maxmod && iter < maxiter){
				op = mult(z, z);
				z.re = op.re + c.re;
				z.im = op.im + c.im;
				iter++;
			}
			
			if(iter == maxiter){
				printf("\033[0;%dm%c\033[0m", black, 219);
			} else{		
			 	//index = (int)(iter / maxiter * 6);
			 	printf("\033[0;%dm%c\033[0m", cmap[map(iter, 0, maxiter, 0, 5)], 219);
			}	
		}
		printf("\n");
	}
	return 0;
}