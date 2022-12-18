#include "usuario-pedido.hpp"

    //Funciones relaciones
    void Usuario_Pedido::asocia(Usuario &u, Pedido &p) {
        UP[&u].insert(&p); 
        PU[&p] = &u;
    }