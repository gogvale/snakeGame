#include <iostream>
using namespace std;
//15 caracteres max

void DanoEnem(int dmg){
	cout<<"Deal "<<dmg<<" dmg";}
void DanoAuto(int dmg){
	cout<<"Take "<<dmg<<" dmg";}
void Heal(int hp){
	cout<<"Recover "<<hp<<" LP";}
void deleteLine(){
	for(int i=0;i<15;i++) cout<<" ";}

