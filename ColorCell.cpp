#include "ColorCell.h"
#include <iostream>
using namespace std;

// CONSTRUCTEURS DESTRUCTEURS /////////////////////////////////////////////////////////////////////

// Constructeur par d�faut
ColorCell::ColorCell() {
	this->rouge = 0;
	this->vert = 0;
	this->bleu = 0;
}

/**
* Constructeur de Noeud avec id et valeur
* @param _rouge:	code pour la couleur rouge
* @param _vert:		code pour la couleur verte
* @param _bleu:		code pour la couleur bleue
*/
ColorCell::ColorCell(short int _rouge, short int _vert, short int _bleu) {
	this->rouge = _rouge;
	this->vert = _vert;
	this->bleu = _bleu;
}

// Destructeur par d�faut
ColorCell::~ColorCell(){}

// GETTERS SETTERS ////////////////////////////////////////////////////////////////////////////////

// Getter de rouge
short int ColorCell::getRouge() const { return rouge; }

// Getter de vert
short int ColorCell::getVert() const { return vert; }

// Getter de bleu
short int ColorCell::getBleu() const { return bleu; }

/**
* Setter de rouge
* Verifie si la valeur est bien entre 0 et 255 avant de l'utiliser
* @param _valeur : short int
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
* Setter de vert
* Verifie si la valeur est bien entre 0 et 255 avant de l'utiliser
* @param _valeur : short int
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
* Setter de bleu
* Verifie si la valeur est bien entre 0 et 255 avant de l'utiliser
* @param _valeur : short int
*/
void ColorCell::setBleu(short int _valeur) {
	if (0 >= _valeur && _valeur <= 255) {
		bleu = _valeur;
	}
	else {
		cout << "Insertion impossible de la valeur pour BLEU : " + _valeur << endl;
	}
}

// FONCTIONS //////////////////////////////////////////////////////////////////////////////////////

// Repr�sentation textuelle de ColorCell
string ColorCell::toString() const {
	return to_string(rouge) + " " + to_string(vert) + " " + to_string(bleu);
}


istream& operator>> (istream& in, ColorCell& colorcell)
{
	in >> colorcell.rouge >> colorcell.vert >> colorcell.bleu;

	return in;
}

ostream& operator<< (ostream& out, ColorCell& colorcell) {

	out << colorcell.toString();

	return out;
}

ColorCell ColorCell::operator + (ColorCell c) {
	// Initialisation des diff�rentes couleurs
	short int bleu;
	short int rouge;
	short int vert;

	//Initialisation des diff�rents op�rateurs de couleurs
	//Bleu
	bleu = (this->bleu + (c.bleu)) / 2;

	//Rouge
	rouge = (this->rouge + (c.rouge)) / 2;

	//Vert
	vert = (this->vert + (c.vert)) / 2;

	return ColorCell(bleu, rouge, vert);
}