#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#define MAX 10

using namespace std;

using std::cout;
using std::cin;
using std::endl;
using std::string;

int determinante(int matriz[][MAX], int orden);
int cofactor(int matriz[][MAX], int orden, int fila, int columna);

int determinantex(int **matriz, int orden);
int cofactorx(int **matriz, int orden, int fila, int columna);

int** crearMatriz(unsigned height, unsigned width){
	
    int** array2D = 0;
    array2D = new int*[height];
    
    for (int h = 0; h < height; h++){
      		
    	cout << "|  ";
      		
    	array2D[h] = new int[width];
        
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
	    SMALL_RECT srctWindow;
		HANDLE hstdout;
		hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	
		if (!GetConsoleScreenBufferInfo(hstdout,&csbiInfo)){
	
			cout << "Error: " << GetLastError() << endl;
	
		}
		
		//cout << "Standard Information for Console Buffer" << endl << endl;
		//cout << "Size: " << csbiInfo.dwSize.X << "X by " << csbiInfo.dwSize.Y << " Y." << endl;
		//cout << "Cursor Postion: " << csbiInfo.dwCursorPosition.X << "X by " << csbiInfo.dwCursorPosition.Y << "Y." << endl;
		//cout << "Max Size: " << csbiInfo.dwMaximumWindowSize.X << "X by " << csbiInfo.dwMaximumWindowSize.Y << "Y." << endl;
		//cout << "Window Dimensions (bottom,right,top,lef): " << csbiInfo.srWindow.Bottom << " ," << csbiInfo.srWindow.Right << " ," << csbiInfo.srWindow.Top << " ," << csbiInfo.srWindow.Left << endl;
		//cout << "Window Attributed: " << csbiInfo.wAttributes << endl;	
    	
    		
    	for (int w = 0; w < width; w++){
        	
        	
        	int z = 0;
            cin >> z;
            array2D[h][w] = z;
            //cout << z << "\t";
            // fill in some initial values
        	// (filling in zeros would be more logic, but this is just for the example)
        	
        	int posx = csbiInfo.dwCursorPosition.X;
        	int posy = csbiInfo.dwCursorPosition.Y;
        	
        	HANDLE handle;      /// A HANDLE TO CONSOLE SCREEN BUFFER

			/// COORD STRUCTURE CONTAINS THE COLUMN AND ROW
			/// OF SCREEN BUFFER CHARACTER CELL
			COORD coord;
		
			coord.X = csbiInfo.dwCursorPosition.X + (4*(w+1));
			coord.Y = posy;
		
			/// RETURNS A HANDLE TO THE SPECIFIED DEVICE.
		
			handle = GetStdHandle(STD_OUTPUT_HANDLE);   /// STD_OUTPUT_HANDLE MEANS STANDARD
		                                            /// OUTPUT DEVICE(console screen buffer)
			SetConsoleCursorPosition( handle,coord );   /// SETS CURSOR POSITION IN SPECIFIED
		                                            /// CONSOLE SCREEN BUFFER
            
                
        }
        	
       	cout << "|\n";
	}
    
    return array2D;
}

int** sumarMatriz(int **matrizA, int **matrizB, int lineas, int columnas){
	
	int** array2D = 0;
    array2D = new int*[lineas];
    
	for (int h = 0; h < lineas; h++){
      		
    	array2D[h] = new int[columnas];
    		
    	for (int w = 0; w < columnas; w++){
        	
            array2D[h][w] = matrizA[h][w] + matrizB[h][w];
    
        }
        
    }
    
	return array2D;
	
}

int** restarMatriz(int **matrizA, int **matrizB, int lineas, int columnas){
	
	int** array2D = 0;
    array2D = new int*[lineas];
    
	for (int h = 0; h < lineas; h++){
      		
    	array2D[h] = new int[columnas];
    		
    	for (int w = 0; w < columnas; w++){
        	
            array2D[h][w] = matrizA[h][w] - matrizB[h][w];
    
        }
        
    }
    
	return array2D;
	
}

int** multiplicarMatrices(int **matrizA, int **matrizB, int lineasA, int columnasA, int lineasB, int columnasB){
	
	int** array2D = 0;
    array2D = new int*[lineasA];
    
	for (int h = 0; h < lineasA; h++){
      		
    	array2D[h] = new int[columnasB];
    	
    }
        
    int vA =  0, vB = 0, vRes = 0, l2 = 0;
        	
    for(int l1 = 0; l1 < lineasA; l1++){ // por cada linea de la matriz A
        		
    	for(int c2 = 0; c2 < columnasB; c2++){ // por cada columna de la matriz B
        			
    		vRes = 0;
        			
			for (int x = 0; x < lineasB; x++){ // por cada columna A y cada Linea B - comodín
					
				int vMulti = 0;
							
				vA = matrizA[l1][x];
							
				vB = matrizB[x][c2];
							
				vMulti = vA * vB;
							
				//cout << "l1: " << l1 << " c2: " << c2 << " x: " << x << "\n";
				//cout << "vA: " << vA << " vB: " << vB << " = " << vRes << "\n";
							
				vRes = vRes + vMulti;
						
			}
			
			//cout << "l1: " << l1 << " c2: " << c2 << "\n";
			//cout << "Total: " << vRes << "\n";
					
			array2D[l1][c2] = vRes;
        		
		}
        		
	}
 
	return array2D;
	
}

int cofactor(int matriz[][MAX], int orden, int fila, int columna)
{
   int submatriz[MAX][MAX];
   int n = orden - 1;
   
   int x = 0;
   int y = 0;
   for (int i = 0; i < orden; i++) {
      for (int j = 0; j < orden; j++) {
         if (i != fila && j != columna) {
            submatriz[x][y] = matriz[i][j];
            y++;
            if (y >= n) {
               x++;
               y = 0;
            }
         }
      }
   }
   
   return pow(-1.0, fila + columna) * determinante(submatriz, n);
}

int determinante(int matriz[][MAX], int orden)
{
   int det = 0.0;
   
   if (orden == 1) {
      det = matriz[0][0];
   } else {
      for (int j = 0; j < orden; j++) {
         det = det + matriz[0][j] * cofactor(matriz, orden, 0, j);
      }
   }
   
   return det;
}

int determinantex(int **matriz, int orden)
{
   int det = 0.0;
   
   if (orden == 1) {
      det = matriz[0][0];
   } else {
      for (int j = 0; j < orden; j++) {
         det = det + matriz[0][j] * cofactorx(matriz, orden, 0, j);
      }
   }
   
   return det;
}

int cofactorx(int **matriz, int orden, int fila, int columna)
{
   int submatriz[MAX][MAX];
   int n = orden - 1;
   
   int x = 0;
   int y = 0;
   for (int i = 0; i < orden; i++) {
      for (int j = 0; j < orden; j++) {
         if (i != fila && j != columna) {
            submatriz[x][y] = matriz[i][j];
            y++;
            if (y >= n) {
               x++;
               y = 0;
            }
         }
      }
   }
   
   return pow(-1.0, fila + columna) * determinante(submatriz, n);
}

int** matrizGirar(int **matriz, int orden){
	
	int** array2D = 0;
    array2D = new int*[orden];
    
	for (int h = 0; h < orden; h++){
		
    	array2D[h] = new int[orden];
    	
    	for (int w = 0; w < orden; w++){
        	
            array2D[w][h] = matriz[h][w];
    
        }
    }
	
	return array2D;
}

float** matrizAdjunta(int **matriz, int orden){
	
	float** array2D = 0;
    array2D = new float*[orden];
    
	for (int h = 0; h < orden; h++){
    	array2D[h] = new float[orden];
    }
	
	int** array2D = matrizGirar(matriz, orden);
	
	
	for (int h = 0; h < orden; h++){
	    	
			cout << "|    ";
	        for (int w = 0; w < orden; w++){
	    		cout << array2D[h][w] << "    ";
	        }
	    	cout << "|\n";
	    	
	    }
	    
	    
	
	return array2D;
}

float** matrizInversa(int **matriz,int orden, int det){
	
	float** array2D = 0;
    array2D = new float*[orden];
    
	for (int h = 0; h < orden; h++){
    	array2D[h] = new float[orden];
    }
    
    float** matrizAdj = matrizAdjunta(matriz,orden);
    
    return array2D;
	
}

float** multiplicarMatricesFloat(int **matrizA, float **matrizB, int lineasA, int columnasA, int lineasB, int columnasB){
	
	float** array2D = 0;
    array2D = new float*[lineasA];
    
	for (int h = 0; h < lineasA; h++){
      		
    	array2D[h] = new float[columnasB];
    	
    }
        
    float vA =  0, vB = 0, vRes = 0, l2 = 0;
        	
    for(int l1 = 0; l1 < lineasA; l1++){ // por cada linea de la matriz A
        		
    	for(int c2 = 0; c2 < columnasB; c2++){ // por cada columna de la matriz B
        			
    		vRes = 0;
        			
			for (int x = 0; x < lineasB; x++){ // por cada columna A y cada Linea B - comodín
					
				int vMulti = 0;
							
				vA = (float)matrizA[l1][x];
							
				vB = matrizB[x][c2];
							
				vMulti = vA * vB;
							
				//cout << "l1: " << l1 << " c2: " << c2 << " x: " << x << "\n";
				//cout << "vA: " << vA << " vB: " << vB << " = " << vRes << "\n";
							
				vRes = vRes + vMulti;
						
			}
			
			//cout << "l1: " << l1 << " c2: " << c2 << "\n";
			//cout << "Total: " << vRes << "\n";
					
			array2D[l1][c2] = vRes;
        		
		}
        		
	}
 
	return array2D;
	
}


int main(){
	Inicio:
	system("cls");
	system("color 1B");
	cout <<"Algebra Lineal"<<endl;
	cout << "\n";
	cout <<"Integrantes:"<<endl;
	cout <<"Franklin Alejandro Cabrera Velásquez - 9989-11-514"<<endl;
	cout <<"Angel Josué García Musus - 9989-21-9224"<<endl;
	cout <<"Dylan Alberto Lopez Domínguez - 9989-21-19034"<<endl;
	cout << "\n";
	
	string carnetStr,opt;
	bool status = true;
	int lineas = 0, columnas = 0, lineasA = 0, columnasA = 0, lineasB = 0, columnasB = 0;;
	
	while(status){

        cout << "Seleccione operacion de matrices a resolver:\n";
        cout << "a) Suma de dos matrices\n";
        cout << "b) Resta de dos matrices\n";
        cout << "c) Multiplicacion de dos matrices\n";
        cout << "d) División de dos matrices\n";
        cout << "e) Determinante de una matriz\n";
        cout << "\n";
        cin >> opt;
        
        if (opt == "a" || opt == "b" || opt == "c" || opt == "d" || opt == "e"){
            status = false;    
        }else{
        	system("cls");
            cout << "¡Favor de seleccionar una opción válida!\n";
            cout << "\n";
        }
        
    }
    
    if(opt=="a" || opt == "b" ){
    	
    	cout << "\n";
		cout << "Ingrese la cantidad de columnas y de lineas:\n";
		cout << "\n";
		cout << "Lineas:";
		cin >> lineas;
		cout << "Columnas:";
		cin >> columnas;
		cout << "\n";
		
		cout << "Ingrese primer matriz:\n";
		cout << "\n";
		
		int** matrizA = crearMatriz(lineas,columnas);
		
		cout << "\n";
		cout << "Ingrese segunda matriz:\n";
		cout << "\n";
		
		int** matrizB = crearMatriz(lineas,columnas);
		
		cout << "\n";
		
		cout << "Resultado:\n";
		cout << "\n";
		
		if(opt=="a"){
			
			int** matrizResultado = sumarMatriz(matrizA,matrizB,lineas,columnas);
	    	
		    for (int h = 0; h < lineas; h++){
				cout << "|    ";
		        for (int w = 0; w < columnas; w++){
		    		cout << matrizResultado[h][w] << "    ";
		            
		        }
		        cout << "|\n";
		    }
	    	
			
		}
		
		if(opt=="b"){
			
			int** matrizResultado = restarMatriz(matrizA,matrizB,lineas,columnas);
	    	
	    	for (int h = 0; h < lineas; h++){
				cout << "|    ";
	            for (int w = 0; w < columnas; w++){
	            		cout << matrizResultado[h][w] << "    ";
	                  	//printf("%i,", matrizResultado[h][w]);
	            }
	            cout << "|\n";
	    	}
	    	
		}
	
	}
	
	if(opt == "c"){
		
		cout << "\n";
		cout << "Ingrese la cantidad de columnas y de lineas de primer matriz:\n";
		cout << "\n";
		cout << "Lineas:";
		cin >> lineasA;
		cout << "Columnas:";
		cin >> columnasA;
		cout << "\n";
		
		cout << "Ingrese primer matriz:\n";
		cout << "\n";
		
		int** matrizA = crearMatriz(lineasA,columnasA);
		
		cout << "\n";
		cout << "Ingrese la cantidad de columnas y de lineas de segunda matriz:\n";
		cout << "\n";
		cout << "Lineas:";
		cin >> lineasB;
		cout << "Columnas:";
		cin >> columnasB;
		cout << "\n";
		
		cout << "\n";
		cout << "Ingrese segunda matriz:\n";
		cout << "\n";
		
		int** matrizB = crearMatriz(lineasB,columnasB);
		
		cout << "\n";
		
		if(columnasA != lineasB){
			cout << "¡¡No se puede calcular porque las columnas de la matriz A no son iguales a las lineas de la matriz B !!";
			cout << "\n";
			cout << "- Presione cualquier tecla para realizar otra operación -\n" ;
			system("pause");
			goto Inicio;
		}
		
		cout << "Resultado:\n";
		cout << "\n";
		
		int** matrizResultado = multiplicarMatrices(matrizA,matrizB,lineasA,columnasA,lineasB,columnasB);
	    
	    //cout << "Sale";
	    
	    for (int h = 0; h < lineasA; h++){
	    	
			cout << "|    ";
	        for (int w = 0; w < columnasB; w++){
	    		cout << matrizResultado[h][w] << "    ";
	        }
	    	cout << "|\n";
	    	
	    }
		
	}
	
	if (opt == "d"){
		
		cout << "\n";
		cout << "Ingrese el orden de las matrices:\n";
		cout << "\n";
		cout << "Orden:";
		cin >> lineasA;
		columnasA = lineasA;
		lineasB = lineasA;
		columnasB = columnasA;
		
		cout << "\n";
		cout << "Matrices de " << lineasA << "x" << columnasA;
		cout << "\n";
		
		cout << "Ingrese primer matriz (numerador):\n";
		cout << "\n";
		
		int** matrizA = crearMatriz(lineasA,columnasA);
		
		cout << "\n";
		cout << "Ingrese segunda matriz (denominador):\n";
		cout << "\n";
		
		int** matrizB = crearMatriz(lineasB,columnasB);
		int det = determinantex(matrizB, lineasB);
		
		if(det == 0){
			cout << "¡¡No se puede calcular porque la matriz divisor su determinante es 0 !!";
			cout << "\n";
			cout << "- Presione cualquier tecla para realizar otra operación -\n" ;
			system("pause");
			goto Inicio;
		}
		
		// Para hallar la inversa - primero hallar adjunta y dividirla por el determinante.
		float** matrizBInv = matrizInversa(matrizB,columnasB,det);
		
		cout << "\n";
		cout << "Matriz Inversa del denominador:\n";
		cout << "\n";
		
		for (int h = 0; h < lineasA; h++){
	    	
			cout << "|    ";
	        for (int w = 0; w < columnasB; w++){
	    		cout << matrizBInv[h][w] << "    ";
	        }
	    	cout << "|\n";
	    	
	    }
		
		float** matrizResultado = multiplicarMatricesFloat(matrizA,matrizBInv,lineasA,lineasA,lineasA,lineasA);
		
		cout << "\n";
		cout << "Resultado:\n";
		cout << "\n";
		
		for (int h = 0; h < lineasA; h++){
	    	
			cout << "|    ";
	        for (int w = 0; w < columnasB; w++){
	    		cout << matrizResultado[h][w] << "    ";
	        }
	    	cout << "|\n";
	    	
	    }
		
	}
	
	if (opt == "e"){
		
		cout << "\n";
		cout << "Ingrese el orden de la matriz:\n";
		cout << "\n";
		cout << "Orden:";
		cin >> lineasA;
		columnasA = lineasA;
		cout << "\n";
		cout << "Matriz de " << lineasA << "x" << columnasA;
		cout << "\n";
		cout << "Ingrese la matriz:\n";
		cout << "\n";
		
		int** matrizA = crearMatriz(lineasA,columnasA);
		
		int matrizDet = determinantex(matrizA, lineasA);
		
		cout << "\n";
		
		cout << "El determinante de la matriz es: " << matrizDet << "\n"; 
		
	}
	
	//string pause = "";
	cout << "\n";
	cout << "- Presione cualquier tecla para realizar otra operación -\n" ;
	system("pause");
	goto Inicio;
	
	return 0;
	
}



