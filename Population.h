#pragma once
#include "NoeudPop.h"
#include "Noeud.h"
using namespace std;

template<class T>
class Population {
public:
	Population();														// Constructeur par d�faut.
	~Population();														// Destructeur par d�faut.

	void fixerTete();													// Fixer courant � tete.
	void suivant();														// Changer courant pour le noeud suivant.
	bool estDansListe();												// V�rifier si courant est dans la liste.
	short int longueur();												// Obtenir le nombre d�individus.

	bool trouver(const short int);										// Trouver un �l�ment pr�cis en fonction de l�id.
	NoeudPop<T>* valeurCourante();										// Obtention de la valeur courante.

	void generer(const short int _nb);									// G�n�rer un certain nombre d�individus.
	void insererFin(T&);												// Ins�rer un nouvel individu.
	void supprimer(const short int _id);								// Suppression d�un noeud.

	short int ancetreCommun(const short int, const short int);			// Trouver l�anc�tre commun.
	short int * enfantCommun(const short int, const short int);			// Trouver l�enfant commun.
	void ancetreETenfantCommuns(const short int, const short int);		// Afficher les informations pour l�anc�tre et l�enfant en commun.

	string toStringIndividu(const short int _id);						// Obtenir la repr�sentation textuelle d�un arbre.

	// Ces fonctions devraient �tre private mais pour les test, elles doivent �tre accessible public//
	short int getNextID();												// Obtenir le prochain id � utiliser.
	void insererFin(Noeud<T>*);											// Inserer un noeud.

private:
	NoeudPop<T>* tete;													// Pointeur tete de liste.
	NoeudPop<T>* courant;												// Pointeur courant de liste.
	NoeudPop<T>* queue;													// Pointeur queue de liste.
	short int nextID;													// Le prochain ID � utiliser.
	
	void insererFin(const Arbre<T>&);									// Ins�rer un nouveau noeud � la fin.

	short int aideAncetreCommun(Arbre<T>& _premier, Arbre<T>& _second);	// Fonction r�cursive pour trouver un ancetre commun.
	void aideGenerer();													// Fonction g�n�rant un nouvel individu.

};

// CONSTRUCTEURS DESTRUCTEURS /////////////////////////////////////////////////////////////////////

// Constructeur par d�faut.
template<class T>
Population<T>::Population() {
	tete = courant = queue = new NoeudPop<T>();
	nextID = 1;
}

// Destructeur par d�faut.
template<class T>
Population<T>::~Population(){
	while (tete != nullptr)
	{
		courant = tete;
		tete = tete->suivant;
		delete courant;
	}
}

// GETTERS SETTERS ////////////////////////////////////////////////////////////////////////////////

/*
* Getter du prochain ID � utiliser.
* La variable nextID est incr�ment� de 1 � chaque appel de la fonction.
* @returns le prochain ID � utiliser.
*/
template<class T>
short int Population<T>::getNextID() {
	nextID++;
	return nextID;
}

/*
* Getter de la longueur de la Population. Soit le nombre d�individus qui la compose.
* @returns Le nombre total d�individus.
*/
template<class T>
short int Population<T>::longueur() {
	short int compteur = 0;
	for (fixerTete(); estDansListe(); suivant()) {
		compteur++;
	}
	return compteur;
}

// FONCTIONS //////////////////////////////////////////////////////////////////////////////////////

// INSERER SUPPRIMER

/*
* Ins�rer un Arbre � la fin de la liste.
* @param _arbre : un Arbre de cellules.
*/
template<class T>
void Population<T>::insererFin(const Arbre<T>& _arbre) {
	queue = queue->suivant = new NoeudPop<T>(_arbre);
}

/*
* Ins�rer une cellule en tant qu�individu.
* @param _cell : la cellule � ins�rer dans la population.
*/
template<class T>
void Population<T>::insererFin(T& _cell) {
	Noeud<T>* newNoeud = new Noeud<ColorCell>(getNextID(), _cell);
	this->insererFin(Arbre<T>(newNoeud));
}

/* 
* Ins�rer un noeud en tant qu�individu.
* @param _noeud : le noeud � ins�rer dans la population.
*/
template<class T>
void Population<T>::insererFin(Noeud<T>* _noeud) {
	insererFin(Arbre<T>(_noeud));
}

/*
* Suppression d�un arbre de la liste cha�n�e.
* @param _id : l�id recherch�.
*/
template<class T>
void Population<T>::supprimer(const short int _id) {
	// Il faut supprimer cet id parmi les anc�tres gauches et droits de tous les arbres
	for (fixerTete(); estDansListe(); suivant()) {
		// On r�cup�re la valeur courante
		NoeudPop<T>* nCourant = valeurCourante();
		// On v�rifie qu�il y a un anc�tre � cellG et puis on v�rifie si c�est l�id que l�on recherche
		if (nCourant->getR_Anc_Gauche() != nullptr && nCourant->getR_Anc_Gauche()->getID() == _id) {
			// getR() et non getR_Anc_Gauche afin de pouvoir modifier la valeur
			nCourant->getR()->ancGauche = nullptr;
		}
		// On v�rifie qu�il y a un anc�tre � cellD et puis on v�rifie si c�est l�id que l�on recherche
		if (nCourant->getR_Anc_Droit() != nullptr && nCourant->getR_Anc_Droit()->getID() == _id) {
			// getR() et non getR_Anc_Droit afin de pouvoir modifier la valeur
			nCourant->getR()->ancDroite = nullptr;
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

// OP�RATIONS BASIQUES

/*
* Obtenir la valeur courante du tableau.
* @returns le pointeur suivant.
*/
template<class T>
NoeudPop<T>* Population<T>::valeurCourante() {
	return courant->suivant;
}

// Transporte le pointeur courant � la t�te de la liste.
template<class T>
void Population<T>::fixerTete() {
	courant = tete;
}

// Transporte le pointeur courant au noeud suivant dans la liste.
template<class T>
void Population<T>::suivant() {
	if(courant != nullptr) courant = courant->suivant;
}

/*
* V�rifie que le pointeur courant est la liste.
* @returns true si le pointeur courant est dans la liste.
*/
template<class T>
bool Population<T>::estDansListe() {
	return (courant != nullptr) && (courant->suivant != nullptr);
}

/*
* Trouver l�id recherch� parmi les Arbres de la population.
* @param _id :	l�id recherch�.
* @returns		true d�s que le pointeur courant est sur l�arbre dont la racine a l�ID = _id.
*				false d�s que la liste est parcourue sans plus de r�sultat.
*/
template<class T>
bool Population<T>::trouver(const short int _id) {
	// On parcours toute la liste
	for (fixerTete(); estDansListe(); suivant()) {
		// On r�cup�re la valeur courante
		NoeudPop<T>* noeudCourant = valeurCourante();
		// On v�rifie l�id courant
		if (noeudCourant->arbre.getR_ID() == _id) {
			return true;
		}
	}
	// Aucun r�sultat, on renvoit false.
	return false;
}

// FONCTIONS ARBOTIC

/*
* Fonction permettant de trouver l�anc�tre commun de deux individus.
* @param _premierID :	l�id du premier individu.
* @param _secondID :	l�id du second individu.
* @returns				l�id de l�anc�tre en commun.
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
* Fonction r�cursive pour trouver un anc�tre commun � partir de deux arbres donn�s.
* @param _premierID :	l�arbre qui sera inspecter noeud par noeud.
* @param _secondID :	l�arbre qui sera parcouru � chaque recherche.
* @returns				un nombre n�gatif dans le cas o� il n�y a pas d�anc�tre commun.
*						sinon l�id de l�anc�tre commun.
*/
template<class T>
short int Population<T>::aideAncetreCommun(Arbre<T>& _premier, Arbre<T>& _second) {
	// V�rifier que l�arbre ne soit pas vide premi�rement
	if (_premier.estVide()) return -1;

	// Chercher l�id dans le second arbre
	if (_second.recherche(_premier.getR_ID()) <= 0) {
		// Si non trouv�

		short int estGauche = -1, estDroit =-1;
		// On cherche avec l�anc�tre cellG
		if (_premier.getR_Anc_Gauche() != nullptr) {
			// On r�cup�re l�anc�tre de cellG
			if (trouver(_premier.getR_Anc_Gauche()->getID())) {
				Arbre<T>& gauche = valeurCourante()->arbre;
				// On cherche � cellG
				estGauche = aideAncetreCommun(gauche, _second);
			}
		}

		// Puis si on ne l�a pas trouv� � cellG, on cherche avec l�anc�tre droit.
		if (_premier.getR_Anc_Droit() != nullptr && estGauche < 0) {
			// On r�cup�re l�anc�tre de droit
			if (trouver(_premier.getR_Anc_Droit()->getID())) {
				Arbre<T>& droit = valeurCourante()->arbre;
				// On cherche � cellD
				estDroit = aideAncetreCommun(droit, _second);
				// Peu importe le r�sultat, apr�s avoir cherch� � cellD, on arr�te la recherche
				return estDroit;
			}
		}
		// Si on a trouv� � cellG
		return estGauche; 

	// On a trouv� un r�sultat 
	} else {
		return _premier.getR_ID();
	}
}

/*
* Fonction permettant de trouver l�enfant commun de deux individus.
* @param _premierID :	l�id du premier individu.
* @param _secondID :	l�id du second individu.
* @returns				l�id de l�enfant en commun et la diff�rence de g�n�ration 
						entre les deux id _premierID et _secondID.
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
				infoEnfant[0] = tmp.getR_ID();

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
* Afficher les informations sur l�anc�tre et l�enfant en commun pour deux individus.
* @param _premierID :	le premier individu � utiliser pour les recherches.
* @param _secondID :	le second individu � utiliser pour les recherches.
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
* Fonction appellant un nombre de fois param�tr� la g�n�ration d�un nouvel individu.
* @param _nb : le nombre de nouveaux individus � g�n�rer.
*/
template<class T>
void Population<T>::generer(const short int _nb) {
	for (short int i = 0; i < _nb; i++) {
		aideGenerer();
	}
}

// Fonction permettant de g�n�rer un nouvel individu � partir de deux parents d�termin�s al�atoirement.
template<class T>
void Population<T>::aideGenerer() {
	// Avoir deux num�ros diff�rents pour les parents de la cellule
	short int randG = rand() % longueur();
	short int randD = randG;
	do {
		randD = rand() % longueur();
	} while (randD == randG);


	// Obtenir les NoeudPop correspondant aux emplacements trouv�s
	NoeudPop<T>* NPopG = nullptr;
	NoeudPop<T>* NPopD = nullptr;
	for (fixerTete(); estDansListe(); suivant()) {

		// D�s que randG est compl�tement d�cr�ment�, on r�cup�re la valeur courante
		if (randG == 0) {
			NPopG = valeurCourante();
		}

		// D�s que randD est compl�tement d�cr�ment�, on r�cup�re la valeur courante

		if (randD == 0) {
			NPopD = valeurCourante();
		}

		if (randG < 0 && randD < 0) {
			break;
		}
		// On d�cr�mente les compteurs
		randG--;
		randD--;
	}

	// On r�cup�re les valeurs
	T cellG = NPopG->getR_cell();
	T cellD = NPopD->getR_cell();

	// On cr�� une nouvelle cellule en fonction des valeurs des cellules parents, gauche et droite
	T newIndividu = cellG + cellD;
	Noeud<T>* newNoeud = new Noeud<T>(getNextID(), newIndividu);
	newNoeud->ancGauche = NPopG->getR();
	newNoeud->ancDroite = NPopD->getR();
	insererFin(newNoeud);
}

/*
* Fonction renvoyant la repr�sentation textuelle d�un individu faisant partie de cette population.
* @param _id :	l�id d�un individu.
* @returns		le string de l�arborescence d�un individu ou un message d�erreur.
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
