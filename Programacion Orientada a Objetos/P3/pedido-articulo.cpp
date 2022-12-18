#include <iomanip>
#include <utility>
#include "pedido-articulo.hpp"

using namespace std;
	
	//Operador logico
	bool OrdenaPedidos::operator () (Pedido *p1, Pedido *p2) const {return (p1->numero() < p2->numero());}
	
    //Funciones relaciones (Pedido_Articulo)
    void Pedido_Articulo::pedir (Pedido &p, Articulo &a, double pr, unsigned c) {
        PedArt[&p].insert (std::make_pair (&a, LineaPedido(pr, c)));
	    ArtPed[&a].insert (std::make_pair (&p, LineaPedido(pr, c)));
    }

    //Funciones de salida
    std::ostream& Pedido_Articulo::mostrarDetallePedidos (std::ostream &os) {
        setlocale (LC_ALL, "es_ES");
        os.imbue (std::locale(""));
        double total = 0;
        for(auto i : PedArt) {
            os << "Pedido núm. " << i.first->numero() << "\nCliente: " << i.first->tarjeta()->titular()->nombre() << "\t\t" << i.first->fecha() << std::endl << std::endl << i.second << std::endl << std::endl;
            total += i.first->total();
        }
        os << "TOTAL VENTAS\t\t" << std::fixed << std::setprecision(2) << total << " €";
        return os;
    }
    
    std::ostream& Pedido_Articulo::mostrarVentasArticulos (std::ostream &os) {
        setlocale (LC_ALL, "es_ES");
        os.imbue (std::locale(""));
        for(auto i : ArtPed) {
            os << "Ventas de [" << i.first->referencia() << "] \"" << i.first->titulo() << "\"\n" << i.second << std::endl;
        }
        return os;
    }

    //Operadores de salida
    std::ostream& operator << (std::ostream& os, const LineaPedido &lp) {
        os << fixed << setprecision(2) << lp.precio_venta() << " €" << "\t" << lp.cantidad();
	    return os;
    }

    std::ostream& operator << (std::ostream &os, const Pedido_Articulo::ItemsPedido &ip) {
        setlocale (LC_ALL, "es_ES");
        os.imbue (std::locale(""));
        double total = 0;
        os << "PVP\tCantidad\tArtículo\n==================================================================\n";
        for(auto i : ip) {
            os << i.second << "\t[" << i.first->referencia() << "] \"" << i.first->titulo() << "\"\n";
            total += (i.second.cantidad() * i.second.precio_venta());
        }
        os << "==================================================================\nTotal\t" << std::fixed << std::setprecision(2) << total << " €";
        return os;
    }

    std::ostream& operator << (std::ostream &os, const Pedido_Articulo::Pedidos &p) {
        setlocale (LC_ALL, "es_ES");
        os.imbue (std::locale(""));
        unsigned ctotal = 0;
        double total = 0;
        os << "[Pedidos: " << p.size() << "]\n==================================================================\n" << "PVP\tCantidad\tFecha de venta\n==================================================================\n";
        for(auto i : p) {
            os << i.second << "\t\t" << i.first->fecha() << std::endl;
            ctotal += i.second.cantidad();
            total += i.second.precio_venta() * i.second.cantidad();
        }
        os << "==================================================================\n" << std::fixed << std::setprecision(2) << total << " €\t" << ctotal;
        return os;
    }
