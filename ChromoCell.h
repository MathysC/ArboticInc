#pragma once
#include <string>
#include <iostream>
using namespace std;

class ChromoCell
{
private:
	string listChromo() const;											// Obtenir les 4 paires en une liste.
	bool pileOuFace() const;											// Un pile ou face utilis� pour la g�n�ration al�atoire.
	char paireUne[2];													// Premi�re Paire de Chromosome.
	char paireDeux[2];													// Deuxi�me Paire de Chromosome.
	char paireTrois[2];													// Troisi�me Paire de Chromosome.
	char paireQuatre[2];												// Quatri�me Paire de Chromosome.

public:
	ChromoCell();														// Constructeur par d�faut.
	ChromoCell(char[], char[], char[], char[]);							// Constructeur avec les 4 paires.
	~ChromoCell();														// Destructeur par d�faut.

	string toString() const;											// Repr�sentation textuelle de ColorCell.

	ChromoCell operator + (ChromoCell c);								// Surcharge de l�op�rateur +.
	friend istream& operator>> (istream& in, ChromoCell& chromocell);	// Surcharge de l�op�rateur >>.
	friend ostream& operator<< (ostream& out, ChromoCell& chromocell);	// Surcharge de l�op�rateur <<.

};
