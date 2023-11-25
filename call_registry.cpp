#include "call_registry.hpp"

/*  *********************  MÈTODES PRIVATS  *********************  */
nat call_registry::altura(node *n) {
// Pre: cert
// Post: retorna l'altura de l'arbre amb arrel n
    nat aux;
    if (n == nullptr)
        aux = 0;
    else
        aux = n->_altura;
    return aux;
}

nat call_registry::factor_equilibri(node *n) {
// Pre: Cert
// Post: retorna el factor d'equilibri de l'arbre AVL amb arrel n
    nat aux;
    if (n == nullptr)
        aux = 0;
    else
        aux = altura(n->_esq) - altura(n->_dret);
    return aux;
}

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

// Mètodes privats per la constructora i destructora
call_registry::node* call_registry::copia_arbre(node *n) {
// Pre: Cert
// Post: retorna un punter que apunta a l'arrel de l'AVL
//       que es còpia de l'arbre AVL apuntat per n
    node *aux(nullptr);
    if (n != nullptr) {
        aux = new node;
        try {
            aux->_ph = n->_ph;
            aux->_esq = copia_arbre(n->_esq);
            aux->_dret = copia_arbre(n->_dret);
        } catch (...) {
            delete aux;
            throw;
        }
    }
    return aux;
}

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

// Metodes privats per inserir un número a l'AVL
call_registry::node* call_registry::rotacio_esquerra(node *n) {
// Pre: cert
// Post: retorna el node arrel de l'arbre AVL després de realitzar
//       una rotació cap a l'esquerra del node arrel n inicial
    node *nova_n = n->_dret;
    node *aux = nova_n->_esq;

    // Intercanvi de nodes
    nova_n->_esq = n;
    n->_dret = aux;

    // S'actualitzen les altures
    n->_altura = max(altura(n->_esq), altura(n->_dret)) + 1;
    nova_n->_altura = max(altura(nova_n->_esq), altura(nova_n->_dret)) + 1;

    return nova_n;
}

call_registry::node* call_registry::rotacio_dreta(node *n) {
// Pre: cert
// Post: retorna el node arrel de l'arbre AVL després de realitzar
//       una rotació cap a la dreta del node arrel n inicial
    node *nova_n = n->_esq;
    node *aux = nova_n->_dret;

    // Intercanvi de nodes
    nova_n->_dret = n;
    n->_esq = aux;

    // S'actualitzen les altures
    n->_altura = max(altura(n->_esq), altura(n->_dret)) + 1;
    nova_n->_altura = max(altura(nova_n->_esq), altura(nova_n->_dret)) + 1;

    return nova_n;
}

call_registry::node* call_registry::insereix_numero(node *n, nat num, const string& name, nat compt) {
// Pre: el número num no existeix en l'arbre AVL amb arrel n
// Post: retorna l'arrel de l'arbre AVL actualitzat amb la inserció del
//       número num mantenint totes les propietats de l'arbre AVL
    if (n == nullptr) {
        node *aux = new node;
        phone ph(num, name, compt);
        aux->_ph = ph;
        aux->_esq = nullptr;
        aux->_dret = nullptr;
        return aux;
    }
    else if (num < n->_ph.numero())
        n->_esq = insereix_numero(n->_esq, num, name, compt);
    else
        n->_dret = insereix_numero(n->_dret, num, name, compt);
    
    n->_altura = max(altura(n->_esq), altura(n->_dret)) + 1;
    _mida++;
    nat fact = factor_equilibri(n);

    if (fact > 1 && num < n->_esq->_ph.numero())
        return rotacio_dreta(n);
    
    if (fact < -1 && num > n->_dret->_ph.numero())
        return rotacio_esquerra(n);
    
    if (fact > 1 && num > n->_esq->_ph.numero()) {
        n->_esq = rotacio_esquerra(n->_esq);
        return rotacio_dreta(n);
    }
    if (fact < -1 && num < n->_dret->_ph.numero()) {
        n->_dret = rotacio_dreta(n->_dret);
        return rotacio_esquerra(n);
    }

    return n;
}

// Metodes privats per eliminar un número a l'AVL
call_registry::node* call_registry::elimina_numero(node *n, nat num) {
// Pre: el número num existeix en l'arbre AVL amb arrel n
// Post: retorna l'arrel de l'arbre AVL actualitzat amb l'eliminació del
//       número num mantenint totes les propietats de l'arbre AVL
    node *aux = n;
    if (n != nullptr) {
        if (num < n->_ph.numero())
            n->_esq = elimina_numero(n->_esq, num);
        else if (num > n->_ph.numero())
            n->_dret = elimina_numero(n->_dret, num);
        else {
            node *aux = ajunta (n->_esq, n->_dret);
            delete (n);
            return aux;
        }
    }
    
    n->_altura = max(altura(n->_esq), altura(n->_dret)) + 1;
    _mida--;
    nat fact = factor_equilibri(n);

    if (fact > 1 && num < n->_esq->_ph.numero())
        return rotacio_dreta(n);
    
    if (fact < -1 && num > n->_dret->_ph.numero())
        return rotacio_esquerra(n);
    
    if (fact > 1 && num > n->_esq->_ph.numero()) {
        n->_esq = rotacio_esquerra(n->_esq);
        return rotacio_dreta(n);
    }
    if (fact < -1 && num < n->_dret->_ph.numero()) {
        n->_dret = rotacio_dreta(n->_dret);
        return rotacio_esquerra(n);
    }

    return n;
}

call_registry::node* call_registry::ajunta(node* n1, node* n2) {
// Pre: Cert
// Post: retorna l'arbre resultant de fusionar n1 i n2
//       mantenint totes les propietats de l'arbre BST
    if (n1 == nullptr) 
        return n2;
    
    else if (n2 == nullptr)
        return n1;

    else {
        node *aux = elimina_maxim(n1);
        aux->_dret = n2;
        return aux;
    }
}

call_registry::node* call_registry::elimina_maxim(node *n) {
// Pre: Cert
// Post: retorna el node amb el valor màxim en l'arbre AVL amb arrel n,
//       eliminant aquest node de l'arbre
    node *n_orig = n, *pare = nullptr;
    while (n->_dret != nullptr) {
        pare = n;
        n = n->_dret;
    }
    if (pare != nullptr) {
        pare->_dret = n->_esq;
        n->_esq = n_orig;
    }
    return n;
}


/*  *********************  MÈTODES PÚBLICS  *********************  */
call_registry::call_registry() throw(error) : _arrel(nullptr), _mida(0) {}

call_registry::call_registry(const call_registry& R) throw(error) : _mida(R._mida) {
    _arrel = copia_arbre(R._arrel);
}

call_registry& call_registry::operator=(const call_registry& R) throw(error) {
// Pre: cert
// Post: el paràmetre implícit és una còpia de R
    _mida = R._mida;
    if (*this != R) {
        esborra_arbre(_arrel);
        _arrel = copia_arbre(R._arrel);
    }
    return *this;
}

call_registry::~call_registry() throw() {
    esborra_arbre(_arrel);
    _mida = 0;
}

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

void call_registry::elimina(nat num) throw(error) {
// Pre: Cert
// Post: Elimina l'entrada corresponent al telèfon amb el número donat.
//       Es produeix un error si el número no estava present.
    if (not conte(num))
        throw error(ErrNumeroInexistent);
    else 
        _arrel = elimina_numero(_arrel, num);
}

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

bool call_registry::es_buit() const throw() {
// Pre: Cert
// Post: Retorna cert si no hi ha cap número registrat, en cas
//       contrari, retorna fals
    return (_arrel == nullptr);
}

nat call_registry::num_entrades() const throw() {
// Pre: Cert
// Post: Retorna el número d'entrades (telèfons) que hi ha al call_registry
    return _mida;
}

void call_registry::dump(vector<phone>& V) const throw(error) {

}