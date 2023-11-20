//============================================================================
// Name        : CS2_Chapter_17_InClassProject.cpp
// Author      : Nicholas Deal
// Version     :
// Copyright   : Make sure you bring the money if you want to use this
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <iomanip>
#include "Movie.hpp"
using namespace std;

int main() {

	map<string, Movie*> movieCatalog;
	map<string, Movie*>::iterator movieCatalogIT;
	pair<map<string, Movie*>::iterator, bool> insert;
	string userInput;

	Movie* aMovie = new Movie();
	aMovie->title = "Castle in the Sky";
	aMovie->category = "Anime";
	aMovie->yearOfProduction = 1989;
	insert = movieCatalog.insert(pair<string, Movie*>(aMovie->title, aMovie));
	if (insert.second == false) {
		cout << "Movie with key: " << aMovie->title << " not inserted" << endl;
	}//if
	else {
		cout << "Movie with key: " << aMovie->title << " inserted successfully" << endl;
	}//else

	aMovie = new Movie();
	aMovie->title = "The Goonies";
	aMovie->category = "Adventure";
	aMovie->yearOfProduction = 1985;
	insert = movieCatalog.insert(pair<string, Movie*>(aMovie->title, aMovie));
	if (insert.second == false) {
		cout << "Movie with key: " << aMovie->title << " not inserted" << endl;
	}//if
	else {
		cout << "Movie with key: " << aMovie->title << " inserted successfully" << endl;
	}//else

	aMovie = new Movie();
	aMovie->title = "Guardians of the Galaxy";
	aMovie->category = "Sci-Fi";
	aMovie->yearOfProduction = 2014;
	insert = movieCatalog.insert(pair<string, Movie*>(aMovie->title, aMovie));
	if (insert.second == false) {
		cout << "Movie with key: " << aMovie->title << " not inserted" << endl;
	}//if
	else {
		cout << "Movie with key: " << aMovie->title << " inserted successfully" << endl;
	}//else

	aMovie = new Movie();
	aMovie->title = "Star Wars";
	aMovie->category = "Sci-Fi";
	aMovie->yearOfProduction = 1977;
	insert = movieCatalog.insert(pair<string, Movie*>(aMovie->title, aMovie));
	if (insert.second == false) {
		cout << "Movie with key: " << aMovie->title << " not inserted" << endl;
	}//if
	else {
		cout << "Movie with key: " << aMovie->title << " inserted successfully" << endl;
	}//else

	aMovie = new Movie();
	aMovie->title = "Big Trouble in Little China";
	aMovie->category = "Action";
	aMovie->yearOfProduction = 1986;
	insert = movieCatalog.insert(pair<string, Movie*>(aMovie->title, aMovie));
	if (insert.second == false) {
		cout << "Movie with key: " << aMovie->title << " not inserted" << endl;
	}//if
	else {
		cout << "Movie with key: " << aMovie->title << " inserted successfully" << endl;
	}//else

	aMovie = new Movie();
	aMovie->title = "Big Trouble in Little China";
	aMovie->category = "Action";
	aMovie->yearOfProduction = 1986;
	insert = movieCatalog.insert(pair<string, Movie*>(aMovie->title, aMovie));
	if (insert.second == false) {
		cout << "Movie with key: " << aMovie->title << " not inserted" << endl;
	}//if
	else {
		cout << "Movie with key: " << aMovie->title << " inserted successfully" << endl;
	}//else

	while (userInput != "-999") {
		cout << endl << "Please type a movie title you wish to find (type -999 to exit): ";
		getline(cin, userInput);
		if (userInput == "-999") {
			cout << endl << "Exiting the search..." << endl << endl;
		}//if
		else {
			try {
			movieCatalog.at(userInput);
			cout << movieCatalog[userInput]->title << " was found!";
			}//try
			catch (const std::out_of_range &e) {
				cout << endl << "Movie with the title '" << userInput << "' was not found." << endl;
				cout << endl << "Loading movie options..." << endl << endl;
				cout << "------------------------------------------------------------------------" << endl;
				cout << "Movie Catalog" << endl;
				cout << setw(30) << "Title" << setw(15) << "Year" << setw(15) << "Category" << endl;
				cout << setw(30) << "=====" << setw(15) << "====" << setw(15) << "========" << endl;
				for (movieCatalogIT = movieCatalog.begin();
						movieCatalogIT != movieCatalog.end();
						movieCatalogIT++) {
					cout << setw(30) << (*movieCatalogIT).second->title << setw(15) << (*movieCatalogIT).second->yearOfProduction << setw(15) <<
							(*movieCatalogIT).second->category << endl;
				}//for
				cout << "-------------------------------------------------------------------------" << endl;
			}//catch
		}//else
	}//while

	for (movieCatalogIT = movieCatalog.begin();
			movieCatalogIT != movieCatalog.end();
			movieCatalogIT++) {
		delete (*movieCatalogIT).second;
	}//for

	movieCatalog.clear();

	cout << "Program ending, have a nice day!" << endl; // prints !!!Hello World!!!
	return 0;
}
