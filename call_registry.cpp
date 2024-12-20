#include "call_registry.hpp"

/*----------------------< MÈTODES PRIVATS >-----------------------*/
// Cost: θ(1)
nat call_registry::altura(node *n) {
// Pre: cert
// Post: retorna l'altura del node n
    nat aux;
    if (n == nullptr)
        aux = 0;
    else 
        aux = n->_altura;
    return aux;
}

// Cost: θ(1)
int call_registry::factor_equilibri(node *n) {
// Pre: Cert
// Post: retorna el factor d'equilibri del node n
    int aux;
    if (n == nullptr)
        aux = 0;
    else 
        aux = altura(n->_esq) - altura(n->_dret);
    
    return aux;
}

// Cost: θ(log (n))
call_registry::node* call_registry::busca(node *n, nat num) {
// Pre: l'arbre amb arrel n conté el número num
// Post: retorna un punter al node on es troba el número num
    while (n != nullptr && num != n->_ph.numero()) {
        if (num < n->_ph.numero())
            n = n->_esq;
        else
            n = n->_dret;
    }
    return n;
}

// Cost: θ(n)
void call_registry::rec_inordre(node *n, vector<phone>& V) {
// Pre: el vector V és buit
// Post: el vector V conté totes les entrades phone de l'arbre
//       amb arrel n que no tenen un nom nul
    if (n != nullptr) {
        rec_inordre(n->_esq, V);
        if (n->_ph.nom() != "")
            V.push_back(n->_ph);
        rec_inordre(n->_dret, V);
    }
}

// Mètodes privats per la constructora i destructora

// Cost: θ(n)
call_registry::node* call_registry::copia_arbre(node *n) {
// Pre: Cert
// Post: retorna un punter que apunta a l'arrel de l'arbr AVL
//       que és còpia de l'arbre AVL amb arrel n
    node *aux(nullptr);
    if (n != nullptr) {
        aux = new node;
        try {
            aux->_ph = n->_ph;
            aux->_altura = n->_altura;
            aux->_esq = copia_arbre(n->_esq);
            aux->_dret = copia_arbre(n->_dret);
        } catch (...) {
            delete aux;
            throw;
        }
    }
    return aux;
}

// Cost: θ(n)
void call_registry::esborra_arbre(node *n) {
// Pre: Cert
// Post: Allibera espai de la memòria de l'arbre AVL apuntat per n. 
//       Si n es null, no realitza cap acció
    if (n != nullptr) {
        esborra_arbre(n->_esq);
        esborra_arbre(n->_dret);
        delete n;
    }
}

// Metodes privats per inserir i eliminar un número a l'AVL

// Cost: θ(1)
call_registry::node* call_registry::rotacio_esquerra(node *n) {
// Pre: cert
// Post: retorna el node pare de l'arbre AVL després de realitzar
//       una rotació cap a l'esquerra del node pare n inicial
    if (n != nullptr) {
        node *nova_n = n->_dret;
        node *aux(nullptr);
        if (nova_n != nullptr)
            aux = nova_n->_esq;

        // Intercanvi de nodes
        if (nova_n != nullptr)
            nova_n->_esq = n;
        n->_dret = aux;

        // S'actualitzen les altures
        n->_altura = max(altura(n->_esq), altura(n->_dret)) + 1;
        if (nova_n != nullptr)
            nova_n->_altura = max(altura(nova_n->_esq), altura(nova_n->_dret)) + 1;
        n = nova_n;
    }

    return n;
}

// Cost: θ(1)
call_registry::node* call_registry::rotacio_dreta(node *n) {
// Pre: cert
// Post: retorna el node pare de l'arbre AVL després de realitzar
//       una rotació cap a la dreta del node pare n inicial
    if (n != nullptr) {
        node *nova_n = n->_esq;
        node *aux (nullptr);
        if (nova_n != nullptr)
            aux = nova_n->_dret;

        // Intercanvi de nodes
        if (nova_n != nullptr)
            nova_n->_dret = n;
        n->_esq = aux;

        // S'actualitzen les altures
        n->_altura = max(altura(n->_esq), altura(n->_dret)) + 1;
        if (nova_n != nullptr)
            nova_n->_altura = max(altura(nova_n->_esq), altura(nova_n->_dret)) + 1;
        n = nova_n;
    }

    return n;
}

// Cost: θ(log (n))
call_registry::node* call_registry::insereix_numero(node *n, nat num, const string& name, nat compt) {
// Pre: el número num no existeix en l'arbre AVL amb arrel n
// Post: retorna l'arrel de l'arbre AVL actualitzat amb la inserció del
//       número num mantenint totes les propietats de l'arbre AVL
    if (n == nullptr) {
        node *aux = new node;
        phone ph(num, name, compt);
        aux->_ph = ph;
        aux->_altura = 1;
        aux->_esq = nullptr;
        aux->_dret = nullptr;
        _mida++;
        return aux;
    }
    else {
        if (num < n->_ph.numero())
            n->_esq = insereix_numero(n->_esq, num, name, compt);
        else 
            n->_dret = insereix_numero(n->_dret, num, name, compt);
    
        n->_altura = max(altura(n->_esq), altura(n->_dret)) + 1;
        int fact = factor_equilibri(n);
    
        if (fact > 1) {
            if (factor_equilibri(n->_esq) >= 0)
                n = rotacio_dreta(n);
            else if (factor_equilibri(n->_esq) < 0) {
                n->_esq = rotacio_esquerra(n->_esq);
                n = rotacio_dreta(n);
            }
        }

        else if (fact < -1) {
            if (factor_equilibri(n->_dret) <= 0)
                n = rotacio_esquerra(n);
            else if (factor_equilibri(n->_dret) > 0) {
                n->_dret = rotacio_dreta(n->_dret);
                n = rotacio_esquerra(n);
            }
        }
    }

    return n;
}

// Cost: θ(log (n))
call_registry::node* call_registry::elimina_numero(node *n, nat num) {
// Pre: el número num existeix en l'arbre AVL amb arrel n
// Post: retorna l'arrel de l'arbre AVL actualitzat amb la eliminació del
//       número num mantenint totes les propietats de l'arbre AVL
    if (n != nullptr) {
        if (num < n->_ph.numero()) 
            n->_esq = elimina_numero(n->_esq, num);
        else if (num > n->_ph.numero())
            n->_dret = elimina_numero(n->_dret, num);
        else {
            if (n->_esq == nullptr || n->_dret == nullptr) {
                node *aux;

                if (n->_esq != nullptr) aux = n->_esq;
                else aux = n->_dret;

                if (aux == nullptr) {
                    aux = n;
                    n = nullptr;
                } 
                else
                    *n = *aux;
                
                _mida--;
                delete aux;
            }
            else {
                node* aux = n->_dret;
                while (aux->_esq != nullptr) {
                    // Trobem el node amb el número mínim de l'arbre de la dreta
                    // Aquest serà el successor del número a eliminar
                    aux = aux->_esq;
                }
                n->_ph = aux->_ph;
                n->_dret = elimina_numero(n->_dret, aux->_ph.numero());
            }
        }
    }

    if (n != nullptr) {
        n->_altura = max(altura(n->_esq), altura(n->_dret)) + 1;
        int fact = factor_equilibri(n);

        if (fact > 1) {
            if (factor_equilibri(n->_esq) >= 0)
                n = rotacio_dreta(n);
            else if (factor_equilibri(n->_esq) < 0) {
                n->_esq = rotacio_esquerra(n->_esq);
                n = rotacio_dreta(n);
            }
        }

        else if (fact < -1) {
            if (factor_equilibri(n->_dret) <= 0)
                n = rotacio_esquerra(n);
            else if (factor_equilibri(n->_dret) > 0) {
                n->_dret = rotacio_dreta(n->_dret);
                n = rotacio_esquerra(n);
            }
        }
    }

    return n;
}


/*----------------------< MÈTODES PÚBLICS >-----------------------*/
// Cost: θ(1)
call_registry::call_registry() throw(error) : _arrel(nullptr), _mida(0) {}

// Cost: θ(n)
call_registry::call_registry(const call_registry& R) throw(error) : _mida(R._mida) {
    _arrel = copia_arbre(R._arrel);
}

// Cost: θ(n)
call_registry& call_registry::operator=(const call_registry& R) throw(error) {
    _mida = R._mida;
    esborra_arbre(_arrel);
    _arrel = copia_arbre(R._arrel);
    
    return *this;
}

// Cost: θ(n)
call_registry::~call_registry() throw() {
    esborra_arbre(_arrel);
    _mida = 0;
}

// Cost: θ(log (n))
void call_registry::registra_trucada(nat num) throw(error) {
// Pre: Cert
// Post: Si el número num existeix, s'incrementa el seu comptador de trucades. 
//       Si el número num no estava prèviament, afegeix una nova entrada
//       amb el número de telèfon donat, un nom buit i el comptador a 1.
    if (conte(num)) {
        node *aux = busca(_arrel, num);
        aux->_ph++;
    }
    else
        _arrel = insereix_numero(_arrel, num, "", 1);
}

// Cost: θ(log (n))
void call_registry::assigna_nom(nat num, const string& name) throw(error) {
// Pre: Cert
// Post: Assigna el nom indicat al número donat. Si el número no 
//       estava prèviament, afegeix una nova entrada amb el número 
//       i nom donats, i el comptador de trucades a 0.
//       Si el número ja existeix prèviament, li assigna el nom donat.
    if (not conte(num)) {
        _arrel = insereix_numero(_arrel, num, name, 0);
    }
    else {
        node *aux = busca(_arrel, num);
        phone ph(aux->_ph.numero(), name, aux->_ph.frequencia());
        aux->_ph = ph;
    }
}

// Cost: θ(log (n))
void call_registry::elimina(nat num) throw(error) {
// Pre: Cert
// Post: Elimina l'entrada corresponent al telèfon amb el número donat.
//       Es produeix un error si el número no estava present.
    if (not conte(num))
        throw error(ErrNumeroInexistent);
    else 
        _arrel = elimina_numero(_arrel, num);
}

// Cost: θ(log (n))
bool call_registry::conte(nat num) const throw() { 
// Pre: Cert
// Post: retorna cert si el paràmetre implícit conté el número num
//       en cas contrari, retorna fals
    bool found (false);
    node *n = _arrel;
    while (not found && n != nullptr) {
        if (n->_ph.numero() == num)
            found = true;
        else if (n->_ph.numero() > num)
            n = n->_esq;
        else if (n->_ph.numero() < num)
            n = n->_dret;
    }
    return found;
}

// Cost: θ(log (n))
string call_registry::nom(nat num) const throw(error) {
// Pre: Cert
// Post: Retorna el nom vinculat amb el número num. Si el número no
//       existeix, es produeix un error
    if (not conte(num))
        throw error(ErrNumeroInexistent);
    else {
        node *n = busca(_arrel, num);
        return n->_ph.nom();
    }
}

// Cost: θ(log (n))
nat call_registry::num_trucades(nat num) const throw(error) {
// Pre: Cert
// Post: Retorna la freqüència vinculada amb el número num. Si el número no
//       existeix, es produeix un error
    if (not conte(num))
        throw error(ErrNumeroInexistent);
    else {
        node *n = busca(_arrel, num);
        return n->_ph.frequencia();
    }
}

// Cost: θ(1)
bool call_registry::es_buit() const throw() {
// Pre: Cert
// Post: Retorna cert si no hi ha cap número registrat, en cas
//       contrari, retorna fals
    return (_arrel == nullptr);
}

// Cost: θ(1)
nat call_registry::num_entrades() const throw() {
// Pre: Cert
// Post: Retorna el número d'entrades (telèfons) que hi ha al call_registry
    return _mida;
}

// Cost: θ(n^2)
void call_registry::dump(vector<phone>& V) const throw(error) {
    rec_inordre(_arrel, V);

    // Comprovem si hi ha noms repetits
    for (nat i = 0; i < V.size(); ++i) {
        for (nat j = i + 1; j < V.size(); ++j) {
            if (V[i].nom() == V[j].nom()) {
                throw error(ErrNomRepetit);
            }
        }
    }
}