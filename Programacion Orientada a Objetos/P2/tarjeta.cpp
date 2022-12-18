#include "tarjeta.hpp"
#include <iomanip>
#include <cstring>
#include <string.h>
#include <cctype>

using namespace std;
bool luhn (const Cadena&);

    //Constructor Numero
    Numero::Numero (const Cadena &n) {
        char cad[] = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        size_t it = strcspn (n.c_str(), cad);

        if (it < n.length()) throw Incorrecto(Razon::DIGITOS);

        char *pch, *aux = new char[30];
        pch = strpbrk (const_cast<char*> (n.c_str()), "1234567890");
        int i = 0;

        while (pch != NULL){
            aux[i++] = *pch;
            pch = strpbrk(pch + 1, "1234567890");
        }

        aux[i] = '\0';
        Cadena num(aux);
        delete[] aux;

        if (num.length() > 19 || num.length() < 13) throw Incorrecto(Razon::LONGITUD);
        if (!luhn(num)) throw Incorrecto(Razon::NO_VALIDO);

        numero_ = num;
    }

    //Constructor Tarjeta
    Tarjeta::Tarjeta (const Numero &n, Usuario &u, const Fecha &fc) : numero_(n), usuario_(&u), caducidad_(fc), estado_(1), tipo_(esTipo()) {
        if( fc < Fecha()) throw Caducada(fc);
        usuario_->es_titular_de(*this);
    }
    
    //Destructor Tarjeta
    Tarjeta::~Tarjeta() {if(usuario_) usuario_->no_es_titular_de(*this);}

    //Operadores de salida
    std::ostream& operator << (std::ostream &os, const Tarjeta &t) {
        os << t.tipo() << std::endl << t.numero() << std::endl;
        int i;
        Cadena aux = t.titular()->nombre();

        for(i = 0; aux[i] != '\0'; i++) {
            if (islower(aux[i])) aux[i] = toupper(aux[i]);
        }

        os << aux << " ";
        aux = t.titular()->apellidos();

        for(i = 0; aux[i] != '\0'; i++) {
            if (islower(aux[i])) aux[i] = toupper(aux[i]);
        }

        os << aux << std::endl;
        os << "Caduca: " << std::setfill('0') << std::setw(2) << t.caducidad().mes() << "/" << std::setw(2) << (t.caducidad().anno() % 100) << std::endl;
        return os;
    }

    std::ostream& operator << (std::ostream &os, const Tarjeta::Tipo &tipo) {
        switch (tipo) {
        case Tarjeta::VISA:
            os << "VISA"; break;
        case Tarjeta::Mastercard:
            os << "Mastercard"; break;
        case Tarjeta::Maestro:
            os << "Maestro"; break;
        case Tarjeta::JCB:
            os << "JCB"; break;
        case Tarjeta::AmericanExpress:
            os << "AmericanExpress"; break;
        case Tarjeta::Otro:
            os << "Otro"; break;
        default:
            os << "Error";
        }
        return os;
    }

    //Funcion consultora
    Tarjeta::Tipo Tarjeta::esTipo() {
        int n = atoi(numero_.num().substr(0, 2).c_str());
        switch (n/10) {
            case 3:
                if (n == 34 || n == 37) return Tarjeta::AmericanExpress;
                else return Tarjeta::JCB;
                break;
            case 4:
                return Tarjeta::VISA; break;
            case 5:
                return Tarjeta::Mastercard; break;
            case 6:
                return Tarjeta::Maestro; break;
            default:
                return Tarjeta::Otro;    
        }
    }

    //Funcion auxiliar
    void eliminaChar (Cadena &c, size_t pos) {
        Cadena aux = c.substr(0, pos);

        if ((pos + 1) < c.length()) aux += Cadena(c.substr(pos + 1, c.length()));

        c = move(aux);
    }
    
    //Funciones bool
    bool operator < (const Numero &x, const Numero &y) {return strcmp(x, y) < 0;}
	bool operator < (const Tarjeta &x, const Tarjeta &y) {return x.numero() < y.numero();}
