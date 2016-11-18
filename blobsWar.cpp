#include <iostream>
using namespace std;

//Funcion usada para que se muestre el tablero en el juego
void tablero(char MatTablero[6][6]) 
{
	for (int iRenglones=0; iRenglones < 6; iRenglones++) {
		for (int iColumnas=0; iColumnas < 6; iColumnas++) 
		{
			cout << MatTablero[iRenglones][iColumnas] << "\t";
		}
		cout << endl;
	}
}

//Se utiliza para que el jugador pueda seleccionar el renglon y columna de la ficha que va mover
void seleccionJugador (char MatTablero[6][6], int &iRenglon, int &iColumna, bool bSeleccion, char &cJugador)
{
	int iJugador;

	iRenglon = 0;
	iColumna = 0;

	if (cJugador == 'X')
	{
		iJugador = 1;
	}
	else
	{ 
		iJugador = 2;
	}

	cout << "Jugador " << iJugador << " " << cJugador << endl;

	while (bSeleccion == false)
	{
		cout << "Renglon -> ";
		cin >> iRenglon;
		cout << "Coumna -> ";
		cin >> iColumna;

		if (MatTablero[iRenglon][iColumna] == cJugador)
		{
			bSeleccion = true;
		}
	}
}

//Esta funcion se encarga de checar si hay algun enemigo en las casillas adyacentes del jugador, y si lo hay lo captura.
//No se llama esta funcion si el jugador perdio el turno o no se movio a una casilla correcta.
void capturaEnemigos (char MatTablero[6][6], int iRenglon, int iColumna, char iJugador, char cOponente) 
{
	if (MatTablero[iRenglon][iColumna-1] == cOponente) 
		(MatTablero[iRenglon][iColumna-1] = iJugador);

	if (MatTablero[iRenglon+1][iColumna] == cOponente)
		(MatTablero[iRenglon+1][iColumna] = iJugador);

	if (MatTablero[iRenglon-1][iColumna] == cOponente)
		(MatTablero[iRenglon-1][iColumna] = iJugador);

	if (MatTablero[iRenglon][iColumna+1] == cOponente)
		(MatTablero[iRenglon][iColumna+1] = iJugador);

	if (MatTablero[iRenglon-1][iColumna-1] == cOponente)
		(MatTablero[iRenglon-1][iColumna-1] = iJugador);

	if (MatTablero[iRenglon+1][iColumna+1] == cOponente)
		(MatTablero[iRenglon+1][iColumna+1] = iJugador);

	if (MatTablero[iRenglon+1][iColumna-1] == cOponente)
		(MatTablero[iRenglon+1][iColumna-1] = iJugador);

	if (MatTablero[iRenglon-1][iColumna+1] == cOponente)
		(MatTablero[iRenglon-1][iColumna+1] = iJugador);
}

//Esta funcion se asegura de que el lugar hacia donde se quiere mover el jugador sea una casilla libre, y si lo es mueve al jugador.
void movimiento (int &iRenglon, int &iColumna, bool bSeleccion, char MatTablero[6][6], char iJugador, bool &bMovio) 
{
	char destino;


	do {
	cout << "a - izq		x - aba		w - arr		d - der" << endl;
	cout << "q - arriba a la izq	e - arriba a la der" << endl;
	cout << "z - abajo a la izq	c - abajo a la der" << endl;
	cin >> destino;
	} while ((destino != 'a') && (destino != 'x') && (destino != 'w') && (destino != 'd') && (destino != 'q')\
		&& (destino != 'e') && (destino != 'z') && (destino != 'c'));

	switch (destino){
		case 'a':
			if (MatTablero[iRenglon][iColumna-1] == '_') {	 
				MatTablero[iRenglon][iColumna-1] = iJugador;	
				iColumna--;
				bMovio = true;
			} else 
				bMovio = false;
			break;
		case 'x': 
			if (MatTablero[iRenglon+1][iColumna] == '_') {
				MatTablero[iRenglon+1][iColumna] = iJugador;
				iRenglon++;
				bMovio = true;
			} else 
				bMovio = false;
			break;
		case 'w':
			if (MatTablero[iRenglon-1][iColumna] == '_') {
				MatTablero[iRenglon-1][iColumna] = iJugador;
				iRenglon--;
				bMovio = true;
			} else
				bMovio = false;
			break;
		case 'd':
			if (MatTablero[iRenglon][iColumna+1] == '_') {
				MatTablero[iRenglon][iColumna+1] = iJugador;
				iColumna++;
				bMovio = true;
			} else
				bMovio = false;
			break;
		case 'q':
			if (MatTablero[iRenglon-1][iColumna-1] == '_') {
				MatTablero[iRenglon-1][iColumna-1] = iJugador;
				iRenglon--;
				iColumna--;
				bMovio = true;
			} else
				bMovio = false;
			break;
		case 'e':
			if (MatTablero[iRenglon-1][iColumna+1] == '_') {
				MatTablero[iRenglon-1][iColumna+1] = iJugador;
				iRenglon--;
				iColumna++;
				bMovio = true;
			} else
				bMovio = false;
			break;
		case 'z':
			if (MatTablero[iRenglon+1][iColumna-1] == '_') {
				MatTablero[iRenglon+1][iColumna-1] = iJugador;
				iRenglon++;
				iColumna--;
				bMovio = true;
			} else
				bMovio = false;
			break;
		case 'c':
			if (MatTablero[iRenglon+1][iColumna+1] == '_') {
				MatTablero[iRenglon+1][iColumna+1] = iJugador;
				iRenglon++;
				iColumna++;
				bMovio = true;
			} else
				bMovio = false;
			break;
		default:
			bMovio = false;
	}
}

//Esta funcion cuenta los puntos de los jugadores cada turno y se asegura de checar si se llenan todas las casillas
//para detener el juego.
void ganador (char MatTablero[6][6], int &iPuntaje1, int &iPuntaje2, bool &bContinuar)
{
	iPuntaje1=0;
	iPuntaje2=0;
	int iCasillas=0;

	for (int ren=0; ren < 6; ren++){
		for (int col=0; col < 6; col++){
			if (MatTablero[ren][col] != '_')
				iCasillas++;
		}
	}

	for (int ren=0; ren < 6; ren++){
		for (int col=0; col < 6; col++){
			if (MatTablero[ren][col] == 'X')
				iPuntaje1++;
			else if (MatTablero[ren][col] == 'O')
				iPuntaje2++;
		}
	}

	if (iCasillas == 36)
		bContinuar = false;
}

//Esta funcion le pregunta al jugador si quiere seguir jugando al final de cada turno
void seguirJugando (bool &bContinuar)
{
	char respuesta;

	do {
		cout << "Seguir (s/n) ->";
		cin >> respuesta;

		respuesta = tolower(respuesta);

		if (respuesta == 'n')
			bContinuar = false;

	} while ((respuesta != 'n') && (respuesta != 's'));
}

//Esta funcion le indica al programa que jugador es el que esta jugando
void turnoJugador (bool &bJugador1, char &iJugador, char &cOponente)
{
	if (bJugador1 == false){
		iJugador = 'X';
		cOponente = 'O';
	} else {
		iJugador = 'O';
		cOponente = 'X';
	}

	bJugador1 = !bJugador1;
}

int main() 
{
	char MatTablero[6][6] = {{'0','1','2','3','4','5'},{'1','X','_','_','_','X'},{'2','_','_','_','_','_'},{'3','_','_','_','_','_'},{'4','_','_','_','_','_'},{'5','O','_','_','_','O'}};
	char cJugador = 'X', cOponente;
	int iRenglon, iColumna, iPuntaje1, iPuntaje2;
	bool bSeleccion = false, bContinuar = true, bJugador1 = true, bMovio = true;

	tablero(MatTablero);

	do
	{
		seleccionJugador(MatTablero, iRenglon, iColumna, bSeleccion, cJugador);
		movimiento(iRenglon, iColumna, bSeleccion, MatTablero, cJugador, bMovio);
		if (bMovio == true) {
		capturaEnemigos(MatTablero, iRenglon, iColumna, cJugador, cOponente);
		}
		tablero(MatTablero);
		ganador(MatTablero, iPuntaje1, iPuntaje2, bContinuar);
		seguirJugando(bContinuar);
		turnoJugador(bJugador1, cJugador, cOponente);
	} while (bContinuar == true);	

	if (iPuntaje1 > iPuntaje2)
		cout << "Jugador 1 X es el ganador con: " << iPuntaje1 << " puntos VS Jugador 2 O con: " << iPuntaje2 << " puntos" << endl;
	else if (iPuntaje2 > iPuntaje1)
		cout << "Jugador 2 O es el ganador con: " << iPuntaje2 << "puntos VS Jugador 1 X con: " << iPuntaje1 << " puntos" << endl;
	else if (iPuntaje1 == iPuntaje2)
		cout << "Empate Jugador 1 X con: " << iPuntaje1 << " puntos y Jugador 2 O con: " << iPuntaje2 << " puntos" << endl;

	return 0;
}