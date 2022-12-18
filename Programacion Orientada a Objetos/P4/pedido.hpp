#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "usuario.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include <iostream>

class Usuario_Pedido;
class Pedido_Articulo;
class Tarjeta;

class Pedido {
    private:
        //Atributos
        static unsigned n_pedidos;
        int num;
        const Tarjeta *tarj;
        Fecha fech;
        double tot;

    public:
        //Constructor
        Pedido (Usuario_Pedido &UP, Pedido_Articulo &PA, Usuario &u, const Tarjeta &t, const Fecha &f = Fecha());

        //Metodos Observadores
        static unsigned n_total_pedidos() noexcept {return n_pedidos;}
        const int numero() const noexcept {return num;}
        const Tarjeta* tarjeta() const noexcept {return tarj;}
        const Fecha fecha() const noexcept {return fech;}
        const double total() const noexcept {return tot;}

        //Clase Vacio
        class Vacio {
            private:
                //Atributos
                Usuario *u;
            public:
                //Constructor
                Vacio (Usuario *us): u(us) {}

                //Metodo observador
                Usuario& usuario() const {return *u;}
        };

        //Clase Impostor
        class Impostor {
            private:
                //Atributos
                Usuario *u;
            public:
                //Constructor
                Impostor (Usuario *us) : u(us) {}

                //Metodo observador
                Usuario& usuario() const {return *u;}
        };

        //Clase SinStock
        class SinStock {
            private:
                //Atributos
                Articulo *a;
            public:
                //Constructor
                SinStock (Articulo *ar) : a(ar) {}

                //Metodo observador
                Articulo& articulo() const {return *a;}
        };
};

//Operador de salida
std::ostream& operator << (std::ostream &os, const Pedido &p);
#endif