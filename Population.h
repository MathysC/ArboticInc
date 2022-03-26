#pragma once
#include "NoeudPop.h"

using namespace std;

template<class T>
class Population {
public:
	Population();							// Constructeur par d�faut
	~Population();							// Destructeur par d�faut

	void insererFin(const Arbre<T>&);		// Ins�rer un nouveau noeud � la fin
	void supprimer(const short int _id);	// Suppression d�un noeud
	NoeudPop<T>* valeurCourante();			// Obtention de la valeur courante

	void fixerTete();						// Fixer courant � tete
	void suivant();							// Changer courant pour le noeud suivant
	bool estDansListe();					// V�rifier si courant est dans la liste
	void trouver(const short int _id);		// Trouver un �l�ment pr�cis en fonction de l�id 

private:
	NoeudPop<T>* tete;						// Pointeur tete de liste
	NoeudPop<T>* courant;					// Pointeur courant de liste
	NoeudPop<T>* queue;						// Pointeur queue de liste
};

// Constructeur par d�faut
template<class T>
Population<T>::Population() {
	tete = nullptr;
	courant = nullptr;
	queue = nullptr;
}

// Destructeur par d�faut
template<class T>
Population<T>::~Population(){
	while (tete != nullptr)
	{
		courant = tete;
		tete = tete->suivant;
		delete courant;
	}
}

/*
* Ins�rer un Arbre � la fin de la liste
* @param _arbre : un Arbre de cellules
*/
template<class T>
void Population<T>::insererFin(const Arbre<T>& _arbre) {
	queue = queue->suivant = new NoeudPop<T>(_arbre);
}

/*
* Suppression d�un arbre de la liste cha�n�e
* @param _id : l�id recherch�
*/
template<class T>
void Population<T>::supprimer(const short int _id) {
	// Il faut tout d�abord trouver l��l�ment voulu
	if (trouver(_id)) {
		NoeudPop<T> noeudCourant = valeurCourante();
		courant->suivant = noeudCourant->suivant;

		if (queue == noeudCourant) {
			queue = courantl';'
		}
		delete noeudCourant;
	}
}

/*
* Obtenir la valeur courante du tableau
*/
template<class T>
NoeudPop<T>* Population<T>::valeurCourante() {
	return courant->suivant;
}

//TODO////////////////////////////////////////////////////////////////////////////////////////////
// Transporte le pointeur courant � la t�te de la liste
template<class T>
void Population<T>::fixerTete() {}

//TODO////////////////////////////////////////////////////////////////////////////////////////////
// Transporte le pointeur courant au noeud suivant dans la liste
template<class T>
void Population<T>::suivant() {}

//TODO////////////////////////////////////////////////////////////////////////////////////////////
// Retourne true si le pointeur courant est la liste
template<class T>
bool Population<T>::estDansListe() {}

//TODO////////////////////////////////////////////////////////////////////////////////////////////
/*
* Trouver l�id recherch� parmi les Arbres de la population
* @param _id : l�id recherch�
*/
template<class T>
void Population<T>::trouver(const short int _id) {}
