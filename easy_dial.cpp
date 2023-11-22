#include "easy_dial.hpp"

easy_dial::easy_dial(const call_registry& R) throw(error) {

}

easy_dial::easy_dial(const easy_dial& D) throw(error) {

}

easy_dial& easy_dial::operator=(const easy_dial& D) throw(error) {
    return *this;
}

easy_dial::~easy_dial() throw() {

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
    return 1;
}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error) {

}

double easy_dial::longitud_mitjana() const throw() {
    return 1;
}