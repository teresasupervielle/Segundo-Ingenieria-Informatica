#include "tarjeta.hpp"
#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include <iomanip>

using namespace std;
unsigned Pedido::n_pedidos = 0;

    //Constructor Pedido
    Pedido::Pedido (Usuario_Pedido &UP, Pedido_Articulo &PA, Usuario &u, const Tarjeta &t, const Fecha &f) : num(n_pedidos + 1), tarj(&t), fech(f), tot(0) {
        if (!u.n_articulos()) throw Pedido::Vacio{&u};
        if (t.titular() != &u) throw Pedido::Impostor{&u};
        if (t.caducidad() < fech) throw Tarjeta::Caducada{t.caducidad()};
        if (!t.activa()) throw Tarjeta::Desactivada{};

        Usuario::Articulos carro {u.compra()};
        for (auto i : carro) {
            if ((unsigned int) i.first -> stock() < i.second) {
                const_cast <Usuario::Articulos&> (u.compra()).clear();
                throw Pedido::SinStock{i.first};
            }

            i.first->stock() -= i.second;
            PA.pedir (*this, *i.first, i.first->precio(), i.second);
            tot += i.first->precio() * i.second;
            u.compra (*i.first, 0);
        }
        UP.asocia(*this, u);
        n_pedidos++;
    }

    //Operador de Salida
    std::ostream& operator << (std::ostream &os, const Pedido &p) {
        os << "Núm. pedido: " << p.numero() << std::endl;
        os << std::setw(13) << "Fecha: " << p.fecha() << std::endl;

        if (p.tarjeta()->tipo() == Tarjeta::Otro) os << std::setw(13) << "Pagado con: Tipo indeterminado n.º: " << p.tarjeta()->numero() << std::endl;
        else os << std::setw(13) <<"Pagado con: " << p.tarjeta()->tipo() << " nº.: " << p.tarjeta()->numero() << std::endl;
    
        os << std::setw(13) << "Importe:: " << std::fixed << std::setprecision(2) << p.total() << " €" << std::endl;
        return os;
    }