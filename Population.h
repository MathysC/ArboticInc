#pragma once
#include "NoeudPop.h"
using namespace std;

template<class T>
class Population {
public:
	Population();														// Constructeur par d�faut
	~Population();														// Destructeur par d�faut

	void insererFin(const Arbre<T>&);									// Ins�rer un nouveau noeud � la fin
	void supprimer(const short int _id);								// Suppression d�un noeud
	NoeudPop<T>* valeurCourante();										// Obtention de la valeur courante

	void fixerTete();													// Fixer courant � tete
	void suivant();														// Changer courant pour le noeud suivant
	bool estDansListe();												// V�rifier si courant est dans la liste
	bool trouver(const short int _id);									// Trouver un �l�ment pr�cis en fonction de l�id 
	
	short int ancetreCommun(const short int, const short int);			// Trouver l�anc�tre commun
	short int aideAncetreCommun(Arbre<T>& _premier, Arbre<T>& _second);	// Fonction r�cursive pour trouver un ancetre commun
	short int * enfantCommun(const short int, const short int);			// Trouver l�enfant commun
	void ancetreETenfantCommuns(const short int, const short int);		// Afficher les informations pour l�anc�tre et l�enfant en commun

	string toStringIndividu(const short int _id);						// Obtenir la repr�sentation textuelle d�un arbre
private:
	NoeudPop<T>* tete;													// Pointeur tete de liste
	NoeudPop<T>* courant;												// Pointeur courant de liste
	NoeudPop<T>* queue;													// Pointeur queue de liste
};

// CONSTRUCTEURS DESTRUCTEURS /////////////////////////////////////////////////////////////////////

// Constructeur par d�faut
template<class T>
Population<T>::Population() {
	tete = courant = queue = new NoeudPop<T>();
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

// FONCTIONS //////////////////////////////////////////////////////////////////////////////////////

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
	// Il faut supprimer cet id parmi les anc�tres gauches et droits de tous les arbres
	for (fixerTete(); estDansListe(); suivant()) {
		// On r�cup�re la valeur courante
		NoeudPop<T>* noeudCourant = valeurCourante();
		Arbre<T> arbreCourant = valeurCourante()->arbre;
		// On v�rifie qu�il y a un anc�tre � gauche et puis on v�rifie si c�est l�id que l�on recherche
		if (arbreCourant.racine->ancGauche != nullptr && arbreCourant.racine->ancGauche->getID() == _id) {
			arbreCourant.racine->ancGauche = nullptr;
		}
		// On v�rifie qu�il y a un anc�tre � droite et puis on v�rifie si c�est l�id que l�on recherche
		if (arbreCourant.racine->ancDroit != nullptr && noeudCourant->arbre.racine->ancDroit->getID() == _id) {
			noeudCourant->arbre.racine->ancDroit = nullptr;
		}
	}

	// On replace le pointeur courant sur le noeud � supprimer
	trouver(_id);
	// Il faut tout d�abord trouver l��l�ment voulu
	if (trouver(_id)) {
		NoeudPop<T> * noeudCourant = valeurCourante();
		this->courant->suivant = noeudCourant->suivant;

		if (queue == noeudCourant) {
			queue = courant;
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

// Transporte le pointeur courant � la t�te de la liste
template<class T>
void Population<T>::fixerTete() {
	courant = tete;
}

// Transporte le pointeur courant au noeud suivant dans la liste
template<class T>
void Population<T>::suivant() {
	if(courant != nullptr) courant = courant->suivant;
}

// Retourne true si le pointeur courant est la liste
template<class T>
bool Population<T>::estDansListe() {
	return (courant != nullptr) && (courant->suivant != nullptr);
}

/*
* Trouver l�id recherch� parmi les Arbres de la population
* @param _id : l�id recherch�
* @returns true d�s que le pointeur courant est sur l�arbre dont la racine a l�ID = _id.
* false d�s que la liste est parcourue sans plus de r�sultat.
*/
template<class T>
bool Population<T>::trouver(const short int _id) {
	// On parcours toute la liste
	for (fixerTete(); estDansListe(); suivant()) {
		// On r�cup�re la valeur courante
		NoeudPop<T>* noeudCourant = valeurCourante();
		// On v�rifie l�id courant
		if (noeudCourant->arbre.racine->getID() == _id) {
			return true;
		}
	}
	// Aucun r�sultat, on renvoit false.
	return false;
}

/*
* Fonction permettant de trouver l�anc�tre commun de deux individus
* @param _premierID : l�id du premier individu
* @param _secondID : l�id du second individu
* @returns l�id de l�anc�tre en commun
*/
template<class T>
short int Population<T>::ancetreCommun(const short int _premierID, const short int _secondID) {
	Arbre<T> premier = Arbre<T>();
	Arbre<T> second = Arbre<T>();

	// R�cup�ration des deux �lements
	if (trouver(_premierID)) {
		premier = valeurCourante()->arbre;
	}
	else {
		cout << "L�individu " << to_string(_premierID) << " n�a pas �t� trouv�." << endl;
		cout << "Fin de la recherche." << endl; 
		return false;
	}
	if (trouver(_secondID)) {
		second = valeurCourante()->arbre;
	}
	else {
		cout << "L�individu " << to_string(_secondID) << " n�a pas �t� trouv�." << endl;
		cout << "Fin de la recherche." << endl;
		return false;
	}

	// On poss�de les deux arbres, il faut trouver l�anc�tre commun
	return aideAncetreCommun(premier, second);
}

/*
* Fonction r�cursive pour trouver un anc�tre commun � partir de deux arbres donn�s
* @param _premierID : l�arbre qui sera inspecter noeud par noeud.
* @param _secondID : l�arbre qui sera parcouru � chaque recherche.
* @returns un nombre n�gatif dans le cas o� il n�y a pas d�anc�tre commun
* sinon l�id de l�anc�tre commun
*/
template<class T>
short int Population<T>::aideAncetreCommun(Arbre<T>& _premier, Arbre<T>& _second) {
	// V�rifier que l�arbre ne soit pas vide premi�rement
	if (_premier.estVide()) return -1;

	// Chercher l�id dans le second arbre
	if (_second.recherche(_premier.racine->getID()) <= 0) {
		// Si non trouv�

		short int estGauche = -1, estDroit =-1;
		// On cherche avec l�anc�tre gauche
		if (_premier.racine->ancGauche != nullptr) {
			// On r�cup�re l�anc�tre de gauche
			if (trouver(_premier.racine->ancGauche->getID())) {
				Arbre<T>& gauche = valeurCourante()->arbre;
				// On cherche � gauche
				estGauche = aideAncetreCommun(gauche, _second);
			}
		}

		// Puis si on ne l�a pas trouv� � gauche, on cherche avec l�anc�tre droit.
		if (_premier.racine->ancDroit != nullptr && estGauche < 0) {
			// On r�cup�re l�anc�tre de droit
			if (trouver(_premier.racine->ancDroit->getID())) {
				Arbre<T>& droit = valeurCourante()->arbre;
				// On cherche � droite
				estDroit = aideAncetreCommun(droit, _second);
				// Peu importe le r�sultat, apr�s avoir cherch� � droite, on arr�te la recherche
				return estDroit;
			}
		}
		// Si on a trouv� � gauche
		return estGauche; 

	// On a trouv� un r�sultat 
	} else {
		return _premier.racine->getID();
	}
}

/*
* Fonction permettant de trouver l�enfant commun de deux individus
* @param _premierID : l�id du premier individu
* @param _secondID : l�id du second individu
* @returns l�id de l�enfant en commun et la diff�rence de g�n�ration entre les deux id _premierID et _secondID
*/
template<class T>
short int * Population<T>::enfantCommun(const short int _premierID, const short int _secondID) {
	
	static short int infoEnfant[2];
	infoEnfant[0] = -1; // enfant
	infoEnfant[1] = -1; // diff�rence de g�n�ration
	// On poss�de les deux individus : Il faut trouver l�arbre dans lequel les deux individus appara�ssent.
	for (fixerTete(); estDansListe(); suivant()) {
		Arbre<T> tmp = valeurCourante()->arbre;
		short int genPremier = tmp.recherche(_premierID);

		// Si on trouve le premier individu, on peut cherche le second
		// Sinon il est inutile de faire cette recherche, on passe au noeud suivant
		if (genPremier >= 0) {
			short int genSecond = tmp.recherche(_secondID);
			// Si le second �l�ment est trouv�
			if (genSecond >= 0) {
				// On retient l�id de l�arbre
				infoEnfant[0] = tmp.racine->getID();

				// On calcule la diff�rence de g�n�ration
				if (genPremier > genSecond) {
					infoEnfant[1] = genPremier - genSecond;
				}
				else {
					infoEnfant[1] = genSecond - genPremier;
				}
				// On arr�te les recherches ici.
				break;
			}
		}

	}

	return infoEnfant;
}

/*
* Afficher les informations sur l�anc�tre et l�enfant en commun pour deux individus
* @param _premierID : le premier individu � utiliser pour les recherches
* @param _secondID : le second individu � utiliser pour les recherches
*/
template<class T>
void Population<T>::ancetreETenfantCommuns(const short int _premierID, const short int _secondID) {
	cout << "Pour les individus " << to_string(_premierID) << " et " << to_string(_secondID) << ":" << endl;

	// Anc�tre en commun
	short int anc = ancetreCommun(_premierID, _secondID);
	if (anc >= 0) {
		cout << " - Il existe un anc�tre commun qui est " << to_string(anc) << "." << endl;
	}
	// Si aucun anc�tre commun
	else {
		cout << " - Il n�existe aucun anc�tre commun." << endl;
	}

	// Enfant en commun
	short int * infoEnfant= enfantCommun(_premierID, _secondID);
	// Afficher la diff�rence de g�n�ration entre les deux individus
	if (*infoEnfant >= 0) {
		cout << " - Il existe un enfant commun qui est " << to_string(*infoEnfant) << "." << endl;
		cout << " - Il y a une diff�rence de g�n�ration de " << to_string(*(infoEnfant+1)) << "." << endl;
	}
	// Si aucun arbre ne poss�de les deux individus
	else {
		cout << " - Il n�existe aucun enfant commun." << endl;
	}
}

/*
* Fonction renvoyant la repr�sentation textuelle d�un individu faisant partie de cette population
* @param _id : l�id d�un individu
* @returns le string de l�arborescence d�un individu ou un message d�erreur.
*/
template<class T>
string Population<T>::toStringIndividu(const short int _id) {
	if (trouver(_id)) {
		return valeurCourante()->arbre.toString();
	}
	else {
		return "Cet individu ne fait pas partie de cette population.";
	}
}