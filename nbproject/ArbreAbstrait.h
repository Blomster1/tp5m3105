#ifndef ARBREABSTRAIT_H
#define ARBREABSTRAIT_H

// Contient toutes les déclarations de classes nécessaires
//  pour représenter l'arbre abstrait

#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Symbole.h"
#include "Exceptions.h"

////////////////////////////////////////////////////////////////////////////////

class Noeud {
    // Classe abstraite dont dériveront toutes les classes servant à représenter l'arbre abstrait
    // Remarque : la classe ne contient aucun constructeur
public:
    virtual int executer() = 0; // Méthode pure (non implémentée) qui rend la classe abstraite

    virtual void ajoute(Noeud* instruction) {
        throw OperationInterditeException();
    }

    virtual ~Noeud() {
    } // Présence d'un destructeur virtuel conseillée dans les classes abstraites
    
    virtual void traduitEnCPP(ostream & cout, unsigned int indentation) const = 0;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudSeqInst : public Noeud {
    // Classe pour représenter un noeud "sequence d'instruction"
    //  qui a autant de fils que d'instructions dans la séquence
public:
    NoeudSeqInst(); // Construit une séquence d'instruction vide

    ~NoeudSeqInst() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute chaque instruction de la séquence
    void ajoute(Noeud* instruction); // Ajoute une instruction à la séquence
    void traduitEnCPP(ostream & cout, unsigned int indentation) const;

private:
    vector<Noeud *> m_instructions; // pour stocker les instructions de la séquence
};

////////////////////////////////////////////////////////////////////////////////

class NoeudAffectation : public Noeud {
    // Classe pour représenter un noeud "affectation"
    //  composé de 2 fils : la variable et l'expression qu'on lui affecte
public:
    NoeudAffectation(Noeud* variable, Noeud* expression); // construit une affectation

    ~NoeudAffectation() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute (évalue) l'expression et affecte sa valeur à la variable
    void traduitEnCPP(ostream & cout, unsigned int indentation) const;

private:
    Noeud* m_variable;
    Noeud* m_expression;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudOperateurBinaire : public Noeud {
    // Classe pour représenter un noeud "opération binaire" composé d'un opérateur
    //  et de 2 fils : l'opérande gauche et l'opérande droit
public:
    NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit);
    // Construit une opération binaire : operandeGauche operateur OperandeDroit

    ~NoeudOperateurBinaire() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute (évalue) l'opération binaire)
    void traduitEnCPP(ostream & cout, unsigned int indentation) const;

private:
    Symbole m_operateur;
    Noeud* m_operandeGauche;
    Noeud* m_operandeDroit;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudInstSi : public Noeud {
    // Classe pour représenter un noeud "instruction si"
    //  et ses 2 fils : la condition du si et la séquence d'instruction associée
public:
    NoeudInstSi(Noeud* conditionSi, Noeud* sequenceSi, vector<Noeud*> vecteurConditionSinonsi, vector<Noeud*> vecteurSequenceSinonsi, Noeud* sequenceSinon);
    // Construit une "instruction si" avec sa condition et sa séquence d'instruction

    ~NoeudInstSi() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute l'instruction si : si condition vraie on exécute la séquence
    void traduitEnCPP(ostream & cout, unsigned int indentation) const;

private:
    Noeud* m_conditionSi;
    Noeud* m_sequenceSi;
    vector<Noeud*> m_vecteurConditionSinonsi;
    vector<Noeud*> m_vecteurSequenceSinonsi;
    Noeud* m_sequenceSinon;
};

///////////////////////////////////////////////////////////////////////////////

class NoeudInstTantque : public Noeud {
    //Classe pour representer un noeud "instruction tant que"
    //  et ses 2 fils : la condition du repeter et la séquence d'instruction associée
public:
    NoeudInstTantque(Noeud* condition, Noeud* sequence);
    // Construit une "instruction tant que" avec sa condition et sa séquence d'instruction
    
    ~NoeudInstTantque() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute l'instruction tant que : tant que la condition est vraie, on fait la séquence
    void traduitEnCPP(ostream & cout, unsigned int indentation) const;

private:
    Noeud* m_condition;
    Noeud* m_sequence;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudInstRepeter : public Noeud {
    // Classe pour représenter un noeud "instruction repeter"
    //  et ses 2 fils : la condition du repeter et la séquence d'instruction associée
public:
    NoeudInstRepeter(Noeud* condition, Noeud* sequence);
    // Construit une "instruction repeter" avec sa condition et sa séquence d'instruction

    ~NoeudInstRepeter() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute l'instruction repeter : repeter la séquence jusqu'à ce que la condition soit vraie
    void traduitEnCPP(ostream & cout, unsigned int indentation) const;

private:
    Noeud* m_condition;
    Noeud* m_sequence;
};

///////////////////////////////////////////////////////////////////////////////

class NoeudInstPour : public Noeud {
    //Classe pour representer un noeud "instruction pour"
    //  et ses 4 fils : l'initialisation de la variable incrémentée, la condition d'incrémentation, l'incrémentation et la séquence d'instruction
public:
    NoeudInstPour(Noeud* initialisation, Noeud* condition, Noeud* incrementation, Noeud* sequence);
    // Construit une "instruction pour" avec son initialisation, sa condition, son incrémentation et sa séquence d'instruction
    
    ~NoeudInstPour() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute l'instruction pour : pour la variable donnée, tant que la condition est fausse, on incrémente la variable et on fait la séquence
    void traduitEnCPP(ostream & cout, unsigned int indentation) const;

private:
    Noeud* m_initialisation;
    Noeud* m_condition;
    Noeud* m_incrementation;
    Noeud* m_sequence;
};

///////////////////////////////////////////////////////////////////////////////

class NoeudInstEcrire : public Noeud {
    //Classe pour representer un noeud "instruction ecrire"
    // et son fils : le vecteur à ecrire
public:
    NoeudInstEcrire(vector<Noeud*> vecteur);
    // Construit une "instruction ecrire" avec son vecteur

    ~NoeudInstEcrire() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute l'instruction ecrire : ecrit le vecteur
    void traduitEnCPP(ostream & cout, unsigned int indentation) const;

private:
    vector<Noeud*> m_vecteur;
};

///////////////////////////////////////////////////////////////////////////////

class NoeudInstLire : public Noeud {
    //Classe pour representer un noeud "instruction lire"
    //  et son fils : le vecteur à lire
public:
    NoeudInstLire(vector<Noeud*> vecteur);
    // Construit une "instruction lire" avec son vecteur
    
    ~NoeudInstLire() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute l'instruction lire : lit le vecteur
    void traduitEnCPP(ostream & cout, unsigned int indentation) const;

private:
    vector<Noeud*> m_vecteur;
};

#endif /* ARBREABSTRAIT_H */