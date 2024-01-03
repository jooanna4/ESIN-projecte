#include "phone.hpp"
#include <cstring>

// Cost: θ(name.size())
phone::phone(nat num, const string& name, nat compt) throw(error) {
    bool found(false);
    nat i = 0;
    int siz = name.size();
    while (not found && i < siz) {        
        if (name[i] == DELETECHAR ||
            name[i] == ENDCHAR ||
            name[i] == ENDPREF)
            found = true;
        i++;
    }

    if (found)
        throw error(ErrNomIncorrecte);
        
    else {
        _num = num;
        _name = name;
        _compt = compt;
    }
}

// Cost: θ(1)
phone::phone(const phone& T) throw(error) {
    _num = T._num;
    _name = T._name;
    _compt = T._compt;
}

// Cost: θ(1)
phone& phone::operator=(const phone& T) throw(error) {
    _num = T._num;
    _name = T._name;
    _compt = T._compt;
    return *this;
}

// Cost: θ(1)
phone::~phone() throw() {}

// Cost: θ(1)
nat phone::numero() const throw() {
    return _num;
}

// Cost: θ(1)
string phone::nom() const throw() {
    return _name;
}

// Cost: θ(1)
nat phone::frequencia() const throw() {
    return _compt;
}

// Cost: θ(1)
phone& phone::operator++() throw() {
    _compt++;
    return *this;
}

// Cost: θ(1)
phone phone::operator++(int) throw() {
    phone aux(*this);
    _compt++;
    return aux;
}

// Cost: θ(1)
bool phone::operator==(const phone& T) const throw() {
    bool found(false);
    if (_compt == T._compt &&
        _name == T._name)
        found = true;

    return found;
}

// Cost: θ(1)
bool phone::operator!=(const phone& T) const throw() {
    return !(*this == T);
}

// Cost: θ(name.size())
bool phone::operator>(const phone& T) const throw() {
    bool found(false);
    if (_compt > T._compt)
        found = true;
    else if (_compt == T._compt) {
        nat i = 0;
        while (_name[i] != '\0' && T._name[i] != '\0') {
            if (_name[i] < T._name[i]) {
                found = false;
                break;
            }
            else if (_name[i] > T._name[i]) {
                found = true;
                break;
            }
            i++;
        }

        /* Si els noms son iguals fins l'string mes petit,
        el mes llarg es mes gran */
        if (_name[i] == '\0' && (T._name[i] != '\0' || T._name[i] == '\0'))
            found = false;
        else if (_name[i] != '\0' && T._name[i] == '\0')
            found = true;
        
    }
    return found;
}

// Cost: θ(name.size())
bool phone::operator<(const phone& T) const throw() {
    return T > (*this);
}

// Cost: θ(name.size())
bool phone::operator<=(const phone& T) const throw() {
    return ((*this) == T || (*this < T));
}

// Cost: θ(name.size())
bool phone::operator>=(const phone& T) const throw() {
    return ((*this) == T || (*this > T));
}