#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

#include <unistd.h>
#include <cstdlib>
#include <string.h>
#include <random>
#include <iomanip>
#include <set>

using namespace std;
std::unordered_set<Cadena> Usuario::registrados;

    //Constructor Clave
    Clave::Clave (const char *p) {
        setlocale (LC_ALL, "");

        if (strlen(p) < 5) throw Clave::Incorrecta (Clave::CORTA);

        random_device r;
        uniform_int_distribution <size_t> dist(0, 63);
        char cad[] = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char salt[2] = {cad[dist(r)], cad[dist(r)]};

        if (crypt (p, salt) == nullptr) throw Clave::Incorrecta (Clave::ERROR_CRYPT);
        pass_ = crypt (p, salt);
    }
    
    //Funciones Clave
	bool Clave::verifica(const char *c) const {
		char *p = crypt (c, pass_.c_str()); 
		
		if (p == nullptr) throw Clave::Incorrecta(ERROR_CRYPT);
		return p == pass_;
	}

    //Constructor Usuario
    Usuario::Usuario (const Cadena &id, const Cadena &n, const Cadena &a, const Cadena &dir, const Clave &p) :
    ID(id), nombre_(n), apellido_(a), direccion_(dir), pass(p), n_articulos_(articulos_.size()){
        if (!registrados.insert(ID).second) throw Id_duplicado(ID);
    }

	//Destructor Usuario
	Usuario::~Usuario () { for (auto &i:tarjetas_) i.second->anula_titular(); registrados.erase(ID);}
	
    //Funcion Usuario
    void Usuario::es_titular_de (const Tarjeta &t) {if (t.titular() == this) tarjetas_[t.numero()] = const_cast <Tarjeta*> (&t);} 
    
    void Usuario::no_es_titular_de (Tarjeta &t) {tarjetas_.erase(t.numero());}
    
    void Usuario::compra (const Articulo &a, size_t cant) {
        Usuario::Articulos::const_iterator got = articulos_.find (const_cast <Articulo*> (&a));
        if (got == articulos_.end()) {
            if (cant > 0) {
                articulos_[const_cast <Articulo*> (&a)] = cant;
                n_articulos_++;
            }
        } else {
            if (cant > 0) articulos_[const_cast <Articulo*> (&a)] = cant;
            else {
                articulos_.erase (const_cast <Articulo*> (&a));
                n_articulos_--;
            }
        }
    }

    //Operadores de salida
    std::ostream& operator << (std::ostream& os, const Usuario& u) noexcept {
        setlocale (LC_ALL,"");
        os << u.ID << "[" << u.pass.clave() << "]" << u.nombre_ << " " << u.apellido_ << endl;
        os << u.direccion_ << endl;
        os << "Tarjetas:\n";
	
        for (auto &t : u.tarjetas_)
            os << *t.second << endl;

        return os;	
    }

    void mostrar_carro(std::ostream& os, const Usuario& u) noexcept{
    
        os << "Carrito de compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]" << std::endl;
        os << " Cant.  Artículo" << std::endl;
        os << "===========================================================" << std::endl;

        for (auto &iIndice : u.compra()){
            os << "  " << iIndice.second << "\t" << "[" << iIndice.first->referencia() << "] \"" << iIndice.first->titulo() << "\", ";
            os << iIndice.first->f_publi().anno() << ". " << std::setprecision(2) << std::fixed << iIndice.first->precio() << " €" << std::endl;
        }
    }
