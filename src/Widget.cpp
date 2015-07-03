/*
		CG-T3: SUPERFICIE BSPLINE
		JOSÉ AUGUSTO COMIOTTO ROTTINI - 201120279
		ENGENHARIA DE COMPUTACAO - UFSM

		CLASSE PARA A IMPLEMENTACAO DOS WIDGETS: widgets, principalmente funcao render do canvas
*/


#include "widget.h"
#include "Ponto3D.h"
#include "Transformacao3D.h"
#include <vector>

// Variaveis globais:
float step=0.2;				// Step para o BSpline
int M = 0, N = 0;				// Dimensao da matriz de acordo com o step
float delta = 0;				// variacao do angulo de animacao da onda senoidal

// Teclas:
bool botaoRotacionaX=false;
bool botaoRotacionaY=false;
bool botaoRotacionaZ=false;

//Botao Anima:
bool botaoAnima = false;


/* MULTIPLICA UMA MATRIZ 4X4 POR UM PONTO 3D (HOMOGENEO) */
Ponto3D multiplica(float matriz[4][4], const Ponto3D& ponto)
{
	float soma;
	float resultado[4];

	for (int x = 0; x<4; x++)
	{
		soma = 0;
		for (int y = 0; y<4; y++)
		{
			soma += (float)matriz[x][y] * ponto.ponto[y];

		}
		resultado[x] = (float)soma;
	}
	Ponto3D ponto_resultante(resultado[0], resultado[1], resultado[2]);
	return ponto_resultante;
}


/* FUNCOES DE BASE DA CURVA BSPLINE */
float basisFunction(int i, float t){
	if (i == 0){
		return (0.167f)*pow(t, 3);
	}
	else if (i == 1){
		return (0.167)*((-3 * pow(t, 3)) + (3 * pow(t, 2)) + (3 * t) + 1);
	}
	else if (i == 2){
		return (0.167)*((3 * pow(t, 3)) - (6 * pow(t, 2)) + 4);
	}
	else if (i == 3){
		return (0.167)*pow(1 - t, 3);
	}
}


/* CALCULO DO PONTO BSPLINE PARA UMA MATRIZ 4X4 */
Ponto3D bSpline(Ponto3D pontosDeControle[4][4], float t, float s)
{
	Ponto3D bspline(0, 0, 0);

	for (int i = 0; i<4; i++){
		for (int j = 0; j<4; j++){
			bspline += pontosDeControle[i][j] * basisFunction(i, s)*basisFunction(j, t);
		}
	}
	return bspline;
}


//SLIDER
Slider::Slider(scv::Point p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue) : scv::Slider(p, width, minValue, maxValue, startValue, stepValue) {
}
void Slider::onValueChange(void) {
	step = (float) 1.f/ (float)getValue();		// Ajusta step de acordo com o slider. Step entre 1/2 e 1/9
}


// CANVAS
Canvas::Canvas(scv::Point p1, scv::Point p2) : scv::Canvas(p1, p2) {
}

void Canvas::render(void) {

	clear(0, 0, 0);

	// Define tamanho da matriz resultante apos B-Spline (10x10 gera 7 matrizes de 4x4 em cada dimensao):
	M = (int)(( 1/step) + 1) * 7;
	N = (int)(( 1/step) + 1) * 7;

	// Cria matrizes:
	std::vector<std::vector<Ponto3D> > matrizSuperficie(M, std::vector<Ponto3D>(N));
	std::vector<std::vector<Ponto3D> > matrizRotacionada(M, std::vector<Ponto3D>(N));
	std::vector<std::vector<Ponto3D> > matrizTransladada(M, std::vector<Ponto3D>(N));
	std::vector<std::vector<Ponto3D> > matrizProjecao(M, std::vector<Ponto3D>(N));

	if (botaoAnima == true) // Se botao anima foi pressionado
	{
		animateSurface();
	}

	matrizSuperficie = bSplineSurface();													// Computa a Superficie
	matrizRotacionada = rotate3D(matrizSuperficie);								// Realiza as rotacoes em 3D
	matrizProjecao = projection(matrizRotacionada);								// Projecao perspectiva + ortografica
	matrizTransladada = translate3D(matrizProjecao);							// translada superficie para melhor visualizacao
	triangulation(matrizTransladada);														    // Faz a triangulacao entre os pontos resultantes

}


/* ANIMA A SUPERFICIE GERANDO ONDULACAO */
void Canvas::animateSurface(){
	// Altura eh uma funcao senoidal deslocada de acordo com a coluna
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			matrizDePontos[i][j].z = 200 / (j + 1) * sin(360 / (j  + 1) + delta);
		}
	}

	// incrementa a fase
	delta += 0.08;

	if (delta == 360)
	{
		delta = 0;
	}

}

/* CALCULA A SUPERFICIE BSPLINE */
std::vector<std::vector<Ponto3D> > Canvas::bSplineSurface(){

	// Cria matriz resultante:
	std::vector<std::vector<Ponto3D> > matrizResultante(M, std::vector<Ponto3D>(N));

	// Percorre a matriz, incrementando a linha e coluna enquanto for possivel pegar subMatrizes 4x4
	for (int i = 0; (i + 3)<10; i++){
		for (int j = 0; (j + 3)<10; j++){

			// Carrega a matriz 4x4 com inicio em i,j
			Ponto3D subMatriz[4][4];
			for (int m = 0; m<10; m++){
				for (int n = 0; n<10; n++){
					if ((m >= i && m<i + 4) && (n >= j && n<j + 4)){
						subMatriz[m - i][n - j] = matrizDePontos[m][n];
					}
				}
			}

			int linhaAtualSubMatriz = 0;
			int colunaAtualSubMatriz = 0;

			// Computa a superficie BSpline      
			for (float t = 0; t <= 1.f; t += step){
				for (float s = 0; s <= 1.f; s += step){
					Ponto3D pontoBSpline = bSpline(subMatriz, t, s);

					int linhaAtualMatrizResultante = (int)(((float)(i + 1)*((int)(1 / step) + 1)) - 1 - linhaAtualSubMatriz);   
					int colunaAtualMatrizResultante = (int)(((float)(j + 1)*((int)(1 / step) + 1)) - 1 - colunaAtualSubMatriz);

					matrizResultante[linhaAtualMatrizResultante][colunaAtualMatrizResultante] = Ponto3D(pontoBSpline.x, pontoBSpline.y, pontoBSpline.z);
					linhaAtualSubMatriz++;
				}
				colunaAtualSubMatriz++;
				linhaAtualSubMatriz = 0;
			}
		}
	}
	return matrizResultante;

}


/* REALIZA A PROJECAO PERSPECTIVA + ORTOGRAFICA */
std::vector<std::vector<Ponto3D> > Canvas::projection(std::vector<std::vector<Ponto3D> > matrizParametro){

	// Cria matriz resultante da operãcao:
	std::vector<std::vector<Ponto3D> > matrizResultante(M, std::vector<Ponto3D>(N));

	float d = -400; // distancia

	for (int l = 0; l<(M); l++)
	{
		for (int c = 0; c<(N); c++)
		{
			assert(matrizParametro[l][c].z != 0);

			// Matriz de projecao perspectiva + ortografica:
			float matrizProjecao[4][4] = {  (float)(d/matrizParametro[l][c].z), 0, 0, 0 ,
																  0, (float)(d / matrizParametro[l][c].z), 0, 0 ,
																  0, 0, 0, 0 ,
																  0, 0, 0, 1  };

			matrizResultante[l][c] = multiplica(matrizProjecao, Ponto3D(matrizParametro[l][c].x, matrizParametro[l][c].y, matrizParametro[l][c].z));

		}
	}
	return matrizResultante;
}


/* AJUSTA ANGULOS DE ACORDO COM TECLAS PRESSIONADAS (X,Y,Z) */
void Canvas::setAngles() {
	
	if (botaoRotacionaX == true){
		angX += 1;
		if (angX >= 360){
			angX = 0;
		}
		botaoRotacionaX = false;
	}
	else if (botaoRotacionaY == true){
		angY += 1;
		if (angY >= 360){
			angY = 0;
		}
		botaoRotacionaY = false;
	}
	else if (botaoRotacionaZ == true){
		angZ += 1;
		if (angZ >= 360){
			angZ = 0;
		}
		botaoRotacionaZ = false;
	}
}


/* REALIZA AS ROTACOES 3D  */
std::vector<std::vector<Ponto3D> >  Canvas::rotate3D(std::vector<std::vector<Ponto3D> > matrizSuperficie) {

	// Ajusta angulos de rotacao de acordo com teclas X,Y,Z pressionadas
	setAngles();	
	
	// Transformacoes 3D:
	Transformacao3D transformacao;
	transformacao.translada(0,0, 500);
	transformacao.rotacaoX(angX);
	transformacao.rotacaoY(angY);
	transformacao.rotacaoZ(angZ);

	// Matriz de pontos resultantes:
	std::vector<std::vector<Ponto3D> > novaMatriz(M, std::vector<Ponto3D>(N));

	// Multiplica os pontos pela matriz de transformacao:
	for (int l = 0; l<(M); l++)
	{
		for (int c = 0; c<(N); c++)
		{
			novaMatriz[l][c]  = multiplica(transformacao.matriz, Ponto3D(matrizSuperficie[l][c].x, matrizSuperficie[l][c].y, matrizSuperficie[l][c].z));
		}
	}

	return novaMatriz;
}

/* REALIZA A TRANSLACAO EM 3D  */
std::vector<std::vector<Ponto3D> >  Canvas::translate3D(std::vector<std::vector<Ponto3D> > matrizSuperficie) {

	// Transformacoes 3D:
	Transformacao3D transformacao;
	transformacao.translada(600,300, 0);

	// Matriz de pontos resultantes:
	std::vector<std::vector<Ponto3D> > novaMatriz(M, std::vector<Ponto3D>(N));

	// Multiplica os pontos pela matriz de transformacao:
	for (int l = 0; l<(M); l++)
	{
		for (int c = 0; c<(N); c++)
		{
			novaMatriz[l][c] = multiplica(transformacao.matriz, Ponto3D(matrizSuperficie[l][c].x, matrizSuperficie[l][c].y, matrizSuperficie[l][c].z));
		}
	}

	return novaMatriz;
}

/* FAZ A TRIANGULACAO ENTRE OS PONTOS */
void Canvas::triangulation(std::vector<std::vector<Ponto3D> > novaMatriz) {
	
	color(1, 1, 1);
	for (int l = 0; l<(M); l++)
	{
		for (int c = 0; c<(N); c++)
		{
		
			if ((l<(M - 1)) && (c<(N - 1))){
				linef((int)novaMatriz[l][c].x, (int)novaMatriz[l][c].y, (int)novaMatriz[l][c + 1].x, (int)novaMatriz[l][c + 1].y);		//linha horizontal
				linef((int)novaMatriz[l][c].x, (int)novaMatriz[l][c].y, (int)novaMatriz[l + 1][c].x, (int)novaMatriz[l + 1][c].y);		//linha vertical
				linef((int)novaMatriz[l][c].x, (int)novaMatriz[l][c].y, (int)novaMatriz[l + 1][c + 1].x, (int)novaMatriz[l + 1][c + 1].y); //linha diagonal
			}
			else{
				if (c == N - 1 && l<N - 1){	// Na ultima coluna, da primeira a penultima linha
					linef((int)novaMatriz[l][c].x, (int)novaMatriz[l][c].y, (int)novaMatriz[l + 1][c].x, (int)novaMatriz[l + 1][c].y); //linha vertical
				}
				if (c<N - 1 && l == M - 1){	// Na ultima linha, da primeira a penultima coluna
					linef((int)novaMatriz[l][c].x, (int)novaMatriz[l][c].y, (int)novaMatriz[l][c + 1].x, (int)novaMatriz[l][c + 1].y); //linha horizontal
				}
				if (c == N - 1 && l == M - 1) // Ponto da ultima linha e ultima coluna
				{
					linef((int)novaMatriz[l][c].x, (int)novaMatriz[l][c].y, (int)novaMatriz[l - 1][c].x, (int)novaMatriz[l - 1][c].y); //linha vertical
				}
			}

		}
	}

}


void Canvas::update(void) {
}


//Button
Button::Button(scv::Point p1, scv::Point p2, std::string str) : scv::Button(p1, p2, str) {
}
void Button::onMouseClick(const scv::MouseEvent &evt) {
	if (botaoAnima == false){
		botaoAnima = true;
		setString("Desabilita Animacao");
	}
	else{
		botaoAnima = false;
		setString("Habilita Animacao");
	}
}


//Label
Label::Label(scv::Point p1, scv::Point p2, std::string str) : scv::Label(p1, p2, str) {
}

