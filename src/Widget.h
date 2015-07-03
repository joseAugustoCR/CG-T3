/*
		CG-T3: SUPERFICIE BSPLINE
		JOSÉ AUGUSTO COMIOTTO ROTTINI - 201120279
		ENGENHARIA DE COMPUTACAO - UFSM

		DEFINICAO DOS WIDGETS
*/

#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <SCV/SCV.h>
#include "Ponto3D.h"


extern Ponto3D matrizDePontos[10][10]; // Matriz de pontos inicial
// Angulos de rotacao:
extern float angX;
extern float angY;
extern float angZ;
// Variaveis para verificar pressionamento de teclas:
extern bool botaoRotacionaX;
extern bool botaoRotacionaY;
extern bool botaoRotacionaZ;


class Slider : public scv::Slider {
private:
public:
   Slider(scv::Point p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue);

   virtual void onValueChange(void);
};

class Canvas : public scv::Canvas {
public:
   Canvas(scv::Point p1, scv::Point p2);

   void animateSurface();
   std::vector<std::vector<Ponto3D> > bSplineSurface();
   std::vector<std::vector<Ponto3D> > projection(std::vector<std::vector<Ponto3D> > matrizSuperficie);
   void setAngles();
   std::vector<std::vector<Ponto3D> >  rotate3D(std::vector<std::vector<Ponto3D> > matrizSuperficie);
   std::vector<std::vector<Ponto3D> >  translate3D(std::vector<std::vector<Ponto3D> > matrizSuperficie);
   void triangulation(std::vector<std::vector<Ponto3D> > matrizSuperficie);

   virtual void render(void);
   virtual void update(void);

};



class Button : public scv::Button {
public:
   Button(scv::Point p1, scv::Point p2, std::string str);

   virtual void onMouseClick(const scv::MouseEvent &evt);
};


class Label : public scv::Label {
public:
   Label(scv::Point p1, scv::Point p2, std::string str);
};

#endif