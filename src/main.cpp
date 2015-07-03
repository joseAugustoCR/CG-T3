/*
		CG-T3: SUPERFICIE BSPLINE
		JOSÉ AUGUSTO COMIOTTO ROTTINI - 201120279
		ENGENHARIA DE COMPUTACAO - UFSM

		REQUISITOS MÍNIMOS: TODOS
			- Malha triangular usando B-Spline, com coordenada z de valor aleatório.
			- Controle do refinamento da malha através do slider.
			- Rotação nos eixos X,Y,Z.
			- Câmera perspectiva.
			

		EXTRAS:
			- Uso de matrizes de transformação.
			- Animação da malha para gerar ondas.




		CLASSE PARA INICIALIZAÇÃO DA APLICAÇÃO: inicia aplicação e matriz de pontos iniciais.
*/


#include <SCV/SCV.h>
#include "Application.h"
#include "Ponto3D.h"
#include "Widget.h"
#include <time.h>
#include <cstdlib>

// Matriz de pontos iniciais
Ponto3D matrizDePontos[10][10];


int main(int argc, char* argv[]) {
   Application *kernel = new Application();
   scv::Kernel::setInstance(kernel);

   // Inicializa a matriz de pontos iniciais centrada na origem:
   srand(time(NULL));
   for (int i = 0; i<10; i++){
	   for (int j = 0; j<10; j++){
		   matrizDePontos[i][j].x = (j * 60) - 270;
		   matrizDePontos[i][j].y = (i * 60) - 270;
		   matrizDePontos[i][j].z = (rand() % 200) -100;
	   }
   }

   kernel->init();
   kernel->run();


   return 0;
}
