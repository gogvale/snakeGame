//#include "stdafx.h"
#include <vector>
#include <iostream>
#define MONSTER "Zubat.txt"
#define BOSS "Boss.txt"
#include "Lorna.h" 
#include "Victor.h"



using namespace std;

int Opciones() {
	cout << "Que desea hacer?" << '\n';
	cout << "\
			1.atacar\n\
			2.usar pocion\n\
			3.no hacer nada\n\
			4.intentar escapar\n";
	int a = 0;
	while (a <= 0 || a >= 5) {
		cin >> a;
		if (a <= 0 || a >= 5) cout << "Opcion invalida" << '\n';
	}
	return a;
}
vector <int*> batallaPokemon(int hpUSER, int potions, string type, string name, int a) {
	Monstruo monstruo1, User;
	User.setHP(100);
	User.setType("Poison");
	User.setDamage(20);
	system("clear");
	vector <int*> b;
	if (a == 0) {
		Monstruo Rattata;
		cout << "Un Rattata salvaje apareció!!" << '\n';
		while (hpUSER>0 && Rattata.getHP()>0) {
			switch (Opciones()) {
			case 1:
				Rattata.getAttacked(50);
				
				break; 	//atacar
			case 2: 
				User.getAttacked(-20);

				break; //usar pocion
			case 3:			//no hacer nada
			case 4:break;	//intentar huir
			}

			//accion Rattata		
		}

	}

	else { //batalla contra boss
		Monstruo Bossaa;
		cout << "Un Boss apareció!!" << '\n';
		while (hpUSER>0 && Bossaa.getHP()>0) {
			switch (Opciones()) {
			case 1:
				Bossaa.getAttacked(50);

				break; 	//atacar
			case 2:		
				User.getAttacked(-20);//usar pocion

			case 3:			//no hacer nada
			case 4:break;	//intentar huir
			}

			//accion Boss		
		}

	}
	// b={HP,potion,GameOver}
	b.push_back(&hpUSER);
	b.push_back(&potions);
	b.erase(b.begin());
	if (hpUSER>0)  int a = 1;
	else int a = 0;
	b.push_back(&a);
	return b;

}
