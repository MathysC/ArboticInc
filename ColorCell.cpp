#include "ColorCell.h"
#include <iostream>
using namespace std;

// CONSTRUCTEURS DESTRUCTEURS /////////////////////////////////////////////////////////////////////

// Constructeur par d�faut.
ColorCell::ColorCell() {
	this->rouge = 0;
	this->vert = 0;
	this->bleue = 0;
}

/**
* Constructeur de Noeud avec id et valeur.
* @param _rouge:	code pour la couleur rouge.
* @param _vert:		code pour la couleur verte.
* @param _bleu:		code pour la couleur bleue.
*/
ColorCell::ColorCell(short int _rouge, short int _vert, short int _bleu) {
	this->rouge = _rouge;
	this->vert = _vert;
	this->bleue = _bleu;
}

// Destructeur par d�faut.
ColorCell::~ColorCell(){}

// GETTERS SETTERS ////////////////////////////////////////////////////////////////////////////////

// Getter de rouge.
short int ColorCell::getRouge() const { return rouge; }

// Getter de vert.
short int ColorCell::getVert() const { return vert; }

// Getter de bleue.
short int ColorCell::getBleu() const { return bleue; }

/**
* Setter de rouge.
* Verifie si la valeur est bien entre 0 et 255 avant de l'utiliser.
* @param _valeur : short int.
*/
void ColorCell::setRouge(short int _valeur) {
	if (0 >= _valeur && _valeur <= 255) {
		rouge = _valeur;
	}
	else {
		cout << "Insertion impossible de la valeur pour ROUGE : " + _valeur << endl;
	}
}

/**
* Setter de vert.
* Verifie si la valeur est bien entre 0 et 255 avant de l'utiliser.
* @param _valeur : short int.
*/
void ColorCell::setVert(short int _valeur) {
	if (0 >= _valeur && _valeur <= 255) {
		vert = _valeur;
	}
	else {
		cout << "Insertion impossible de la valeur pour VERT : " + _valeur << endl;
	}
}

/**
* Setter de bleue.
* Verifie si la valeur est bien entre 0 et 255 avant de l'utiliser.
* @param _valeur : short int.
*/
void ColorCell::setBleu(short int _valeur) {
	if (0 >= _valeur && _valeur <= 255) {
		bleue = _valeur;
	}
	else {
		cout << "Insertion impossible de la valeur pour BLEU : " + _valeur << endl;
	}
}

// FONCTIONS //////////////////////////////////////////////////////////////////////////////////////

/*
* Repr�sentation textuelle de ColorCell.
* @returns le string de ColorCell.
*/
string ColorCell::toString() const {
	return to_string(rouge) + " " + to_string(vert) + " " + to_string(bleue);
}

/*
* Surcharge de l�op�rateur >>. R�cup�ration des informations formant une ColorCell.
* @param _in :			le stream d�input.
* @param _colorcell :	la colorcell � modifier.
* @returns				Le stream � jour.
*/
istream& operator>> (istream& _in, ColorCell& _colorcell)
{
	_in >> _colorcell.rouge >> _colorcell.vert >> _colorcell.bleue;

	return _in;
}

/*
* Surcharge de l�op�rateur <<. Retour du toString de ColorCell.
* @param _out :			le stream de output.
* @param _colorcell :	la colorCell � repr�senter.
* @returns				le stream � jour.
*/
ostream& operator<< (ostream& _out, ColorCell& _colorcell) {

	_out << _colorcell.toString();

	return _out;
}

/*
* Surcharge de l�op�rateur +. Permet un calcul sur les 3 champs qui composent ColorCell.
* @param _colorcell :	le deuxi�me colorCell � utiliser dans ce calcul.
* @returns				une nouvelle ColorCell avec les informations deux autres.
*/
ColorCell ColorCell::operator + (ColorCell _colorcell) {
	// Initialisation des diff�rentes couleurs
	short int bleue;
	short int rouge;
	short int vert;

	//Initialisation des diff�rents op�rateurs de couleurs
	//Bleu
	bleue = (this->bleue + (_colorcell.bleue)) / 2;

	//Rouge
	rouge = (this->rouge + (_colorcell.rouge)) / 2;

	//Vert
	vert = (this->vert + (_colorcell.vert)) / 2;

	return ColorCell(bleue, rouge, vert);
}