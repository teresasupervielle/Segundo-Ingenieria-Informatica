#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include <set>
#include <map>
#include "pedido.hpp"
#include "usuario.hpp"

class Usuario;
class Pedido;

class Usuario_Pedido {
    public:
        //Definicion relaciones
        typedef std::set<Pedido*> Pedidos;
        typedef std::map<Usuario*, Pedidos> UsuarioP;
        typedef std::map<Pedido*, Usuario*> PedidoU;

        //Funciones relaciones
        void asocia(Usuario &u, Pedido &p);
        void asocia(Pedido &p, Usuario &u) {asocia (u, p);}

        //Metodos observadores
        const Pedidos& pedidos(Usuario &u) { return UP.find(&u)->second;}
        const Usuario* cliente(Pedido &p) { return PU.find(&p)->second;}

    private:
        //Atributos
        UsuarioP UP;
        PedidoU PU;
};

#endif