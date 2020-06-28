#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

class Monstruo{
public:	
	Monstruo():Damage(50),hp(100){ }
    void Provocar(){
    cout << "El enemigo busca atacarte"<< endl;
}
    void Atacar(){
    cout << "¡Al ataque! Daño de \t" << Damage << " puntos." <<endl; 
}
    void setHP(int a){
	hp=a;
}
    void setType(string a){
		type=a;
}
    int getHP(){
	return hp;
}
    friend string getName(Monstruo p);
    string getType(){
	return type;
}
    void setDamage(int a){
	Damage=a;
}
	int getDamage(){
	return Damage;
}
    void getAttacked(int a){
		if(a>hp) a=hp;
		setHP(getHP()-a);
	}
	bool fainted(){
		if(hp==0) return 1;
		return 0;
	}
private:
   string type;
   int Damage,hp;
};
class Boss : public Monstruo{ 
public: 
    Boss(int dmg){
		setHP(300);
		setDamage(dmg);}
	void resetCounter(){
		counter=0;}
    void MegaCura(){
		counter++;
		switch(counter){
				case 1:case 2:
					cout<<"Charging Heal... >:D"<<endl;
					break;
				default: 
					getAttacked(-100);
					cout<<"Vida recuperada :D"<<endl;
					resetCounter();
					break;
			}
	} 
private:
	int counter;
};
