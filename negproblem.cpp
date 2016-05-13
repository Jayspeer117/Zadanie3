#include <iostream>
#include <cstdlib>
using namespace std;

/*
Program ten sluzy sprawdzeniu czy ma sie w wolnym tego slowa znaczeniu problem.
Argument 1 - ilosc promili alkoholu w krwi [>0]
Argument 2 - ilosc nielegalnych substancji w krwi [>0]
Argument 3 - czy zostawil cie partner/partnerka [1-tak,0-nie]
Argument 4 - o ktorej godzinie musisz wstawac [0-24,-1-wcale]
Argument 5 - czy czujesz potrzebe zmiany w swoim zyciu [1-tak,0-nie]
Argument 6 - czy studiujesz/studiowales na agh[1-tak,0-nie] 
*/

int main(int argc, char **argv){

	if(argc != 7){
		cout << "Zla liczba argumentow" << endl;
		return 0;
	}
	
	int p[6];
	
	for(int i = 0; i < 6; i++) p[i] = atoi(argv[i+1]);

	if( !(((((!(p[0] < 3) || !(p[1] > 2)) && (!(p[2] == 1) || !(p[0] < 4))) && !(p[3] != -1)) || !(p[4] == 1)) && (p[5] == 0) )) cout << "1" << endl; //masz problem
	else cout << "0" << endl; //nie masz problemu

	return 0;
}
