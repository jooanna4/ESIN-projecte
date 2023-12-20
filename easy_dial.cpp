#include "easy_dial.hpp"
/*----------------------< MÈTODES PRIVATS >-----------------------*/
// Cost: θ(nom.length() * log(#simbols))
easy_dial::node_tst* easy_dial::insereix_nom(node_tst *n, const string &nom, nat i, phone ph) {
    if (n == nullptr) {
        n = new node_tst;
        n->_c = nom[i];
        n->_esq = nullptr;
        n->_dret = nullptr;
        n->_cen = nullptr;
        if (i < k.size()-1)
            n->_cen = insereix_nom(n->_cen, nom, i+1, ph);
        else
            n->_telf = ph;
    }
    else {
        if (nom[i] < n->_c)
            n->_esq = insereix_nom(n->_esq, nom, i, ph);
        else if (nom[i] > n->_c)
            n->_dret = insereix_nom(n->_dret, nom, i, ph);
        else
            n->_cen = insereix_nom(n->_cen, nom, i+1, ph);
    }
    return n;
}

// Cost: θ(n)
easy_dial::node_tst* easy_dial::copia_tst(node_tst *n) {
// Pre: Cert
// Post: retorna un punter que apunta a l'arrel de l'arbre TST
//       que és còpia de l'arbre TST amb arrel n
    node_tst *aux(nullptr);
    if (n != nullptr) {
        aux = new node_tst;
        try {
            aux->_c = n->_c;
            aux->_ph = n->_ph;
            aux->_esq = copia_tst(n->_esq);
            aux->_dret = copia_tst(n->_dret);
            aux->_cen = copia_tst(n->_cen);
        } catch (...) {
            delete aux;
            throw;
        }
    }
    return aux;
}

// Cost: θ(n)
void easy_dial::esborra_tst(node_tst *n) {
// Pre: Cert
// Post: Allibera espai de la memòria de l'arbre AVL apuntat per n. 
//       Si n es null, no realitza cap acció
    if (n != nullptr) {
        esborra_tst(n->_esq);
        esborra_tst(n->_dret);
        esborra_tst(n->_cen);
        delete n;
    }
}

/*----------------------< MÈTODES PÚBLICS >-----------------------*/

easy_dial::easy_dial(const call_registry& R) throw(error) : _arrel(nullptr), _pref("") {
    vector<phone>vec;
    // vec amb nom del call_registry ordenat per frequencies
    R.dump(vec);
    string k;
    for (int i = 0; i < vec.size(); i++) {
        k = vec[i].nom() + phone::ENDCHAR;
        _arrel = insereix_nom(_arrel, k, 0, vec[i]);
    }
}

easy_dial::easy_dial(const easy_dial& D) throw(error) {
    _arrel = copia_tst(_arrel);
}

easy_dial& easy_dial::operator=(const easy_dial& D) throw(error) {
    
    return *this;
}

easy_dial::~easy_dial() throw() {
    esborra_tst(_arrel);
}

string easy_dial::inici() throw() {
    return "";
}

string easy_dial::seguent(char c) throw(error) {
    return "";
}

string easy_dial::anterior() throw(error) {
    return "";
}

nat easy_dial::num_telf() const throw(error) {
    // mirar tots els phones amb prefix actual i anar deixant el mes gran a una variable
    return 1;
}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error) {
    if (pref != "") {
        
    }
}

double easy_dial::longitud_mitjana() const throw() {
    return 1;
}