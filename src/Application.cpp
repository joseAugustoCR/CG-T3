/*
		CG-T3: SUPERFICIE BSPLINE
		JOSÉ AUGUSTO COMIOTTO ROTTINI - 201120279
		ENGENHARIA DE COMPUTACAO - UFSM

		IMPLEMENTACAO DA CLASSE DA APLICACAO:	 parametros da aplicacao, angulos iniciais e callbacks do teclado
*/

#include "Application.h"
#include "Widget.h"

// Define angulos de visualizacao inicias:
float angX = 50, angY = 0, angZ =80;

Application::Application(void) : Kernel() {
   setWindowSize(1119, 687);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("CG-TB3: Superficie B-Spline ");
}

Application::~Application(void) {
}

void Application::init(void) {
   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(1119, 687));

   addComponent(_mainPanel);

   Slider *sliderRefinamento = new Slider(scv::Point(200,612), 100, 2.f, 9.0f, 5.0f, 1);			// Slider para ajuste do refinamento da malha
   addComponent(sliderRefinamento);

   Label *labelRefinamento = new Label(scv::Point(32, 612), scv::Point(200, 625), "Refinamento da Malha: ");		// Label do slider
   addComponent(labelRefinamento);

   Canvas *canvas = new Canvas(scv::Point(4,6), scv::Point(1110, 579));										// Canvas para desenho
   addComponent(canvas);

   Button *button = new Button(scv::Point(418,611), scv::Point(550, 635), "Habilita Animacao");		
   addComponent(button);

   Label *labelInstrucoes = new Label(scv::Point(600, 612), scv::Point(750, 625), "Pressione as teclas X,Y e Z para rotacionar nos eixos. ");		// Label do slider
   addComponent(labelInstrucoes);

}

/* CALLBACKS DO TECLADO: VERIFICA TECLAS X,Y,Z PARA ROTACAO NOS EIXOS */
void Application::onKey(const scv::KeyEvent &evt) {	

	if (evt.keycode == 88){					// Se tecla X
		botaoRotacionaX = true;
	}
	else if (evt.keycode == 89){			// Se tecla Y
		botaoRotacionaY = true;
	}
	else if (evt.keycode == 90){			// Se tecla Z
		botaoRotacionaZ = true;
	}

}

void Application::onSizeChange(void) {
   _mainPanel->setSize(getWidth(), getHeight());
}
void Application::onPositionChange(void) {
}
