/*
		CG-T3: SUPERFICIE BSPLINE
		JOSÉ AUGUSTO COMIOTTO ROTTINI - 201120279
		ENGENHARIA DE COMPUTACAO - UFSM

		CLASSE PARA A IMPLEMENTACAO DE TRANSFORMACOES 3D
*/

#include "Transformacao3D.h"
#include <math.h>

/* CONSTRUTOR: CARREGA A MATRIZ IDENTIDADE */
Transformacao3D::Transformacao3D() 
{
      colunas = 4;
      linhas = 4;

    for (int x=0;x<linhas;x++)
    {
        for(int y=0;y<colunas;y++)
        {
            if (x==y)
            {
                matriz[x][y] = 1;
            }
            else
            {
                matriz[x][y] = 0;
            }
        }
    }
}

Transformacao3D::~Transformacao3D()
{
    //dtor
}


/* CONCATENA UMA MATRIZ DE TRANSFORMACAO A MATRIZ PRINCIPAL ATRAVES DA MULTIPLICACAO */
void Transformacao3D::multiplica(float matriz1[4][4], float matriz2[4][4])
{
    float matrizResultante[4][4];
    float soma;
    int i = 0;

     for (int x=0;x<4;x++)
    {
        for(int y=0;y<4;y++)
        {
            matrizResultante[x][y]=0;
            for (int j=0;j<4;j++)
            {
                matrizResultante[x][y]+= matriz1[x][j] * matriz2[j][y];
            }
        }
    }
    for (int x=0;x<4;x++)
    {
        for(int y=0;y<4;y++)
        {
            matriz[x][y] = matrizResultante[x][y];
        }
    }
}


/* ROTACAO NO EIXO X */
void Transformacao3D::rotacaoX(float ang)
{
	float rad = ang*((float)3.14 / (float)180);
	float matrizRotacao[4][4] = { 1,0,0, 0,
														0,cos(rad), - sin(rad), 0, 
														0, sin(rad), cos(rad), 0, 
														0, 0, 0, 1 };

	multiplica(matriz, matrizRotacao);
}


/* ROTACAO NO EIXO Y */
void Transformacao3D::rotacaoY(float ang)
{
    float rad=ang*((float)3.14/(float)180);
    float matrizRotacao[4][4] = {cos(rad),0, sin(rad),0,
													   0,1,0,0,
													   -sin(rad),0, cos(rad),0,
													   0,0,0,1};

    multiplica(matriz, matrizRotacao);
}


/* ROTACAO NO EIXO Z */
void Transformacao3D::rotacaoZ(float ang)
{
	float rad = ang*((float)3.14 / (float)180);
	float matrizRotacao[4][4] = { cos(rad), -sin(rad), 0, 0,
		                                                sin(rad), cos(rad), 0, 0,
														0, 0, 1,0,
														0, 0, 0, 1};

	multiplica(matriz, matrizRotacao);
}


/* TRANSLACAO */
void Transformacao3D::translada(int tx, int ty, int tz)
{
    float matrizTranslacao[4][4] = {1,0,0,tx,0,1,0,ty,0,0,1,tz,0,0,0,1};

    multiplica(matriz, matrizTranslacao);
}

/* ESCALA */
void Transformacao3D::escala(int sx, int sy, int sz)
{
    float matrizEscala[4][4] = {sx,0,0,0,0,sy,0,0,0,0,sz,0,0,0,0,1};

    multiplica(matriz, matrizEscala);
}





/*void Matriz:: print()
{
    std::cout<< "\n\nMATRIZ"<<std::endl;
    for (int x=0;x<3;x++)
    {
        for(int y=0;y<3;y++)
        {
            std::cout<< matriz[x][y]<<std::endl;
        }
    }

}*/
