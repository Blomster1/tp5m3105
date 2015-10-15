#include <stdlib.h>
#include "ArbreAbstrait.h"
#include "Symbole.h"
#include "SymboleValue.h"
#include "Exceptions.h"
#include <typeinfo>

////////////////////////////////////////////////////////////////////////////////
// NoeudSeqInst
////////////////////////////////////////////////////////////////////////////////

NoeudSeqInst::NoeudSeqInst() : m_instructions() {
}

int NoeudSeqInst::executer() {
    for (unsigned int i = 0; i < m_instructions.size(); i++)
        m_instructions[i]->executer(); // on exécute chaque instruction de la séquence
    return 0; // La valeur renvoyée ne représente rien !
}

void NoeudSeqInst::ajoute(Noeud* instruction) {
    if (instruction != nullptr) m_instructions.push_back(instruction);
}

////////////////////////////////////////////////////////////////////////////////
// NoeudAffectation
////////////////////////////////////////////////////////////////////////////////

NoeudAffectation::NoeudAffectation(Noeud* variable, Noeud* expression)
: m_variable(variable), m_expression(expression) {
}

int NoeudAffectation::executer() {
    int valeur = m_expression->executer(); // On exécute (évalue) l'expression
    ((SymboleValue*) m_variable)->setValeur(valeur); // On affecte la variable
    return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudOperateurBinaire
////////////////////////////////////////////////////////////////////////////////

NoeudOperateurBinaire::NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit)
: m_operateur(operateur), m_operandeGauche(operandeGauche), m_operandeDroit(operandeDroit) {
}

int NoeudOperateurBinaire::executer() {
    int og, od, valeur;
    if (m_operandeGauche != nullptr) og = m_operandeGauche->executer(); // On évalue l'opérande gauche
    if (m_operandeDroit != nullptr) od = m_operandeDroit->executer(); // On évalue l'opérande droit
    // Et on combine les deux opérandes en fonctions de l'opérateur
    if (this->m_operateur == "+") valeur = (og + od);
    else if (this->m_operateur == "-") valeur = (og - od);
    else if (this->m_operateur == "*") valeur = (og * od);
    else if (this->m_operateur == "==") valeur = (og == od);
    else if (this->m_operateur == "!=") valeur = (og != od);
    else if (this->m_operateur == "<") valeur = (og < od);
    else if (this->m_operateur == ">") valeur = (og > od);
    else if (this->m_operateur == "<=") valeur = (og <= od);
    else if (this->m_operateur == ">=") valeur = (og >= od);
    else if (this->m_operateur == "et") valeur = (og && od);
    else if (this->m_operateur == "ou") valeur = (og || od);
    else if (this->m_operateur == "non") valeur = (!og);
    else if (this->m_operateur == "/") {
        if (od == 0) throw DivParZeroException();
        valeur = og / od;
    }
    return valeur; // On retourne la valeur calculée
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstSi
////////////////////////////////////////////////////////////////////////////////

NoeudInstSi::NoeudInstSi(Noeud* conditionSi, Noeud* sequenceSi, vector<Noeud*> vecteurConditionSinonsi, vector<Noeud*> vecteurSequenceSinonsi, Noeud* sequenceSinon)
: m_conditionSi(conditionSi), m_sequenceSi(sequenceSi), m_vecteurConditionSinonsi(vecteurConditionSinonsi), m_vecteurSequenceSinonsi(vecteurSequenceSinonsi), m_sequenceSinon(sequenceSinon) {
}

int NoeudInstSi::executer() {
    int i = 0;
    bool cond = false;
    if (m_conditionSi->executer()) {
        m_sequenceSi->executer();
    } else {
        while (!cond && i < m_vecteurConditionSinonsi.size()) {
            if (m_vecteurConditionSinonsi[i]->executer()) {
                m_vecteurSequenceSinonsi[i]->executer();
                cond = true;
            } else {
                i++;
            }
        }
        
        if (!cond && m_sequenceSinon != nullptr) {
            m_sequenceSinon->executer();
        }
    }

    return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstTantQue
////////////////////////////////////////////////////////////////////////////////

NoeudInstTantque::NoeudInstTantque(Noeud* condition, Noeud* sequence)
: m_condition(condition), m_sequence(sequence) {
}

int NoeudInstTantque::executer() {
    while (m_condition->executer()) {
        m_sequence->executer();
    }
    return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstRepeter
////////////////////////////////////////////////////////////////////////////////

NoeudInstRepeter::NoeudInstRepeter(Noeud* condition, Noeud* sequence)
: m_condition(condition), m_sequence(sequence) {
}

int NoeudInstRepeter::executer() {
    while (!m_condition->executer()) m_sequence->executer();
    return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstPour
////////////////////////////////////////////////////////////////////////////////

NoeudInstPour::NoeudInstPour(Noeud* initialisation, Noeud* condition, Noeud* incrementation, Noeud* sequence)
: m_initialisation(initialisation), m_condition(condition), m_incrementation(incrementation), m_sequence(sequence) {
}

int NoeudInstPour::executer() {
    for (m_initialisation->executer(); m_condition->executer(); m_incrementation->executer()) m_sequence->executer();
    return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstEcrire
////////////////////////////////////////////////////////////////////////////////

NoeudInstEcrire::NoeudInstEcrire(vector <Noeud*> vecteur)
: m_vecteur(vecteur) {
}

int NoeudInstEcrire::executer() {
    for (unsigned int i = 0; i < m_vecteur.size(); i++) {
        if (typeid (*m_vecteur[i]) == typeid (SymboleValue)) {
            if (*((SymboleValue*) m_vecteur[i]) == "<CHAINE>") {
                cout << ((SymboleValue*) m_vecteur[i])->getChaine().substr(1, ((SymboleValue*) m_vecteur[i])->getChaine().size() - 2);
            } else {
                cout << " " << ((SymboleValue*) m_vecteur[i])->executer();
            }
        } else {
            cout << ((Noeud*) m_vecteur[i])->executer();
        }
    }
    cout << "\n";
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstLire
////////////////////////////////////////////////////////////////////////////////

NoeudInstLire::NoeudInstLire(vector<Noeud*> vecteur)
: m_vecteur(vecteur) {
}

int NoeudInstLire::executer() {
    for (unsigned int i = 0; i < m_vecteur.size(); i++) {
        int var_temp;
        cout << "Saisir " << ((SymboleValue*) m_vecteur[i])->getChaine() << " : ";
        cin >> var_temp;
        ((SymboleValue*) m_vecteur[i])->setValeur(var_temp);
    }
    return 0;
}