#include "easy_dial.hpp"
/*----------------------< MÈTODES PRIVATS >-----------------------*/
// Cost: θ(nom.length() * log(#simbols))
easy_dial::node_tst* easy_dial::insereix_nom(node_tst *n, const string& nom, nat i, phone& ph) {
    if (n == nullptr) {
        n = new node_tst;
        n->_c = nom[i];
        n->_esq = nullptr;
        n->_dret = nullptr;
        n->_cen = nullptr;
        if (i < nom.size())
            n->_cen = insereix_nom(n->_cen, nom, i+1, ph);
        else if (i == nom.size())
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
// Post: Allibera espai de la memòria de l'arbre AVL apuntat per n. 
//       Si n es null, no realitza cap acció
    if (n != nullptr) {
        esborra_tst(n->_esq);
        esborra_tst(n->_dret);
        esborra_tst(n->_cen);
        delete n;
    }
}

easy_dial::node_tst* easy_dial::consulta(node_tst *n, nat i, const string &nom) {
    node_tst *res = nullptr;
    if (n != nullptr) {
        if (i == nom.size() && n->_c == phone::ENDCHAR)
            res = n;
        else if (n->_c > nom[i])
            res = consulta(n->_esq, i, nom);
        else if (n->_c < nom[i])
            res = consulta(n->_dret, i, nom);
        else if (n->_c == nom[i])
            res = consulta(n->_cen, i+1, nom);
    }
    return res;
}

phone easy_dial::primer_phone(node_tst* n) {
    if (n != nullptr) {
        phone phone_esq = primer_phone(n->_esq);
        if (phone_esq.nom() != "") {
            return phone_esq;
        }
        if (n->_c == phone::ENDCHAR && n->_telf.nom() != "") {
            return n->_telf;
        }
        phone phone_cen = primer_phone(n->_cen);
        if (phone_cen.nom() != "") {
            return phone_cen;
        }
        return primer_phone(n->_dret);
    }
    else 
        return phone();
}

easy_dial::node_tst* easy_dial::consultapref(node_tst *n, string pref) {
// Retorna el punter al node al ultim node del prefix pref
    int i = 0;
    node_tst *aux(n);

    while (aux != nullptr && i < pref.size()) {
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

    return aux;
}

void easy_dial::comencen(node_tst *n, vector<string>& result, const string& prefix_actual) {
    if (n != nullptr) {
        comencen(n->_esq, result, prefix_actual);
        if (n->_c == '#')
            result.push_back(prefix_actual);
        else
            comencen(n->_cen, result, prefix_actual + n->_c);
        comencen(n->_dret, result, prefix_actual);
    }
}
// Merge Sort
vector<phone> easy_dial::ordena(vector<phone>&vec) {
    if (vec.size() > 1) {
        nat mid = vec.size()/2;
        
        vector<phone> esq(vec.begin(),vec.begin()+mid);
        vector<phone> dreta(vec.begin()+mid,vec.begin()+vec.size());

        esq = ordena(esq);
        dreta = ordena(dreta);

        unsigned i = 0;
        unsigned j = 0;
        unsigned k = 0;
        while (i < esq.size() && j < dreta.size()) {
            if (esq[i] < dreta[j]) {
                vec[k]=esq[i];
                i++;
            } else {
                vec[k] = dreta[j];
                j++;
            }
            k++;
        }

        while (i<esq.size()) {
            vec[k] = esq[i];
            i++;
            k++;
        }

        while (j<dreta.size()) {
            vec[k]=dreta[j];
            j++;
            k++;
        }
    }
    return vec;
}


/*----------------------< MÈTODES PÚBLICS >-----------------------*/

easy_dial::easy_dial(const call_registry& R) throw(error) : _arrel(nullptr), _prefindef(true) {
    _pref = "";
    vector<phone>vec;
    R.dump(vec);
    // vec amb nom del call_registry ordenat per frequencies
    string k;
    for (int i = 0; i < vec.size(); i++) {
        k = vec[i].nom() + phone::ENDCHAR;
        _arrel = insereix_nom(_arrel, k, 0, vec[i]);
    }
}

easy_dial::easy_dial(const easy_dial& D) throw(error) {
    esborra_tst(_arrel);
    _arrel = copia_tst(D._arrel);
    _pref = D._pref;
    _prefindef = D._prefindef;
}

easy_dial& easy_dial::operator=(const easy_dial& D) throw(error) {
    esborra_tst(_arrel);
    _arrel = copia_tst(D._arrel);
    _pref = D._pref;
    _prefindef = D._prefindef;
    return *this;
}

easy_dial::~easy_dial() throw() {
    esborra_tst(_arrel);
    _arrel = nullptr;
    _pref = "";
    _prefindef = true;
}

string easy_dial::inici() throw() {
    _pref = "";             
    _prefindef = false;         // Pref a buit
    return (primer_phone(_arrel)).nom();
}

string easy_dial::seguent(char c) throw(error) {
    if (_prefindef) throw error(ErrPrefixIndef);

    // Comprovació amb F(S, p)
    node_tst *pref = consultapref(_arrel, _pref);
    phone mes_gran1;
    if (pref != nullptr)
        mes_gran1 = primer_phone(pref->_cen);
    if (mes_gran1.nom() == "") {
        _pref = "";
        _prefindef = true;
        throw error(ErrPrefixIndef);
    }
    // Canvi prefix
    _pref += c;
    _prefindef = false;

    // Comprovació amb F(S, p')
    pref = consultapref(_arrel, _pref);
    phone mes_gran2;
    if (pref != nullptr)
        mes_gran2 = primer_phone(pref->_cen);
    if (mes_gran2.nom() == "") {
        return "";
    }
    else
        return mes_gran2.nom();
}

string easy_dial::anterior() throw(error) {
    if (_prefindef) throw error(ErrPrefixIndef);
    else if (_pref == "") throw error(ErrNoHiHaAnterior);
    else if (_pref.size() == 1) throw error(ErrPrefixIndef);

    _pref.pop_back();

    node_tst *pref = consultapref(_arrel, _pref);
    phone mes_gran = primer_phone(pref->_cen);
    if (mes_gran.nom() != "")
        return mes_gran.nom();
    else
        return "";
}

nat easy_dial::num_telf() const throw(error) {
    if (_prefindef) throw error(ErrPrefixIndef);

    node_tst *pref = consultapref(_arrel, _pref);
    phone mes_gran = primer_phone(pref->_cen);

    if (mes_gran.nom() == "") throw error(ErrNoExisteixTelefon);

    return mes_gran.numero();
}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error) {
    if (pref != "") {
        node_tst *npref = consultapref(_arrel, pref);
        comencen(npref->_cen, result, pref);
    }
}

/* Retorna el número mitjà de pulsacions necessàries para obtenir un
  telèfon. Formalment, si X és el conjunt de noms emmagatzemats en
  el easy_dial i t(s) és el número de pulsacions mínimes
  necessàries (= número de crides a l'operació seguent) per
  obtenir el telèfon el nom del qual és s. La funció retorna la suma
      Pr(s) · t(s)
  per tots els telèfons s del conjunt X, sent Pr(s) la probabilitat de
  telefonar a s. La probabilitat s'obté dividint la freqüència de s per
  la suma de totes les freqüències. */
double easy_dial::longitud_mitjana() const throw() {
    double sum = 0;
    double total_freq = 0;
    vector<phone> vec;
    recorre_tst(_arrel, "", vec);
    for (const auto& p : vec) {
        total_freq += p.frequencia();
    }
    for (const auto& p : vec) {
        double prob = p.frequencia() / total_freq;
        string nom = p.nom();
        int num_pulsacions = 0;
        bool encontrado = false;
        inici();
        while (!encontrado && num_pulsacions < nom.size()) {
            if (seguent(nom[num_pulsacions]) == nom) {
                num_pulsacions += nom.size();
                encontrado = true;
            }
            num_pulsacions++;
        }
        if (!encontrado) continue;
        sum += prob * num_pulsacions;
    }
    return sum;
}

void easy_dial::recorre_tst(node_tst* n, string prefix, vector<phone>& vec) const {
    if (n != nullptr) {
        recorre_tst(n->_esq, prefix, vec);
        if (n->_c == phone::ENDCHAR && n->_telf.nom() != "") {
            vec.push_back(n->_telf);
        }
        recorre_tst(n->_cen, prefix + n->_c, vec);
        recorre_tst(n->_dret, prefix, vec);
    }
}