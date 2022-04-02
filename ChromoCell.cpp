#include "ChromoCell.h"
#include <iostream>
using namespace std;

// CONSTRUCTEURS DESTRUCTEURS //////////////////////////

// Constructeur par d�faut.
ChromoCell::ChromoCell() {}

/**
* Constructeur de Noeud avec id et valeur.
* @param _paireUne:		La premi�re paire de chromosomes.
* @param _paireDeux:	La deuxi�me paire de chromosomes.	
* @param _paireTrois:	La troisi�me paire de chromosomes.
* @param _paireQuatre:	La quatri�me paire de chromosomes.
*/
ChromoCell::ChromoCell(char _paireUne[], char _paireDeux[], char _paireTrois[], char _paireQuatre[]) {
	this->paireUne[0] = _paireUne[0];
	this->paireUne[1] = _paireUne[1];
	this->paireDeux[0] = _paireDeux[0];
	this->paireDeux[1] = _paireDeux[1];
	this->paireTrois[0] = _paireTrois[0];
	this->paireTrois[1] = _paireTrois[1];
	this->paireQuatre[0] = _paireQuatre[0];
	this->paireQuatre[1] = _paireQuatre[1];	
}

// Destructeur par d�faut.
ChromoCell::~ChromoCell(){}

// FONCTIONS //////////////////////////////////////////////////////////////////////////////////////

/*
* Surcharge de l�op�rateur >>. R�cup�ration des informations formant une ChromoCell.
* @param _in :			le stream d�input.
* @param _chromocell :	la ChromoCell � modifier.
* @returns				Le stream � jour.
*/
istream& operator>> (istream& _in, ChromoCell& _chromocell)
{

	string paire;
	_in >> paire;
	_chromocell.paireUne[0] = paire[0];
	_chromocell.paireUne[1] = paire[1];

	_in >> paire;
	_chromocell.paireDeux[0] = paire[0];
	_chromocell.paireDeux[1] = paire[1];

	_in >> paire;
	_chromocell.paireTrois[0] = paire[0];
	_chromocell.paireTrois[1] = paire[1];

	_in >> paire;
	_chromocell.paireQuatre[0] = paire[0];
	_chromocell.paireQuatre[1] = paire[1];

	return _in;
}

/*
* Surcharge de l�op�rateur <<. Retour du toString de ColorCell.
* @param _out :			le stream de output.
* @param _chromocell :	la ChromoCell � repr�senter.
* @returns				le stream � jour.
*/
ostream& operator<< (ostream& _out, ChromoCell& _chromocell) {

	_out << _chromocell.toString();

	return _out;
}

/*
* Surcharge de l�op�rateur +. Permet un calcul sur les 4 champs qui composent ChromoCell.
* @param _chromocell :	le deuxi�me ChromoCell � utiliser dans ce calcul.
* @returns				une nouvelle ChromoCell avec les informations deux autres.
*/
ChromoCell ChromoCell::operator + (ChromoCell _chromocell) {
	// Initialisation des diff�rentes couleurs
	char _Une[2];
	char _Deux[2];
	char _Trois[2];
	char _Quatre[2];
	char _Complet[8];
	bool element;
	for (short int i = 0; i < 8; i+=2) {
		// Choisir de quel ChromoCell provient le premier chromosomes
		element = pileOuFace();
		
		if (element) {
			// Choisir si je mets l�element du premier ChromoCell en premier ou second
			
			// Choisir si je prends le premier �l�ment de la paire ou le second
			element = pileOuFace();
			_Complet[i] = this->listChromo()[i + element];
			element = pileOuFace();
			_Complet[i + 1] = _chromocell.listChromo()[i + element];
		}
		else {
			// Choisir si je prends le premier �l�ment de la paire ou le second
			element = pileOuFace();
			_Complet[i+1] = this->listChromo()[i + element];
			element = pileOuFace();
			_Complet[i] = _chromocell.listChromo()[i + element];
		}

		_Une[0] = _Complet[0];
		_Une[1] = _Complet[1];

		_Deux[0] = _Complet[2];
		_Deux[1] = _Complet[3];

		_Trois[0] = _Complet[4];
		_Trois[1] = _Complet[5];

		_Quatre[0] = _Complet[6];
		_Quatre[1] = _Complet[7];


	}

	return ChromoCell(_Une,_Deux,_Trois,_Quatre);
}

/*
* Fonction permettant plusieurs choix lors de la g�n�ration al�atoire de ChromoCell.
* @returns Un bool�an choisie al�atoirement.
*/
bool ChromoCell::pileOuFace() const {
	return rand() % 2;
}

/*
* Repr�sentation textuelle de ChromoCell de toutes les paires � la suite, utile pour simplifier le code.
* @returns le string de ChromoCell sans espace pour s�parer les valeurs.
*/
string ChromoCell::listChromo() const {
	string res;
	res.append(1, paireUne[0]);
	res.append(1, paireUne[1]);
	res.append(1, paireDeux[0]);
	res.append(1, paireDeux[1]);
	res.append(1, paireTrois[0]);
	res.append(1, paireTrois[1]);
	res.append(1, paireQuatre[0]);
	res.append(1, paireQuatre[1]);
	return res;
}

/*
* Repr�sentation textuelle de ChromoCell.
* @returns le string de ChromoCell.
*/
string ChromoCell::toString() const {
	string res;
	res.append(1, paireUne[0]);
	res.append(1, paireUne[1]);
	res.append(1, ' ');
	res.append(1, paireDeux[0]);
	res.append(1, paireDeux[1]);
	res.append(1, ' ');
	res.append(1, paireTrois[0]);
	res.append(1, paireTrois[1]);
	res.append(1, ' ');
	res.append(1, paireQuatre[0]);
	res.append(1, paireQuatre[1]);
	res.append(1, ' ');
	return res;
}
