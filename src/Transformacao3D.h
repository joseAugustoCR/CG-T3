/*
	CG-T3: SUPERFICIE BSPLINE
	JOSÉ AUGUSTO COMIOTTO ROTTINI - 201120279
	ENGENHARIA DE COMPUTACAO - UFSM

	CLASSE PARA A IMPLEMENTACAO DE TRANSFORMACOES 3D
*/

#ifndef TRANSFORMACAO3D_H
#define TRANSFORMACAO3D_H


class Transformacao3D
{
    public:
        float matriz[4][4];		// Matriz principal de transformacao
        int linhas, colunas;

		Transformacao3D();				// Construtor
		void rotacaoX(float ang);	// Rotacao no eixo X
        void rotacaoY(float ang);		// Rotacao no eixo Y
		void rotacaoZ(float ang);	// Rotacao no eixo Z
        void translada(int tx, int ty, int tz);	// Translacao
        void escala(int sx, int sy, int sz);			// Escala
		virtual ~Transformacao3D();
    protected:
    private:
        void multiplica(float matriz1[4][4], float matriz2[4][4]);	// Multiplicacao de matrizes para concatenacao
};

#endif // TRANSFORMACAO3D_H
