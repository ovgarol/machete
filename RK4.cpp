#include <iostream>
#include <fstream>
#include <math.h>

#define DIM 2 // Pasa a preprocesador el número de ecuaciones simultaneas
#define PI 3.141592

using namespace std;

/*  
    i es el índice de la función
    t es el parámetro, tiempo usualmente
    x[DIM] es el vector de funciones a calcular
    Aquí se definen las funciones que calculan la pendiente a cada paso
*/
 
float dx_i(float t, float x[DIM], int i){ 

    /*  
        definición de la función a calcular 
        debe tener tantos índices como el número de ecuaciones simultáneas (DIM)
        la forma que tienen que tener es de una función que depende de x_i y t
        return f(x_i,t)
        puse unos ejemplos para que te guiés por cualquier cosa
    */
    switch(i){      
        case 0:
            return x[1]-x[0]-x[0]*x[1];
        case 1:    
            return x[0]-x[1]-2*t*x[1];
    }
}

int main(){

    // CONDICIONES INICIALES
    float x[DIM] = {2.5,2.5}; // valores  iniciales del vector x

    //  PARÁMETROS DE CÁLCULO
    float h = 0.05;// tamaño de paso
    int t_max = 60; // tiempo de cálculo máximo
    int t_min = 0; // tiempo de inicio de cálculo
    int sampling_rate = 1/h; // 30/h es mensual 

    //  PARÁMETROS DE RK4 ¡¡¡NO TOCAR!!!
    float k[4][DIM] = {0,0,0,0};    // valores correctores de RK
    float w[4] = {1,2,2,1};         // peso de cada factor de corrección
    float z[4] = {0,0.5,0.5,1};     // peso de cada iteración en la variable independinte
    float dum_x[DIM];               // vector para valuar y re-evaluar el vector x
    ofstream datos;                 // archivo de descarga de datos
    
    // NOMBRE DE ARCHIVO DE SALIDA    
    datos.open("OUTPUT.dat");    
    char DELIMITADOR[]= " ";  
    /*
        Rutina de cálculo de RK4
    */

    for(int t=t_min; t<(t_max-t_min)/h; t++){   // iteración sobre el tiempo
        for(int i=0;i<DIM;i++){         // iteración sobre las DIM funciones
            x[i] += h*(w[0]*k[0][i]+w[1]*k[1][i]+w[2]*k[2][i]+w[3]*k[3][i])/6.0;    // iterador integrador
            //if (x[i]<=0) x[i]=0; // corrección NO_NEGATIVOS. Descomentar si no se permite x<0
            dum_x[i] = x[i]; // actualizar dum_x
            }           
        if (t%sampling_rate == 0){   // para imprimir datos a intervalos conocidos de tiempo 
            datos << "\n" << t*h << DELIMITADOR;    // imprime t en archivo
            for(int i=0;i<DIM;i++) datos << x[i] << DELIMITADOR;   // imprime x[i](t) en archvo
        }
        for(int l=0;l<4;l++){           // iteracion sobre los cuatros valores de k
            for(int i=0;i<DIM;i++){k[l][i] = dx_i((t+z[l])*h, dum_x,i);}    // calculo de k
            for(int i=0;i<DIM;i++){dum_x[i] = x[i]+k[l][i]*h/w[l];}     // calculo de dum_x
        }
    }   
    
    datos.close();
    return 0;
}   

    
