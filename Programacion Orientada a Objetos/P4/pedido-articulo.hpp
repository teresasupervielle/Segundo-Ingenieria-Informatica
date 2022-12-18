#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include <set>
#include <map>
#include <ostream>
#include "pedido.hpp"
#include "articulo.hpp"

class Pedido;
class Articulo;

class LineaPedido {
    private:
        //Atributos
        double p_venta;
        unsigned cant;
    
    public:
        //Constructor
        explicit LineaPedido (double pv, unsigned c = 1) : p_venta (pv), cant (c) {}

        //Metodos observadores
        const double precio_venta () const noexcept {return p_venta;}
        const unsigned cantidad () const noexcept {return cant;}
};

class OrdenaPedidos {
    public:
        //Operadores logicos
        bool operator () (Pedido *p1, Pedido *p2) const;
};

class OrdenaArticulos {
    public:
        //Operadores logicos
        bool operator () (Articulo *a1, Articulo *a2) const {return a1->referencia() < a2->referencia();}
};

class Pedido_Articulo {    
    public:
        //Relaciones
        typedef std::map <Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map <Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

        //Funciones relaciones
        void pedir (Pedido &p, Articulo &a, double pr, unsigned c = 1);
        void pedir (Articulo &a, Pedido &p, double pr, unsigned c = 1) {pedir (p, a, pr, c);}

        //Metodos observadores
        ItemsPedido detalle (Pedido &p) const {return PedArt.find(&p)->second;}
        Pedidos ventas (Articulo &a) const {auto i = ArtPed.find(&a); return (i != ArtPed.end()) ? i->second:Pedidos{};}

        //Funciones de salida
        std::ostream& mostrarDetallePedidos (std::ostream &os);
        std::ostream& mostrarVentasArticulos (std::ostream &os);
        
	private:
        //Atributos
        std::map<Pedido *, ItemsPedido, OrdenaPedidos> PedArt;
        std::map<Articulo *, Pedidos, OrdenaArticulos> ArtPed;
};

//Operadores de salida
std::ostream& operator << (std::ostream& os, const LineaPedido &lp);
std::ostream& operator << (std::ostream &os, const Pedido_Articulo::ItemsPedido &ip);
std::ostream& operator << (std::ostream &os, const Pedido_Articulo::Pedidos &p);

#endif
