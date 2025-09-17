#include "Disenio.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

// === Definiciones de las funciones de diseño ===

void color (int x){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void posicion(int Ren, int col) {
    COORD coordenada;
    coordenada.X = col;
    coordenada.Y = Ren;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenada);
}

void positioncenter(string texto, int fila, int colInicio, int colFin) {
    int longitud = texto.length();
    int anchoMarco = colFin - colInicio;
    int columna = colInicio + (anchoMarco - longitud) / 2;
    posicion(fila, columna);
    cout << texto;
}

void Marco(int x, int y, int j, int k) {
    posicion(x, y); cout << (char)201;
    posicion(x, k); cout << (char)187;
    posicion(j, y); cout << (char)200;
    posicion(j, k); cout << (char)188;
    for (int i = y + 1; i < k; i++) {
        posicion(x, i); cout << (char)205;
        posicion(j, i); cout << (char)205;
    }
    for (int i = x + 1; i < j; i++) {
        posicion(i, y); cout << (char)186;
        posicion(i, k); cout << (char)186;
    }
}

void ocultarCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Colorea(int texto, int fondo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int atributo = (fondo << 4) | texto;
    SetConsoleTextAttribute(hConsole, atributo);
}

void Menu(int opcion, const vector<string>& opciones) {
    int totalOpciones = opciones.size();
    int alturaMarco = 29 - 15;
    int lineaInicio = 15 + (alturaMarco - totalOpciones) / 2;
    for (int i = 0; i < totalOpciones; i++) {
        if (i + 1 == opcion) {
            Colorea(7, 1);
        } else {
            Colorea(7, 0);
        }
        positioncenter(opciones[i], lineaInicio + i, 70, 95);
    }
    Colorea(7, 0);
}

int Click(const vector<string>& opciones) {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hIn, &prev_mode);
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    INPUT_RECORD InputRecord;
    DWORD Events;
    COORD coord;
    int opcionSeleccionada = -1;
    int totalOpciones = opciones.size();
    int alturaMarco = 29 - 15;
    int lineaInicio = 15 + (alturaMarco - totalOpciones) / 2;

    while (true) {
        ReadConsoleInput(hIn, &InputRecord, 1, &Events);
        if (InputRecord.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mer = InputRecord.Event.MouseEvent;
            // <-- ¡LA CORRECCIÓN ESTÁ AQUÍ! -->
            // Solo reacciona si el botón izquierdo se presiona Y no es un evento de movimiento.
            if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mer.dwEventFlags == 0) {
                coord = mer.dwMousePosition;
                for (int i = 0; i < totalOpciones; i++) {
                    int filaOpcion = lineaInicio + i;
                    if (coord.Y == filaOpcion && coord.X >= 70 && coord.X <= 95) {
                        opcionSeleccionada = i + 1;
                        SetConsoleMode(hIn, prev_mode);
                        return opcionSeleccionada;
                    }
                }
            }
        }
    }
}

void esperar_clic_cerrar() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode;
    GetConsoleMode(hInput, &prevMode);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    INPUT_RECORD record;
    DWORD count;
    while (true) {
        ReadConsoleInput(hInput, &record, 1, &count);
        if (record.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mer = record.Event.MouseEvent;
            // <-- ¡LA CORRECCIÓN TAMBIÉN VA AQUÍ! -->
            if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mer.dwEventFlags == 0) {
                if (mer.dwMousePosition.Y == 5 && mer.dwMousePosition.X >= 108 && mer.dwMousePosition.X <= 109) {
                    SetConsoleMode(hInput, prevMode);
                    return;
                }
            }
        }
    }
}

// Coloca esta función en tu archivo Disenio.cpp



void limpiarEventosMouse() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    // Esta función de Windows vacía el búfer de entrada de la consola (mouse y teclado)
    FlushConsoleInputBuffer(hInput);
}

/* ejemplo

int main() {
    ocultarCursor();
    system("mode con: cols=120 lines=35");

    vector<string> misOpciones = {
        "1.- Insertar Datos",
        "2.- Imprimir Datos",
        "3.- Eliminar Datos",
        "4.- Buscar Datos",
        "5.- Salir"
    };

    int opcion = 0;
    while (true) {
        system("cls"); // Limpia la pantalla para el menú
        Menu(opcion, misOpciones);
        opcion = Click(misOpciones);

        if (opcion == 5) {
            break;
        }

        // === Lógica de la ventana y el case en el main ===
        system("cls"); // Limpia la pantalla para la ventana
        Marco(6, 10, 30, 110);
        Marco(4, 10, 6, 110);
        Marco(4, 105, 6, 110);
        posicion(5, 108); cout << "X";
          positioncenter("titulo", 5, 10, 110);
        positioncenter(misOpciones[opcion - 1], 5, 10, 110);

        // Aquí se ejecuta la lógica de cada case
        switch (opcion) {
            case 1: {
                posicion(8, 12); cout << "Lógica para Insertar Datos";
                posicion(10, 12); cout << "Ingrese Nombre: ";
                string nombre;
                cin >> nombre; 
                posicion(11, 12); cout << "Ingrese Edad: ";
                int edad;
                cin >> edad;
                posicion(13, 12); cout << "Nombre: " << nombre << ", Edad: " << edad;
                break;
            }
            case 2:
                posicion(8, 12); cout << "Lógica para Imprimir Datos.";
                posicion(10, 12); cout << "Mostrando datos guardados...";
                break;
            case 3:
                posicion(8, 12); cout << "Lógica para Eliminar Datos.";
                posicion(10, 12); cout << "Eliminando datos...";
                break;
            case 4:
                posicion(8, 12); cout << "Lógica para Buscar Datos.";
                posicion(10, 12); cout << "Buscando datos...";
                break;
        }

        // Se llama a la función que espera el clic del mouse
        esperar_clic_cerrar();
    }
    return 0;
}
   */

