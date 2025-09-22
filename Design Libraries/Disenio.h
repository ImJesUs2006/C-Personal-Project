#ifndef DISENIO_H
#define DISENIO_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

// === Declaraciones de las funciones ===
void color (int x);
void posicion(int Ren, int col);
void positioncenter(string texto, int fila, int colInicio, int colFin);
void Marco(int x, int y, int j, int k);
void ocultarCursor();
void Colorea(int texto, int fondo);
void Menu(int opcion, const vector<string>& opciones);
int Click(const vector<string>& opciones);
void esperar_clic_cerrar();
void limpiarEventosMouse();

#endif // DISENIO_H
