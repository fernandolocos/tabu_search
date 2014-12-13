#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "tabu.h"

using namespace std;

void readInstance(const char *instance, vector<character> &heroes, 
	vector<character> &villains, vector<collaboration> &collab, 
	vector<int> &team_villains)
{
	int i, id, intelligence, strength, speed, durability, energy, fighting, 
		numberAppeared, c1, c2, value, idVillain;
   string name, type, inst = (string) instance;

	// abre os arquivos de leitura
	ifstream file1, file2, file3;   				
	file1.open("marvel_characters.txt");  
	file2.open("shared_comic_books.txt");
	file3.open(instance);

	// faz a leitura do file1 e cria os vetores de personagens
	for (i = 0; i < 767; i++) {
		file1 >> id >> name >> type >> intelligence >> strength >> speed >> 
			durability >> energy >> fighting >> numberAppeared;
			
		if(type == "hero") {
			heroes.push_back(character(id, name, intelligence, strength, speed, 
				durability, energy, fighting, numberAppeared));
		} else {
			villains.push_back(character(id, name, intelligence, strength, speed, 
				durability, energy, fighting, numberAppeared));
		}
	}

	// faz a leitura do file2 e cria o vetor de colaboracoes
	for (i = 0; i < 57308; i++) {
		file2 >> c1 >> c2 >> value;
		collab.push_back(collaboration(c1, c2, value));
	}
	 
	// faz a leitura do file3 e cria o vetor de team_villains
	inst.replace(0,11,"");
	inst.replace(inst.end()-8,inst.end(),"");
	instance = inst.c_str();;
	for (i = 0; i < atoi(instance); i++) {
		file3 >> idVillain;
		team_villains.push_back(idVillain);
	}

	file1.close();
	file2.close();
	file3.close();
}

void printInstance(vector<character> heroes, vector<character> villains, 
	vector<collaboration> collab, vector<int> team_villains)
{
	unsigned int i;
	cout << "HEROES\n";
	//for (i = 0; i < heroes.size(); i++) {
	for (i = 0; i < heroes.size(); i++) {
		cout << heroes[i].id  << " " << heroes[i].name << " " << 
			heroes[i].intelligence << " " <<
			heroes[i].strength << " " << heroes[i].speed << " " << 
			heroes[i].durability << " " << heroes[i].energy << " " << 
			heroes[i].fighting << " " << heroes[i].numberAppeared << "\n";
	}
	
	cout << "\nVILLAINS\n";
	for (i = 0; i < villains.size(); i++) {
		cout << villains[i].id  << " " << villains[i].name << " " << 
			villains[i].intelligence << " " <<
			villains[i].strength << " " << villains[i].speed << " " << 
			villains[i].durability << " " << villains[i].energy << " " << 
			villains[i].fighting << " " << villains[i].numberAppeared << "\n";
	}
	
	/*cout << "\nCOLLAB\n";
	for (i = 0; i < collab.size(); i++) {
		cout << collab[i].c1  << " " << collab[i].c2 << " " << 
			collab[i].value << "\n";
	}*/
	
	cout << "\nTEAM VILLAINS\n";
	cout << team_villains.size() << endl;
	for (i = 0; i < team_villains.size(); i++) {
		cout << team_villains[i] << "\n";
	}
}

void printSolution(vector<int> team_heroes, vector<int> team_villains, 
	int collaboration_lv, int fighting_exp)
{
	//unsigned int i;
	int solution = collaboration_lv + fighting_exp;
	
	/*cout << "\nTEAM VILLAINS\n";
	for (i = 0; i < team_villains.size(); i++) {
		cout << team_villains[i] << "\n";
	}
	
	cout << "\nTEAM HEROES\n";
	for (i = 0; i < team_heroes.size(); i++) {
		cout << team_heroes[i] << "\n";
	}*/
	
	cout << "  " << solution << "       " << collaboration_lv << "      " 
		<<	fighting_exp << "\n";
}

int main(int argc, char **argv)
{   
   vector<character> heroes, villains;
	vector<collaboration> collab;
	vector<int> team_heroes, team_villains;
	int budget, collaboration_lv, fighting_exp;

   if(argc != 3)
   {
      cout << argv[0] << " <instancia> <budget=(0,1)>\n";
      return 0;
   }
   
   budget = atoi(argv[2]);

   readInstance(argv[1], heroes, villains, collab, team_villains);
   //printInstance(heroes, villains, collab, team_villains);

	if(budget){
		// fiz isso so pra rodar e nao dar bug
		team_heroes = initial_solution(heroes,villains,collab,team_villains,budget);
	}
	else {
		team_heroes = initial_solution(heroes,villains,collab,team_villains,budget);
	}
	
	collaboration_lv = collaboration_level(team_heroes, collab);
	fighting_exp = fighting_experience(team_heroes, team_villains, collab);
	printSolution(team_heroes, team_villains, collaboration_lv, fighting_exp);
	
   return 0;
}


