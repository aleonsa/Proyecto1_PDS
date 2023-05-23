#include <stdio.h>
#include <stdlib.h>

#define shift 16 // 2^16=65536
#define unshift ((1<< shift)-1) //

#define INT2FIXED(x) ((x) << shift)
#define FLOAT2FIXED(x) ((int)((x) * (1 << shift))) 
#define FIXED2INT(x) ((x) >> shift)
#define FIXED2DOUBLE(x) (((double)(x)) / (1 << shift))
#define MULT(x, y) (((x) >> 8) * ((y)>> 8))

//-----------------------------//
//  0x0000.0000
//Se toma como acuerdo la primera mitad (16 MSB) como 
//entero, y la segunda mitad como (16 LSB) como fracción
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int suma(int a, int b);
int resta(int a, int b);
int multi(int a, int b);
int divi(int a, int b);
int entero(int a);
int fracc(int a);

int suma(int a, int b){ //SUMA A + B
	
	return (a+b)<<shift;;
}
int resta(int a, int b){ // RESTA A - B
	return (a-b)<<shift;
}
int multi(int a, int b){ // multiplica A*B
	return a*b;
}
int divi(int a, int b){ //DIVIDE A / B
	return a/b;
}
int entero(int a){ //Devuelve la parte entera
	return a>>shift;
}
int fracc(int a){ //Devuelve la parte fraccionaria
	return (a&unshift);
}

