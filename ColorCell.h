#pragma once
#include <string>
#include <iostream>
using namespace std;

class ColorCell
{
private:
	short int rouge;
	short int vert;
	short int bleu;

public:
	ColorCell();									// Constructeur par d�faut
	ColorCell(short int, short int, short int);		// Constructeur avec les valeurs de rouge, vert et bleu
	~ColorCell();									// Destructeur de ColorCell

	short int getRouge() const;						// Getter de rouge
	short int getVert() const;						// Getter de vert
	short int getBleu() const;						// Getter de bleu

	void setRouge(short int);						// Setter de rouge, v�rifie que la valeur est entre 0 et 255
	void setVert(short int);						// Setter de vert, v�rifie que la valeur est entre 0 et 255
	void setBleu(short int);						// Setter de bleu, v�rifie que la valeur est entre 0 et 255

	string toString() const;						// Repr�sentation textuelle de ColorCell

	ColorCell operator + (ColorCell c) {
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

	friend istream& operator>> (istream& in, ColorCell& colorcell)
	{
		in >> colorcell.rouge;
		in >> colorcell.vert;
		in >> colorcell.bleu;

		return in;
	}


	friend istream& operator << (istream& in, ColorCell& colorcell) {

		in << colorcell.rouge;
		in << colorcell.vert;
		in << colorcell.bleu;

		return in;
	}

	friend istream& operator + (istream& in, ColorCell& colorcell) {

		in + colorcell.rouge;
		in + colorcell.vert;
		in + colorcell.bleu;

		return in;
	}

}
	
};





