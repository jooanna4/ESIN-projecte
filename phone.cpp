#include "phone.hpp"

phone::phone(nat num=0, const string& name="", nat compt=0) throw(error) {
    _num = num;
    if (name == DELETECHAR || 
        name == ENDCHAR || 
        name == ENDPREF) 
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

~phone() throw() {}

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
    _compt++;
    return *this;
}

bool phone::operator==(const phone& T) const throw() {
    bool found;
    if (_num == T._num && 
        _compt == T._compt &&
        _name == T._name)
        found = true;
    else
        found = false;
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
        int i = 0;
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
        int i = 0;
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
        int i = 0;
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
        int i = 0;
        while (i < _name.size() && found) {
            if (_name[i] != T._name[i]) 
                found = false;
            i++;
        }
    }
    return found;
}