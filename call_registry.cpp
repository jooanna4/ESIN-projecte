#include "call_registry.hpp"

// Metodes privats
static int call_registry::altura(node *n) {
    
}
static int call_registry::factor_equilibri(node *n) {

}

// Metodes publics
call_registry::call_registry() throw(error);

call_registry::call_registry(const call_registry& R) throw(error);
call_registry& call_registry::operator=(const call_registry& R) throw(error);
call_registry::~call_registry() throw();

void call_registry::registra_trucada(nat num) throw(error);

void call_registry::assigna_nom(nat num, const string& name) throw(error);

void call_registry::elimina(nat num) throw(error);

bool call_registry::conte(nat num) const throw();

string call_registry::nom(nat num) const throw(error);

nat call_registry::num_trucades(nat num) const throw(error);

bool call_registry::es_buit() const throw();

nat call_registry::num_entrades() const throw();

void call_registry::dump(vector<phone>& V) const throw(error);