#pragma once
#include "Noeud.h"
#include <string>
using namespace std;

template<class T>
class Arbre
{
public:
	Noeud<T>* racine;													// Le noeud racine de l�arbre

	Arbre();															// Constructeur par d�faut
	~Arbre();															// Destructeur par d�faut
	bool estVide() const;												// Fonction v�rifiant si l�arbre est vide
	void viderArbre();													// Fonction initiant la suppression de l�arbre
	void aideVider(Noeud<T>*);											// Fonction r�cursive pour vider l�arbre

	short int recherche(const short int& _id);							// Fonction initiant la recherche
	bool aideRecherche(Noeud<T>*, const short int&, short int&);		// Fonction r�cursive de recherche
	string toString(Noeud<T>*, short int);								// Repr�sentation textuelle de l�arbre
};

// CONSTRUCTEURS DESTRUCTEURS /////////////////////////////////////////////////////////////////////

// Constructeur par d�faut
template<class T>
Arbre<T>::Arbre() { racine = nullptr; }


template<class T>
Arbre<T>::~Arbre() { viderArbre(); }

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
void Arbre<T>::aideVider(Noeud<T>* _racine) {

	// La racine est vide
	//if (_racine == nullptr) {
	//	cout << "La racine est d�j� vide." << endl;
	//	return;
	//}
	//aideVider(_racine->ancGauche);
	//aideVider(_racine->ancDroit);
	//if (_racine != racine) {
	//	cout << _racine->getID() << endl;
	//	delete _racine;
	//}
}

// Vider l'arbre
template<class T>
void Arbre<T>::viderArbre() {
	aideVider(racine);
	racine = nullptr;
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
		// Obtenir les valeurs de la cellule de ce Noeud
		res += string(_generation, '-') + _racine->toString()+'\n';
		_generation++;
		
		// Obtenir les valeurs de la cellule de l'anc�tre Gauche
		res += toString(_racine->ancGauche, _generation);

		// Obtenir les valeurs de la cellule de l'anc�tre Droit
		res += toString(_racine->ancDroit, _generation);
	}
	return res;
}

/*
* Fonction r�cursif de recherche avec parcours pr�fixe d�arbre
* @param _racine : le noeud courant
* @param _id : l�id recherch�
* @param _generation : la g�n�ration courante
* @param true si l�id recherch� est trouv�, 
* la g�neration est modifi�e en cons�quence du r�sultat de la recherche : 
* - La g�n�ration o� se trouve l�id trouv�.
* - un short int n�gatif si la recherche �choue
*/
template<class T>
bool Arbre<T>::aideRecherche(Noeud<T>* _racine, const short int& _id, short int& _generation) {
	// Si ce noeud poss�de le bon id :
	if (_racine == nullptr) return false; // Si on arrive � une feuille, on annule la recherche
	if (_racine->getID() == _id) return true; // Si on arrive � l�ID recherch�, on valide la recherche

	// Sinon on visite ses anc�tres :
	_generation++; // visiter les anc�tres signifie changer de g�n�ration
	bool isGauche = aideRecherche(_racine->ancGauche,_id,_generation); // On cherche du c�t� gauche

	// S�il n�est pas du c�t� gauche
	if (!isGauche) {
		// On cherche du c�t� droit
		bool isDroit = aideRecherche(_racine->ancDroit, _id, _generation);
		// On renvoit le r�sultat du c�t� droit 
		return isDroit;
	}
	// Si l�ID est du c�t� gauche, on renvoit true
	else return isGauche;
}

/*
* Fonction de recherche dans l�arbre de l�id en param�tre
* @param _id : l�id recherch�
* @returns generation : un nombre positif correspond � la g�n�ration o� se trouve l�id recherch� dans l�arbre
* un nombre n�gatif dans le cas d��chec de la recherche
*/
template<class T>
short int Arbre<T>::recherche(const short int& _id) {
	// La recherche depuis la racine signifie la g�n�ration actuelle, donc 0
	short int generation = 0;
	// Si un r�sultat est trouv� on renvoit la g�n�ration correspondante
	if (aideRecherche(racine, _id, generation)) {
		return generation;
	} else {
		// Sinon on renvoit un short int n�gatif indiquant l��chec de la recherche 
		return -1;
	}
}