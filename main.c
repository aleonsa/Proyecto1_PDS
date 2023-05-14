#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M 	10000 //numero de muestras
#define N 	50	// long de ventana gaussiana
#define f 	100 // frecuencia de la senal
#define A	50 // amplitud de la senal
#define PI 	3.14159265358979
#define fs	100000 // frecuencia de muestreo
#define snr 4.5 // relacion señal-ruido en dB
#define alpha 0.4


//funcion para ejecutar convolucion entre dos senales
void convolve(float *x, int len_x, float *h, int len_h, double *y)
{
    int len_y = len_x + len_h - 1;
    int i, j;

    for (i = 0; i < len_y; i++) {
        y[i] = 0;
        for (j = 0; j < len_h; j++) {
            if ((i - j) >= 0 && (i - j) < len_x) {
                y[i] += x[i - j] * h[j];
            }
        }
    }
}


int main(int argc, char *argv[]) {
	
	int m,n; 	//Indices 
	float xsin[M] = {};
	float noise[M] = {};
	double y[M+N-1] = {};
	float w[M] = {};
	float snr_lin = pow(10, snr/10.0); //snr lineal
	float noise_power = A*A/snr_lin;

	float t[M];
	float Ts = 1.0/fs; // periodo de muestreo

	srand(time(NULL)); // semilla para ruido

	FILE *fsin, *fsinN, *fgaussW, *fconv; // define apuntadores de archivo 
		fsin = fopen("sin.dat", "w");
		fsinN = fopen("sinNoise.dat", "w");
		fgaussW = fopen("gaussWindow.dat","w");
		fconv	= fopen("conv.dat","w");

	for (int n = 0; n < M; n++){
        t[n] = n*Ts;
        xsin[n] = A*sin(2.0*PI*f*t[n]);
		noise[n] = sqrt(noise_power)*((float)rand()/(float)RAND_MAX - 0.5);
    }

	for (int n = 0; n < M; n++){
        fprintf(fsin, "%f\n", xsin[n]);
		xsin[n] += noise[n];
		fprintf(fsinN, "%f\n", xsin[n]);
    }
	
	for(int n=0; n<N; n++){
		w[n] = exp(-0.5 * pow((n - (N-1)/2) / (alpha * (N-1)/2), 2));
		fprintf(fgaussW, "%f\n", w[n]);
	}

	convolve(xsin, M, w, N, y);

	for (n = 0; n < N + M - 1; n++) {
        fprintf(fconv,"%f\n ", y[n]);
    }
	
	fclose(fsin);
	fclose(fsinN);
	fclose(fgaussW);
	fclose(fconv);
	
	system("gnuplot -p graf2.gp");
	
	return 0;
}
