#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <math.h>
using namespace std;

#define g 9.81
#define pi 3.1416
#define up 72
#define down 80
#define left 75
#define right 77
#define enter 13

struct Variables {
	int Op;
}V;

int Menu();
void Mrua();
void LeyNewton();
void Cursor(bool);
void gotoxy(int, int);
void Elegir(int, int, int);

int main() {
	Cursor(false);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  //Color de letras blancas
	system("cls");
	switch (Menu()) {
	case 1:
		Mrua();
		break;
	case 2:
		LeyNewton();
	}
	return 0;
}

int Menu() {
	//Abrir el menu de "Physics"
	ifstream archivo;
	string texto;
	archivo.open("menu.txt", ios::in);
	if (archivo.fail()) {
		cout << "\tError en cargar el texto" << endl;
		system("pause>null");
		exit(1);
	}
	else {
		while (!archivo.eof()) {
			getline(archivo, texto);
			cout << texto << endl;
		}
	}
	//Escoger Opcion
	int tecla;
	Elegir(9, 12, 3);
	system("cls");
	return V.Op;
}

void Mrua() {
inicio:
	bool Val[6] = { false };
	int col = 0;
	cout << "\tSeleccione los datos conocidos:\n" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "\t\t Distancia" << endl
		<< "\t\t Velocidad Final" << endl
		<< "\t\t Velocidad Inicial" << endl
		<< "\t\t Tiempo" << endl
		<< "\t\t Aceleracion";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(17, 8); cout << "Continuar";

	//Marcar Opcion
	int tecla;
	double resultado = 0, resultado2;
	double dis = 999, vef = 999, vei = 999, tie = 999, ace = 999;
	do {
		gotoxy(12, 1 + V.Op); cout << ">>";
		tecla = _getch();
		gotoxy(12, 1 + V.Op); cout << "  ";

		if (tecla == up) V.Op--;
		if (tecla == down) V.Op++;
		if (V.Op == 0) V.Op = 7;
		if (V.Op == 6 && tecla == up) V.Op = 5;
		if (V.Op == 6 && tecla == down) V.Op = 7;
		if (V.Op == 8) V.Op = 1;
		if (tecla == enter && V.Op != 7) {
			Val[V.Op] = !Val[V.Op];
			col = (Val[V.Op] == false) ? 12 : 10;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
			gotoxy(17, 1 + V.Op);
			if (V.Op == 1) cout << "Distancia";
			if (V.Op == 2) cout << "Velocidad Final";
			if (V.Op == 3) cout << "Velocidad Inicial";
			if (V.Op == 4) cout << "Tiempo";
			if (V.Op == 5) cout << "Aceleracion";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
	} while (tecla != enter || V.Op != 7);
	int aux = 0;
	for (int i = 0; i < 6; i++) {
		aux += Val[i];
	}
	if (aux < 3 || aux == 5) {
		cout << "Datos incorrectos";
		system("pause>null");
		system("cls");
		goto inicio;
	}
	Cursor(true);
	gotoxy(0, 13);
	if (Val[1]) { cout << "\t Ingrese la Distancia (metros): "; cin >> dis; }
	if (Val[2]) { cout << "\t Ingrese la V. Final (m/s): "; cin >> vef; }
	if (Val[3]) { cout << "\t Ingrese la V. Inicial (m/s): "; cin >> vei; }
	if (Val[4]) { cout << "\t Ingrese el Tiempo (segundos): "; cin >> tie; }
	if (Val[5]) { cout << "\t Ingrese la Aceleracion (m/s^2): "; cin >> ace; }
	Cursor(false);
	system("cls");

	//CALCULAR

	if (!Val[1] && !Val[2]) dis = (vei*tie) + (ace*tie*tie / 2);
	if (!Val[1] && !Val[3]) vei = vef - (ace*tie);
	if (!Val[1] && !Val[4]) tie = (vef - vei) / ace;
	if (!Val[1] && !Val[5]) ace = (vef - vei) / tie;
	if (!Val[2] && !Val[3]) vei = (dis - (ace*tie*tie / 2)) / tie;
	if (!Val[2] && !Val[4]) vef = sqrt(pow(vei, 2) + (2 * ace*dis));
	if (!Val[2] && !Val[5]) ace = (2 * (dis - (vei*tie))) / (tie*tie);
	if (!Val[3] && !Val[4]) vei = sqrt(pow(vef, 2) - (2 * ace*dis));;
	if (!Val[3] && !Val[5]) vei = (2 * dis / tie) - vef;
	if (!Val[4] && !Val[5]) ace = (pow(vef, 2) - pow(vei, 2)) / (2 * dis);

	if (dis == 999) dis = (vei*tie) + ace * tie*tie / 2;
	if (vef == 999) vef = vei + (ace*tie);
	if (vei == 999) vei = vef - (ace*tie);
	if (tie == 999 && ace == 0) tie = dis / vei;
	if (tie == 999) tie = (vef - vei) / ace;
	if (ace == 999) ace = (vef - vei) / tie;

	cout << "\t Distancia: " << dis << " m" << endl;
	cout << "\t Velocidad Final: " << vef << " m/s" << endl;
	cout << "\t Velocidad Inicial: " << vei << " m/s" << endl;
	cout << "\t Tiempo: " << tie << " s" << endl;
	cout << "\t Aceleracion: " << ace << " m/s^2" << endl;
	cout << "\n\t\t Guardar datos" << endl;
	cout << "\t\t Menu Principal" << endl;
	Elegir(13, 6, 2);

	if (V.Op == 1) {
		ofstream archivo;
		string nombre;
		cin.clear();
		cin.ignore();
		gotoxy(9, 10); cout << "Escriba el nombre del archivo: ";
		Cursor(true);
		getline(cin, nombre);
		Cursor(false);

		archivo.open(nombre.c_str(), ios::out);
		if (archivo.fail()) exit(1);
		archivo << "Distancia:         " << dis << " m" << endl;
		archivo << "Velocidad Final:   " << vef << " m/s" << endl;
		archivo << "Velocidad Inicial: " << vei << " m/s" << endl;
		archivo << "Tiempo:            " << tie << " s" << endl;
		archivo << "Aceleracion:       " << ace << " m/s^2" << endl;
		archivo.close();
		cout << "\t Archivo creado";
		system("pause>null");
	}
	main();
}

void LeyNewton() {
	int nf;
	char sig;
	float fr, fue, ang, mk, ace, mas, sdfx = 0, sdfy = 0;
	float *fuerza, *angulo;
	cout << "\tQue quiere calcular?\n" << endl
		<< "\t\t Fuerza" << endl
		<< "\t\t Masa" << endl
		<< "\t\t Aceleracion";
	Elegir(12, 2, 3);

	switch (V.Op) {
		//Fuerza
	case 1:
		gotoxy(9, 6);
		Cursor(true);
		cout << "Ingrese la aceleracion (con signo): ";
		cin >> ace;
		cout << "\t Ingrese la masa (kg): ";
		cin >> mas;
		cout << "\t Ingrese el coeficiente de rozamiento: ";
		cin >> mk;
		fue = mas * (ace + mk * g);
		cout << "\n\t La fuerza es: " << fue << " N" << endl;
		cout << "\n\t\t Guardar datos" << endl;
		cout << "\t\t Menu Principal" << endl;
		Cursor(false);
		Elegir(13, 12, 2);

		if (V.Op == 1) {
			ofstream archivo;
			string nombre;
			cin.clear();
			cin.ignore();
			gotoxy(9, 15); cout << "Escriba el nombre del archivo: ";
			Cursor(true);
			getline(cin, nombre);
			Cursor(false);

			archivo.open(nombre.c_str(), ios::out);
			if (archivo.fail()) exit(1);
			archivo << "Masa:        " << mas << " kg" << endl;
			archivo << "Aceleracion: " << ace << " m/s^2" << endl;
			archivo << "Fuerza:      " << fue << " N" << endl;
			archivo << "Friccion:    " << -1 * mk*mas*g << " N" << endl;
			archivo.close();
			cout << "\t Archivo creado";
			system("pause>null");
		}
		break;

		//Masa
	case 2:
		gotoxy(9, 6);
		Cursor(true);
		cout << "Ingrese la aceleracion: ";
		cin >> ace;
		cout << "\t Ingrese la fuerza (N): ";
		cin >> fue;
		cout << "\t Ingrese el coeficiente de rozamiento: ";
		cin >> mk;
		mas = fue / (ace + g * mk);
		cout << "\n\t La masa es: " << mas << " kg" << endl;
		cout << "\n\t\t Guardar datos" << endl;
		cout << "\t\t Menu Principal" << endl;
		Cursor(false);
		Elegir(13, 12, 2);

		if (V.Op == 1) {
			ofstream archivo;
			string nombre;
			cin.clear();
			cin.ignore();
			gotoxy(9, 15); cout << "Escriba el nombre del archivo: ";
			Cursor(true);
			getline(cin, nombre);
			Cursor(false);

			archivo.open(nombre.c_str(), ios::out);
			if (archivo.fail()) exit(1);
			archivo << "Masa:        " << mas << " kg" << endl;
			archivo << "Aceleracion: " << ace << " m/s^2" << endl;
			archivo << "Fuerza:      " << fue << " N" << endl;
			archivo << "Friccion:    " << -1 * mk*mas*g << " N" << endl;
			archivo.close();
			cout << "\t Archivo creado";
			system("pause>null");
		}
		break;

		//Aceleracion
	case 3:
		Cursor(true);
		gotoxy(9, 6);
		cout << "Hacia donde sera el eje x positivo? (i = izquierda / d = derecha): ";
		cin >> sig;
		if (sig != 'i') sig = 'd';
		cout << "\t Ingrese el angulo de elevacion (en grados): ";
		cin >> ang;
		cout << "\t Ingrese el numero de fuerzas a ingresar: ";
		cin >> nf;
		fuerza = new float[nf];
		angulo = new float[nf];
		for (int i = 0; i<nf; i++) {
			cout << "\t Ingrese la fuerza " << i + 1 << " seguido de su angulo (respecto al suelo): ";
			cin >> fuerza[i] >> angulo[i];
			sdfy += fuerza[i] * sin((angulo[i] - ang)*pi / 180);
			sdfx += fuerza[i] * cos((angulo[i] - ang)*pi / 180);
		}
		cout << "\t Ingrese la masa (kg): ";
		cin >> mas;
		cout << "\t Ingrese el coeficiente de rozamiento: ";
		cin >> mk;
		Cursor(false);
		fr = mk * ((g*mas*cos(ang*pi / 180)) - sdfy);
		if (sig == 'i') fr *= -1;
		ace = ((mas*g*sin(ang*pi / 180)) - (mk*(mas*g*cos(ang*pi / 180) - sdfy)) + sdfx) / mas;
		if (((mas*g*sin(ang*pi / 180) + sdfx) < fr) && sig == 'd') ace = 0;
		if (((mas*g*sin(ang*pi / 180) + sdfx) > fr) && sig == 'i') ace = 0;
		if (sig == 'i') ace *= -1;
		system("cls");
		cout << "\t La aceleracion es: " << ace << " m/s^2" << endl;
		cout << "\n\t\t Guardar datos" << endl;
		cout << "\t\t Menu Principal" << endl;
		Elegir(13, 2, 2);
		if (V.Op == 1) {
			ofstream archivo;
			string nombre;
			cin.clear();
			cin.ignore();
			gotoxy(9, 6); cout << "Escriba el nombre del archivo: ";
			Cursor(true);
			getline(cin, nombre);
			Cursor(false);

			archivo.open(nombre.c_str(), ios::out);
			if (archivo.fail()) exit(1);
			archivo << "Masa:        " << mas << " kg" << endl;
			archivo << "Aceleracion: " << ace << " m/s^2" << endl;
			archivo << "Fuerzas (X):  " << sdfx << " N" << endl;
			archivo << "Fuerzas (Y):  " << sdfy << " N" << endl;
			archivo << "Coeficiente: " << mk;
			archivo << "Friccion:    " << -1 * fr << " N" << endl;
			archivo.close();
			cout << "\t Archivo creado";
			system("pause>null");
		}
	}
	main();
}

void Elegir(int x, int y, int op) {
	int tecla;
	V.Op = 1;
	do {
		gotoxy(x, y + V.Op - 1); cout << ">>";
		tecla = _getch();
		gotoxy(x, y + V.Op - 1); cout << "  ";

		if (tecla == up) V.Op--;
		if (tecla == down) V.Op++;

		if (V.Op == 0) V.Op = op;
		if (V.Op == op + 1) V.Op = 1;
	} while (tecla != enter);
}

void gotoxy(int x, int y) {
	HANDLE sc = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(sc, pos);
}

void Cursor(bool Visib) {
	HANDLE sc = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = (Visib) ? TRUE : FALSE;
	SetConsoleCursorInfo(sc, &cci);
}
