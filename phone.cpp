#include "phone.hpp"

phone::phone(nat num, const string& name, nat compt) throw(error) {
    _num = num;
    if (name == to_string(DELETECHAR) || 
        name == to_string(ENDCHAR) || 
        name == to_string(ENDPREF)) 
        throw (ErrNomIncorrecte);
    else
        _name = name;
    _compt = compt;
}

phone::phone(const phone& T) throw(error) {
    _num = T._num;
    _name = T._name;
    _compt = T._compt;
}

phone& phone::operator=(const phone& T) throw(error) {
    _num = T._num;
    _name = T._name;
    _compt = T._compt;
    return *this;
}

phone::~phone() throw() {}

nat phone::numero() const throw() {
    return _num;
}

string phone::nom() const throw() {
    return _name;
}

nat phone::frequencia() const throw() {
    return _compt;
}

phone& phone::operator++() throw() {
    _compt++;
    return *this;
}

phone phone::operator++(int) throw() {
    phone aux(*this);
    _compt++;
    return aux;
}

bool phone::operator==(const phone& T) const throw() {
    bool found(false);
    if (_num == T._num && 
        _compt == T._compt &&
        _name == T._name)
        found = true;

    return found;
}

bool phone::operator!=(const phone& T) const throw() {
    return !(*this == T);
}

bool phone::operator>(const phone& T) const throw() {
    bool found(true);
    if (_compt < T._compt)
        found = false;
    else if (_compt == T._compt) {
        unsigned int i = 0;
        while (i < _name.size() && found) {
            if (_name[i] < T._name[i]) 
                found = false;
            i++;
        }
    }
    return found;
}

bool phone::operator<(const phone& T) const throw() {
    bool found(true);
    if (_compt > T._compt)
        found = false;
    else if (_compt == T._compt) {
        unsigned int i = 0;
        while (i < _name.size() && found) {
            if (_name[i] > T._name[i]) 
                found = false;
            i++;
        }
    }
    return found;
}

bool phone::operator<=(const phone& T) const throw() {
    bool found(true);
    if (*this > T)
        found = false;
    else if (_compt == T._compt) {
        unsigned int i = 0;
        while (i < _name.size() && found) {
            if (_name[i] != T._name[i]) 
                found = false;
            i++;
        }
    }
    return found;
}

bool phone::operator>=(const phone& T) const throw() {
    bool found(true);
    if (*this < T)
        found = false;
    else if (_compt == T._compt) {
        unsigned int i = 0;
        while (i < _name.size() && found) {
            if (_name[i] != T._name[i]) 
                found = false;
            i++;
        }
    }
    return found;
}