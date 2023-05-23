#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M 	10000*100 //numero de muestras
#define N 	50*100	// long de ventana gaussiana
#define f 	10*100 // frecuencia de la senal
#define A	50*100 // amplitud de la senal
#define PI 	3.141*100
#define fs	10000*100 // frecuencia de muestreo
#define snr 4*100 // relacion señal-ruido en dB
#define alpha 0.4*100 // alpha para la campana gaussiana


//funcion para ejecutar convolucion entre dos senales
void convolve(int *x, int len_x, int *h, int len_h, int *y)
{
    int len_y = len_x + len_h - 1; //longitud de la conv
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
	int xsin[M] = {}; // variable para guardar la senal seno
	int noise[M] = {}; // variable para guardar el ruido
	int y[M+N-1] = {}; // variable para la senal convolucionada
	int wGauss[M] = {}; // variable para guardar la ventana gaussiana
	int snr_lin = pow(10, snr/10.0); //snr lineal 
	long noise_power = A*A/snr_lin; // potencia de la senal

	int w = (2*PI*f)/fs; // omega normalizada

	srand(time(NULL)); // semilla para ruido

	/*------- define apuntadores de archivo ----------*/ 
	FILE *fsin, *fsinN, *fgaussW, *fconv; 
		fsin = fopen("sin.dat", "w");
		fsinN = fopen("sinNoise.dat", "w");
		fgaussW = fopen("gaussWindow.dat","w");
		fconv	= fopen("conv.dat","w");

	/*------ Genera senal con IIR cuasiestable --------*/ 
	int a1,a2;
    a1 = -2*cos(w);
    a2 = 1;
    
    xsin[0] = 0; xsin[1] = sin(w);
	
	for (int n = 2; n < M; n++)
    {
        xsin[n] = -a1*xsin[n-1] - a2*xsin[n-2];
    }
	//Escalamiento en amplitud
	for (int n = 0; n < M; n++)
    {
        xsin[n] = A*xsin[n];
    }

	/*------- Genera ruido con SNR < 5dB ----------*/ 
	for (int n = 0; n < M; n++){
		noise[n] = (int)sqrt(noise_power)*((int)rand()*100 / (int)RAND_MAX*100 - 0.5*100);
    }

	// Guarda el seno y el seno con ruido sumado en archivos .dat
	for (int n = 0; n < M; n++){
        fprintf(fsin, "%f\n", xsin[n]);
		xsin[n] += noise[n];
		fprintf(fsinN, "%f\n", xsin[n]);
    }
	
	// Guarda la ventana gaussiana en archivo .dat
	for(int n=0; n<N; n++){
		wGauss[n] = exp(-0.5 * pow((n - (N-1)/2) / (alpha * (N-1)/2), 2));
		fprintf(fgaussW, "%f\n", wGauss[n]);
	}

	/* ---  Aplica la convolucion con func previamente creada  ---*/
	convolve(xsin, M, wGauss, N, y);

	// Guarda el resultado en un archivo .dat
	for (n = 0; n < N + M - 1; n++) {
        fprintf(fconv,"%f\n ", y[n]);
    }

	/*---  Cierra archivos  ---*/
	fclose(fsin);
	fclose(fsinN);
	fclose(fgaussW);
	fclose(fconv);
	
	/*Grafica con herramienta GNU-Plot*/
	system("gnuplot -p main.gp");
	
	return 0; // Fin del programa
}
