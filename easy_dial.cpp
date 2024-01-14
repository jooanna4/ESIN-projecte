#include "easy_dial.hpp"
#include <iostream>
using namespace std;

/*------------------------< MERGE SORT >-------------------------*/
// Cost: θ(n)
void merge(vector<string>& v, int ini, int m, int fi) {
// Pre:  'ini' és l'índex inicial del rang a fusionar, 
//       'm' és l'índex mitjà del rang a fusionar, 
//       'fi' és l'índex final del rang a fusionar.
//       0 <= ini <= m <= fi < v.size()
//       Els subvectors v[ini..m] i v[m+1..fi] estan ordenats lexicogràficament.
// Post: El rang v[ini..fi] està ordenat lexicogràficament.
    vector<string> esq(m-ini+1);
    vector<string> dreta(fi-m);
    for(int i = 0; i < esq.size(); i++){
        esq[i] = v[ini+i];
    }
    for(int j = 0; j < dreta.size(); j++){
        dreta[j]=v[m+j+1];
    }

    int i = 0, j = 0, k;

    for(k = ini; k <= fi && i < esq.size() && j < dreta.size(); k++){
        if(esq[i] < dreta[j]){
            v[k] = esq[i];
            i++;
        }else if(esq[i] > dreta[j]){
            v[k] = dreta[j];
            j++;
        }
    }
    while(i < esq.size()){
        v[k] = esq[i];
        k++; i++;
    }
    while(j < dreta.size()){
        v[k] = dreta[j];
        k++; j++;
    }
}

// Cost: θ(n * log (n))
void merge_sort(vector<string>&result, int ini, int fi) {
// Pre: 0 <= ini, ini <= fi, fi < result.size()
// Post: result està ordenat lexicogràficament
    if (ini < fi) {
        int m = (ini+fi)/2;
        merge_sort(result, ini, m);
        merge_sort(result, m+1, fi);
        merge(result, ini, m, fi);
    }
}

/*----------------------< MÈTODES PRIVATS >-----------------------*/
// Cost: θ(nom.size() * log(#simbols))
easy_dial::node_tst* easy_dial::insereix_nom(node_tst *n, const string& nom, nat i, phone& ph) {
// Pre:  'nom' és un string no buit, i = 0, 'ph' es el telèfon amb nom = 'nom'
// Post: retorna l'arrel de l'arbre TST on s'ha inserit el nom 'nom'.
//       cada node conté el telèfon més gran dels seus fills (seguint les condicions d'ordenació de la classe phone)
//       L'arbre resultant compleix les propietats de l'estructura trie de subarbres binaris (TST).
//       'ph' s'ha inserit a l'últim caràcter de 'nom' (phone::ENDCHAR)
    if (n == nullptr) {
        n = new node_tst;
        n->_c = nom[i];
        n->_esq = nullptr;
        n->_dret = nullptr;
        n->_cen = nullptr;
        if (i < nom.size())
            n->_cen = insereix_nom(n->_cen, nom, i+1, ph);
        if (n->_c == phone::ENDCHAR) 
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
    if (n != nullptr && n->_c != phone::ENDCHAR) {
        phone aux;
        if (n->_esq != nullptr) aux = n->_esq->_telf;
        if (n->_cen != nullptr && aux < n->_cen->_telf) aux = n->_cen->_telf;
        if (n->_dret != nullptr && aux < n->_dret->_telf) aux = n->_dret->_telf;
        n->_telf = aux;
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
            aux->_telf = n->_telf;
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
// Post: Allibera espai de la memòria de l'arbre AVTST apuntat per n. 
//       Si n es null, no realitza cap acció
    if (n != nullptr) {
        esborra_tst(n->_esq);
        esborra_tst(n->_dret);
        esborra_tst(n->_cen);
        delete n;
    }
}

// Cost: θ(n)
void easy_dial::primer_phone(node_tst* n, phone &tel) {
// Pre: cert
// Post: posa a 'tel' el primer phone del TST (el de major freqüencia)
    if (n != nullptr) {
        if (n->_c == phone::ENDCHAR && tel < n->_telf) {
            tel = n->_telf;
        }

        primer_phone(n->_esq, tel);
        primer_phone(n->_cen, tel);
        primer_phone(n->_dret, tel);
    }
}

// Cost: θ(pref.size() * log(#simbols))
easy_dial::node_tst* easy_dial::consultapref(node_tst *n, string pref) {
// Pre:  'pref' és un string no buit
// Post: Retorna el punter a l'ultim node del prefix pref
//       Si no existeix el prefix 'pref', retorna nullptr
    int i = 0, sz = pref.size();
    node_tst *aux(n);
    
    if (n != nullptr && n->_c != pref[0]) {             // Buscar on comença el prefix pref
        bool found(false);
        while (aux != nullptr && not found) {
            if (pref[0] < aux->_c) aux = aux->_esq;
            else if (pref[0] > aux->_c) aux = aux->_dret;
            else found = true;
        }
    }
    
    while (aux != nullptr && i < sz-1) {                // Buscar on acaba el prefix pref
        char c_actual = pref[i];
        if (c_actual < aux->_c) 
            aux = aux->_esq;
        else if (c_actual > aux->_c) 
            aux = aux->_dret;
        else {
            aux = aux->_cen;
            i++;
        }
    }
    if (aux != nullptr && aux->_c != pref[pref.size()-1]) aux = nullptr;

    return aux;
}

// Cost: θ(#simbols)
void easy_dial::comencen(node_tst *n, vector<string>& result) {
// Pre: cert
// Post: posa al final del vector 'result' tots els noms de l'arbre n
    if (n != nullptr) {
        if (n->_c == phone::ENDCHAR)
            result.push_back(n->_telf.nom());
        
        comencen(n->_esq, result);
        comencen(n->_cen, result);
        comencen(n->_dret, result);
    }
}

// Cost: θ(1)
void easy_dial::reset() {
// Pre:  Cert
// Post: Posa el prefix a indefinit
    _prefindef = true;
    _pref = "";
    _hihatelefon = false;
}

// Cost: θ(#simbols)
void easy_dial::longitudm(node_tst *n, nat i, double &freq, double &acumfp) const {
// Pre:  freq = 0, acumfp = 0
// Post: freq = suma de totes les frequencies del easy_dial
//       acumfp = frequencia*numero de pulsacions de tots els telefons del easy_dial
    if (n != nullptr){
        if (n->_c == phone::ENDCHAR) {
            freq += n->_telf.frequencia();
            acumfp += n->_telf.frequencia()*i;
        }

        longitudm(n->_esq, i, freq, acumfp);
        longitudm(n->_cen, i+1, freq, acumfp);
        longitudm(n->_dret, i, freq, acumfp);
    }
}


/*----------------------< MÈTODES PÚBLICS >-----------------------*/

easy_dial::easy_dial(const call_registry& R) throw(error) : _npref(nullptr), _arrel(nullptr), _prefindef(true), _hihatelefon(false) {
    vector<phone>vec;
    R.dump(vec);
    string k;

    for (int i = 0; i < vec.size(); i++) {
        k = vec[i].nom() + phone::ENDCHAR;
        _arrel = insereix_nom(_arrel, k, 0, vec[i]);
    }
}

easy_dial::easy_dial(const easy_dial& D) throw(error) {
    _arrel = copia_tst(D._arrel);
    _pref = D._pref;
    _prefindef = D._prefindef;
    _npref = D._npref;
    _hihatelefon = D._hihatelefon;
}

easy_dial& easy_dial::operator=(const easy_dial& D) throw(error) {
    esborra_tst(_arrel);
    _arrel = copia_tst(D._arrel);
    _pref = D._pref;
    _prefindef = D._prefindef;
    _npref = D._npref;
    _hihatelefon = D._hihatelefon;

    return *this;
}

easy_dial::~easy_dial() throw() {
    esborra_tst(_arrel);
}

string easy_dial::inici() throw() {
    _pref = "";
    _prefindef = false;         // Pref a buit
    _npref = _arrel;

    if (_npref != nullptr) {
        _hihatelefon = true;
        return _npref->_telf.nom();
    }
    else return "";
}

string easy_dial::seguent(char c) throw(error) {
    if (_prefindef) throw error(ErrPrefixIndef);
    else if (not _hihatelefon) {
        reset();
        throw error(ErrPrefixIndef);
    }

    // Comprovació amb F(S, p)
    if (_npref == nullptr) {                // No existeix F(S, p)
        reset();
        throw error(ErrPrefixIndef);
    }
    phone aux(_npref->_telf);

    // Canvi prefix
    if (c == '\0') c = phone::ENDCHAR;
    _pref += c;
    _prefindef = false;

    // Comprovació amb F(S, p')
    _npref = consultapref(_arrel, _pref);
    
    if (_npref == nullptr) {
        _hihatelefon = false;
        return "";
    }
    else if (_npref->_telf == aux) {

        node_tst *aux1(_npref->_cen);
        bool found(false);
        nat i = aux1->_telf.frequencia();
        // Busca el segon mes gran
        while (aux1 != nullptr && not found && i > 0) {
            if (aux1->_esq != nullptr && aux1->_esq->_telf.frequencia() == i && aux1->_esq->_telf.nom() != _npref->_telf.nom()) {
                found = true;
                aux1 = aux1->_esq;
            }
            else if (aux1->_cen != nullptr && aux1->_cen->_telf.frequencia() == i && aux1->_cen->_telf.nom() != _npref->_telf.nom()) {
                found = true;
                aux1 = aux1->_cen;
            }
            else if (aux1->_dret != nullptr && aux1->_dret->_telf.frequencia() == i && aux1->_dret->_telf.nom() != _npref->_telf.nom()) {
                found = true;
                aux1 = aux1->_dret;
            }
            i--;
        }
        if (found) {
            _hihatelefon = true;
            _npref = aux1;
            return aux1->_telf.nom();
        }
        else {
            _hihatelefon = false;
            return "";
        }
    }
    else return _npref->_telf.nom();
}

string easy_dial::anterior() throw(error) {
    if (_prefindef) throw error(ErrPrefixIndef);
    else if (_pref == "") {
        reset();
        throw error(ErrNoHiHaAnterior);
    }

    _pref.pop_back();                               // Elimina l'ultim caracter del prefix en curs
    if (_pref == "") {
        _npref = _arrel;
        _hihatelefon = true;
        return _npref->_telf.nom();
    }
    else {
        _npref = consultapref(_arrel, _pref);
        if (_npref == nullptr) {
            reset();
            throw error(ErrNoExisteixTelefon);
        }
        else 
            _hihatelefon = true;
        return _npref->_cen->_telf.nom();
    }
}

nat easy_dial::num_telf() const throw(error) {
    if (_prefindef) throw error(ErrPrefixIndef);
    if (not _hihatelefon) {
        throw error(ErrNoExisteixTelefon);
    }
    phone mes_gran;
    if (_pref == "") mes_gran = _arrel->_telf;
    else {
        node_tst *pref = consultapref(_arrel, _pref);
        if (pref == nullptr) {
            throw error(ErrNoExisteixTelefon);
        }

        if (pref->_c == phone::ENDCHAR) mes_gran = pref->_telf;
        else primer_phone(pref->_cen, mes_gran);
    }
    if (mes_gran.nom().empty()) {
        throw error(ErrNoExisteixTelefon);
    }

    return mes_gran.numero();
}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error) {
    if (pref != "") {
        node_tst *npref = consultapref(_arrel, pref);
        if (npref != nullptr) {
            if (npref->_c == phone::ENDCHAR) result.push_back(npref->_telf.nom());
            else {
                comencen(npref->_cen, result);
                merge_sort(result, 0, result.size()-1);
            }
        }
    }
    else {
        comencen(_arrel, result);
        merge_sort(result, 0, result.size()-1);
    }
}

double easy_dial::longitud_mitjana() const throw() {
    double freq = 0;
    if (_arrel != nullptr)
        freq = _arrel->_telf.frequencia();

    double acumfp = 0;
    longitudm(_arrel, 1, freq, acumfp);
    if (freq != 0) freq = acumfp / freq;
    return freq;
}