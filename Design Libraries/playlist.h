#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <commdlg.h>
#include "Disenio.h"

using namespace std;



// Estructuras de la lista enlazada

// ... Tus funciones de Disenio.h aquí ...

// Función para seleccionar un archivo
struct Song {
    string name;
    string artist;
    string filePath;
};
struct Node {
    Song data;
    Node* next;
};
// Función para seleccionar un archivo

string seleccionarArchivo();
void agregarCancion(Node*& playlist, Song nuevaCancion);
void eliminarCancion(Node*& playlist, int num);
void mostrarLista(Node* head);
void reproducirLista(Node* head);


#endif 

