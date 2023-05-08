#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIDE 30
#define DIM 3
#define SCALE 10
#define DIST 2
#define TOL 0.01
#define LINE 1

int N = pow(2, DIM);

void resetGrid(float g[][SIDE]){
	for(int i=0; i<SIDE; i++){
		for(int j=0; j<SIDE; j++){
			g[i][j] = 0;
		}	
	}
}

void buildPoints(float p[][DIM], int start, int lim, int depth) {//questa funzione e STATA un incubo, crea i punti iniziali del cubo ricorsivamente
  if (depth == DIM) return;
  for (int i=0; i<lim; i++) p[i+start][depth] = i < lim/2? 1: -1;
  buildPoints(p, start, lim/2, depth+1);
  buildPoints(p, lim/2+start, lim/2, depth+1);
}


float dist(float p1[], float p2[]){
	float sum = 0;
	for(int i=0; i<DIM; i++) sum += pow(p1[i]-p2[i], 2);
	return pow(sum, 0.5);
}

void matMult(float* a, int m1, int n1, float* b, int m2, int n2, float* result){
	if (m1 != n2) printf("Errore, le matrici hanno dimensioni incompatibili\n");
	for (int i=0; i<n1; i++) {
    	for (int j=0; j<m2; j++) {
      	*(result+j+i*m2) = 0;
      		for (int k=0; k<m1; k++) {
        		*(result+j+i*m2) += *(a+i*m1+k) * *(b+k*m2+j);
      		}
    	}
  	}
}


void computeProjection(float p[], float pr[]) {//proiezione dalla terza dimensione alla seconda
  //float pjr[][] = computeProjection2(p);
  float z = 1 / (DIST-p[2]);
  float projection[] = {z, 0, 0, 0, z, 0};
  matMult(projection, 3, 2, p, 1, 3, pr);
}

int scale(float a){
	return floor(a*SCALE + SIDE/2);
}


void show(float p[], float grid[][SIDE]){//proietta e disegna
	for(int i=0; i<N; i++){
		float prj1[DIM-1];
		float p1[DIM];
		for(int k=0; k<DIM; k++) p1[k] = p[i*DIM+k];
		computeProjection(p1, prj1);
		int x = scale(prj1[0]);
		int y = scale(prj1[1]);
		if(x>=0&&x<SIDE&&y>=0&&y<SIDE) grid[y][x] =  1 / (DIST-p1[2]);
		if(LINE){
			for(int j=0; j<N; j++){
				float p2[DIM];
				for(int k=0; k<DIM; k++) p2[k] = p[j*DIM+k];
				if(j!=i && abs(dist(p1, p2)-2) < TOL){
					float prj2[DIM-1];
					computeProjection(p2, prj2); 
					int x1=scale(prj2[0]), y1=scale(prj2[1]);
				
					if(x1==x && y1==y) continue; //le due proiezioni sono lo stesso punto, nessun segmento visibile può unirli!
			
					int dx = x1-x, dy = y1-y;
					int d = abs(dx)>abs(dy)? abs(dx): abs(dy);
					float incx = (float)dx / (float)d;
					float incy = (float)dy / (float)d;
					
					for(int w=1; w<d; w++){
						int offy = round(incy*w);
						int offx = round(incx*w);
						if(y+offy>=0&&y+offy<SIDE&&x+offx>=0&&x+offx<SIDE) grid[y+offy][x+offx] = 1;
					}
				}
			}
		}
	}
	
	for(int i=0; i<SIDE; i++){//stampa la griglia
		for(int j=0; j<SIDE; j++){
			if(grid[i][j]>0){
				putchar('+');
			}else{
				putchar(' ');
			}
		}
		printf("\n");
	}
}

void reshapePoints(float p[][DIM], float p1[], float b1[]){
	for(int i=0; i<N; i++){
		for(int j=0; j<DIM; j++){
			p1[i*DIM+j] = p[i][j];
			b1[i*DIM+j] = p[i][j];
		}
	}
}

void replacePoints(float p[], float b[]){
	for(int i=0; i<DIM*N; i++) p[i] = b[i];
}

float theta = 0.07;
float rho = 0.1;
float rXY[] = {cos(theta), -sin(theta), 0, sin(theta), cos(theta), 0, 0, 0, 1};
float rYZ[] = {1, 0, 0, 0, cos(rho), -sin(rho), 0, sin(rho), cos(rho)};

int main(){
	system("cls");
	float grid[SIDE][SIDE];
	float pointsBuilt[N][DIM];
	
	float pointsBuffer[N*DIM];
	float points[N*DIM];
	
	buildPoints(pointsBuilt, 0, N, 0);
	reshapePoints(pointsBuilt, points, pointsBuffer);
	replacePoints(points, pointsBuffer);
	
	int iter = 0;
	//printf("%f", round2(-0.5));
	while(1){//rotazioni successive. Sovrascrivere i punti e sopprimere il buffer?
		resetGrid(grid);
		
		matMult(points, DIM, N, rYZ, DIM, DIM, pointsBuffer);
		replacePoints(points, pointsBuffer);
		
		matMult(points, DIM, N, rXY, DIM, DIM, pointsBuffer);
		replacePoints(points, pointsBuffer);
		
		printf("\x1b[d"); //resetta la posizione del cursore! putchar rimpiazza le cose già scritte, non stampa nuova roba!
		show(points, grid);

		//iter++;
		//if(iter==8) break;
	}	
	return 0;
}