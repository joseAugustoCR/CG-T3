/*
CG - TRABALHO 2
JOSÉ AUGUSTO COMIOTTO ROTTINI - ENGENHARIA DE COMPUTACAO - UFSM

    Definição da classe ponto.
*/
#ifndef PONTO3D_H
#define PONTO3D_H


class Ponto3D
{

    public:
        float ponto [4];
        float x,y,z;
        Ponto3D(float x1, float y1, float z1);
        Ponto3D();
        virtual ~Ponto3D();
		Ponto3D operator+=(const Ponto3D& ponto);
		Ponto3D operator+(const Ponto3D& ponto);
		Ponto3D operator-(const Ponto3D& ponto);
		Ponto3D operator*(const Ponto3D& ponto);
		Ponto3D& operator=(const Ponto3D& ponto);
		Ponto3D operator*(float num);

    protected:
    private:
};

#endif // PONTO3D_H
