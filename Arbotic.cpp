#include "Arbotic.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Population.h"
using namespace std;

void Arbotic::ouverture_population(string _fichierPopulation) {

	ifstream fin(_fichierPopulation); //Lecture

	// Variables composant un client
	string type;
	short int NB;
	int num;
	int i = 1;
	fin >> type >> NB;

	// Tant que l�on peut recup�rer les informations
	while (i < NB + 1) {

	}
	

	// Fermer la lecture du fichier
	fin.close();
}

void Arbotic::sauvegarde_population(string _nomFichierPopulation) {

	// Cr�ation/Ouverture du fichier de sauvegarde
	ofstream sortie;
	sortie.open(_nomFichierPopulation);

	// On parcourt tous la clients et on sauvegarde les informations
	

	// Fermeture du fichier
	sortie.close();
}




void Arbotic::ouverture_transactions(string _fichierTransaction) {

	ifstream fin(_fichierTransaction); //Lecture

	char caractere;
	

	short int NB;
	int ID;
	int X;
	int Y;
	string type;

	//Impl�mentaion des variables n�cessaires 
	

	while (fin >> caractere) {
		switch (caractere) {

			// Cr�er une population vide de type ...
		case 'C': {
			fin >> type;
			cout << "Cr�er une population vide de type:" << type << "\n" << endl;

			break;
		}

				// Ajoute � la population courante un individu sans parent de type... ayant les valeurs ... Population.insererFin(Cellule)
		case 'A': {
			fin >> type;
			cout << "Ajoute � la population courante un individu sans parents de type" << type << "ayant les valeurs:" << endl;
			population.insererFin(Cellule);
			break;
		}

				// Ouverture du fichier population
		case 'O': {
			cout << "Ouverture du fichier population \n" << endl;
			fin >> nomFichierPopulation;
			ouverture_population(nomFichierPopulation);
			break;
		}

				// Sauvegarde fichier population
		case 'S': {
			cout << "Sauvegarde du fichier population \n" << endl;
			fin >> nomFichierPopulation;
			sauvegarde_population(nomFichierPopulation);
			break;
		}

				// G�nerer NB individues � partir de la population courante 
		case '+': {
			fin >> NB;
			cout << "G�n�re" << NB << "individues � partir de la population courante \n" << endl;
			population.generer(NB);

			break;
		}

				//  Supprime un individu X
		case '-': {
			fin >> ID;
			cout << "Supprime l'individu" << ID << "\n" << endl;
			population.supprimer(ID);
			break;
		}

				//  Trouve un anc�tre commun entre deux individus
		case '?': {
			fin >> X >> Y;
			cout << "Anc�tre commmun entre deux individu" << X << "et" << Y << ": \n" << endl;
			population.ancetreETenfantCommuns(X,Y);
			break;
		}

				//  Affiche l'arbre g�n�tique complet de l'individu X
		case '$': {
			fin >> X;
			cout << "Affiche l'arbre g�n�tique complet de l'individu" << X << "incluant ses caract�riques: \n" << endl;
			population.toStringIndividu(X);
			break;
		}

				// Cas erreur
		default: {
			cout << "\n fin de la liste transaction \n";
			fin.close();
			return;
		}
		}
	}

	cout << "\n Merci Isaaaaaaa :)" << endl;
	fin.close();
}