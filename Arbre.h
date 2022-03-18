#pragma once
#include "Noeud.h"
#include <string>
using namespace std;

template<class T>
class Arbre
{
public:
	Noeud<T>* racine;

	Arbre();
	bool estVide() const;
	void vider(Noeud<T>*);

	string toString(Noeud<T>*, short int);
};

// CONSTRUCTEURS DESTRUCTEURS /////////////////////////////////////////////////////////////////////

// Constructeur par d�faut
template<class T>
Arbre<T>::Arbre() { racine = nullptr; }

// GETTERS SETTERS ////////////////////////////////////////////////////////////////////////////////

// FONCTIONS //////////////////////////////////////////////////////////////////////////////////////

// Retourne True si l'arbre est vide
template <class T>
bool Arbre<T>::estVide() const { return racine == nullptr; }

/**
* Fonction r�cursive pour vider l'arbre
* Vider l'arbre � partir d'un noeud donn�
* @param _racine : un noeud de l'arbre
*/
template<class T>
void Arbre<T>::vider(Noeud<T>* _racine) {

	// La racine est vide
	if (_racine == nullptr) {
		cout << "La racine est d�j� vide.";
		return;
	}
	vider(_racine->ancGauche);
	vider(_racine->ancDroit);
	delete _racine;
}

/**
* Fonction r�cursif pour retourner l'affichage de l'arbre
* Retourner l'affichage l'arbre � partir d'un noeud donn� et d'une g�n�ration donn�e 
* @param _racine : le noeud de d�part
* @param _generation : le nombre de tiret au lancement de la fonction
*/
template<class T>
string Arbre<T>::toString(Noeud<T>* _racine,short int _generation) {
	string res = "";
	if (_racine != nullptr) {
		res += string(_generation, '-') + _racine->toString()+'\n';
		_generation++;
		res += toString(_racine->ancGauche, _generation);
		res += toString(_racine->ancDroit, _generation);
	}
	return res;
}