#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<stdio.h>
#include<fstream>

using namespace std;

char And[9][3];
char Impl[9][3];
char Not[9][3];
char Or[9][3];

int score = 0;
int step = 0;

void printRules(){
	system("clear");
	cout << endl;
	cout << " W tej grze zadaniem jest zdobycie wymaganej ilosci punktow," << endl;
	cout << " w jak najmniejszej liczbie krokow. Mozna tez dazyc do innych" << endl;
	cout << " celow, np.: zdobycie jak najwiecej punktow powyzej limitu." << endl;
	cout << endl;
	cout << " W grze wystepuja dwie kwadratowe tablice o wielkosci zadanej" << endl;
	cout << " przez gracza. Punkty dostaje sie przez zdobycie jak najwiecej" << endl;
	cout << " wylosowanych wartosci {0, x, 1} odpowiadajacych wartosciom" << endl;
	cout << " wystepujacym w logice trojwartosciowej. Robi się to dzieki" << endl;
	cout << " uzyciu polecen and, or oraz impl (mozna rownierz uzyc: &, v, ->)." << endl;
	cout << " Wynik zapisywany jest w pierwszej tablicy, a druga generowana" << endl;
	cout << " jest losowo. Mozna takze uzyc polecenia not(~), aby zanegowac" << endl;
	cout << " wartosci obu tablic. Nie jest to liczone jako krok. " << endl;
	cout << endl;
	cout << " Aby wyjsc wpisz 'wyjdz' po rozpoczeciu gry. Powodzenia!" << endl;
	cout << endl;
}

bool loadFile(string type, char tab[][3], int row, int col){
	ifstream File;
	File.open(type.c_str());

	if(!File.good()) return false;

	char input;
	
	for(int i = 0; i < row; i++) {for(int j = 0; j < col; j++){
		if(File.good()){
			File >> input;
			if(input == '1') tab[i][j] = '1';
			else if(input == '0') tab[i][j] = '0';
			else if(input == 'x') tab[i][j] = 'x';
			else{
				cout << "Bledne dane w " << type << "." << endl;
				File.close();
				return false;
			}
		}else{
			File.close();
			return false;
		}
	}}
	File.close();
	return true;
}

void printTable(char **tab, int N){
	system("clear");
	cout << endl;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++) cout << " " << tab[i][j];
		cout << endl;
	}
	cout << endl;
}

void printTables(char **tab1, char **tab2, int N){
	system("clear");
	cout << endl;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++) cout << " " << tab1[i][j];
		cout << "	";
		for(int j = 0; j < N; j++) cout << " " << tab2[i][j];
		cout << endl;
	}
	cout << endl;
}

void generate(char **tab, int N){
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++){
		int tmp = rand() % 3;
		if(tmp == 0) tab[i][j] = '1';
		else if(tmp == 1) tab[i][j] = '0';
		else tab[i][j] = 'x';
	}
}

void tNot(char **tab1, char **tab2, int N){
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++){
		for(int key = 0; key < 3; key++){
			if(Not[key][0] == tab1[i][j]){
				tab1[i][j] = Not[key][1];
				break;
			}
		}
		for(int key = 0; key < 3; key++){
			if(Not[key][0] == tab2[i][j]){
				tab2[i][j] = Not[key][1];
				break;
			}
		}
	}step--;
}

void tAnd(char **tab1, char **tab2, int N, char target){
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++){
		for(int key = 0; key < 9; key++){
			if(And[key][0] == tab1[i][j] && And[key][1] == tab2[i][j]){
				tab1[i][j] = And[key][2];
				generate(tab2, N);
				if(tab1[i][j] == target) score++;
				break;
			}	
		}
	}
}

void tOr(char **tab1, char **tab2, int N, char target){
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++){
		for(int key = 0; key < 9; key++){
			if(Or[key][0] == tab1[i][j] && Or[key][1] == tab2[i][j]){
				tab1[i][j] = Or[key][2];
				generate(tab2, N);
				if(tab1[i][j] == target) score++;
				break;
			}	
		}
	}
}

void tImpl(char **tab1, char **tab2, int N, char target){
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++){
		for(int key = 0; key < 9; key++){
			if(Impl[key][0] == tab1[i][j] && Impl[key][1] == tab2[i][j]){
				tab1[i][j] = Impl[key][2];
				generate(tab2, N);
				if(tab1[i][j] == target) score++;
				break;
			}	
		}
	}
}

char goal(){
	int seed = rand() % 3;
	if(seed == 0) return '0';
	else if(seed == 1) return '1';
	else return 'x';
}

int main(int argc, char * argv[]){

	srand(time(NULL));	 
  
	if(argc == 5) while(argc > 1){
		string tmp=argv[argc-1];
		if(tmp=="not.txt" &&  loadFile(argv[argc - 1], Not, 3, 2));
		else if(tmp=="and.txt" && loadFile(argv[argc - 1], And, 9, 3));
		else if(tmp=="impl.txt" && loadFile(argv[argc - 1], Impl, 9, 3));
		else if(tmp=="or.txt" && loadFile(argv[argc - 1], Or, 9, 3));
		else{
			cout << "Nie udalo sie otworzyc odpowiednich plikow." << endl;
			return 0;
		}   	  
		argc--;	     
	}
	else{
		cout << "Zla liczba argumentow." << endl;
		return 0;
	}
	
	printRules();

	int N;

	flag:
	cout << "Podaj wielkość planszy: ";
	cin >> N;
	cout << endl;
	if(cin.fail()){
		cout << "Nie podano liczby." << endl;
		cin.clear();
		cin.ignore(1024, '\n');
		goto flag;
	}
	if(N < 3){
		cout << "Plansza bedzie za mala. ";
		goto flag;
	}

	char **tab1, **tab2; 
	tab1 = new char *[N]; tab2 = new char *[N];
	for(int i = 0; i < N; i++){
		tab1[i] = new char[N]; tab2[i] = new char[N];
	}
	
	string input = "";
	
	generate(tab1, N);
	generate(tab2, N);

	while(score < 4 * N * N){
		printTables(tab1, tab2, N);
		
		
		char target = goal();
		cout << "Prog: " << 4 * N * N << endl;
		cout << "Punkty: " << score << endl << endl;	
		cout << "Kroki: " << step << endl << endl;	
		cout << "Cel: { " << target << " }" << endl << endl;	

		cin >> input;
		
		if(input == "wyjdz") break;
		
		if(input == "~" || input == "not") tNot(tab1, tab2, N);
		else if(input == "->" || input == "impl") tImpl(tab1, tab2, N, target);
		else if(input == "v" || input == "or") tOr(tab1, tab2, N, target);
		else if(input == "&" || input == "and") tAnd(tab1, tab2, N, target);
		else step--;
		step++;
	}
	system("clear");
	cout << "Twój wynik" << endl << "Punkty: " << score << endl << "Kroki: " << step << endl;

	return 0;
}
