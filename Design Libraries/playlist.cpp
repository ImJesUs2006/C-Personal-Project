#include <iostream>
#include "playlist.h"
using namespace std;

std::string seleccionarArchivo() {
    OPENFILENAMEA ofn; // Usar OPENFILENAMEA para la version ANSI
    char szFile[260] = {0}; // Usar char para un buffer de caracteres
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Archivos de Audio (*.mp3;*.wav)\0*.mp3;*.wav\0Todos los archivos (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrTitle = "Selecciona un archivo de audio";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn) == TRUE) { // Llamar a GetOpenFileNameA
        return std::string(ofn.lpstrFile);
    } else {
        return "";
    }
}

// Función para agregar una canción
void agregarCancion(Node*& head, Song nuevaCancion) {
    Node* newNode = new Node;
    newNode->data = nuevaCancion;
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}
// Función para mostrar la lista
void mostrarLista(Node* head) {
    if (head == nullptr) {
        posicion(10, 12); std::cout << "La lista esta vacia.";
        return;
    }
    int fila = 10;
    Node* temp = head;
    posicion(fila, 12); std::cout << "Lista de Reproduccion:";
    fila++;
    int count = 1;
    while (temp != nullptr) {
        posicion(fila, 12); std::cout << count << ". " << temp->data.name;
        temp = temp->next;
        fila++;
        count++;
    }
}
// Función para eliminar una canción
void eliminarCancion(Node*& head, int numero) {
    if (head == nullptr) {
        posicion(10, 12); std::cout << "La lista esta vacia, no hay nada que eliminar.";
        return;
    }
    Node* temp = head;
    Node* prev = nullptr;
    if (numero == 1) {
        head = temp->next;
        delete temp;
        posicion(10, 12); std::cout << "Cancion eliminada.";
        return;
    }
    int count = 1;
    while (temp != nullptr && count != numero) {
        prev = temp;
        temp = temp->next;
        count++;
    }
    if (temp == nullptr) {
        posicion(10, 12); std::cout << "Numero de cancion no valido.";
        return;
    }
    prev->next = temp->next;
    delete temp;
    posicion(10, 12); std::cout << "Cancion eliminada.";
}
// Función para reproducir la lista


void reproducirLista(Node* head) {
    if (head == nullptr) {
        posicion(10, 12);
        std::cout << "La lista esta vacia.";
        // No necesitas esperar_clic_cerrar() aquí, ya que la función principal lo hará.
        Sleep(1500); // Una pequeña pausa es mejor
        return;
    }

    // === Dibuja la interfaz (sin cambios) ===
    system("cls");
    Marco(6, 10, 30, 110);
    Marco(4, 10, 6, 110);
    Marco(4, 105, 6, 110);
    Marco(28, 10, 30, 110); // Corregí el marco inferior para que sea de 28 a 30
    posicion(5, 108); cout << "X";
    Colorea(15, 0);
    positioncenter("Reproductor de musica", 5, 10, 110);
    
    posicion(8, 12); cout << "Fila de reproduccion.";
    posicion(10,12);cout << "  /\\^/`\\  ";
    posicion(11,12);cout << " | \\/   |  ";
    posicion(12,12);cout << " | |    |  ";
    posicion(13,12);cout << "  \\ \\   /   ";
    posicion(14,12);cout << "  '\\//'   ";
    posicion(15,12);cout << "    ||     ";
    posicion(16,12);cout << "    ||    ";
    posicion(17,12);cout << "    ||     ";
    posicion(18,12);cout << "    ||  ,  "; 
    posicion(19,12);cout << " |\\  ||  |\\ ";
    posicion(20,12);cout << " | | ||  | |";
    posicion(21,12);cout << " | | || / / ";
    posicion(22,12);cout << "  \\ \\||/ /  ";
    posicion(23,12);cout << "  `\\//`   ";
    
    // Controles en pantalla
    int filaControles = 26;
    int inicioColumna = 12;
    Colorea(10, 0); posicion(filaControles, inicioColumna);      std::cout << "|>";  // Play
    Colorea(14, 0); posicion(filaControles, inicioColumna + 5);  std::cout << "||";  // Pausa
    Colorea(12, 0); posicion(filaControles, inicioColumna + 10); std::cout << "|#|"; // Detener
    Colorea(15, 0); posicion(filaControles, inicioColumna + 15); std::cout << ">>";  // Siguiente
    
    Node* currentSong = head;

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode;
    GetConsoleMode(hInput, &prevMode);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    while (currentSong != nullptr) {
        std::string openCommand = "open \"" + currentSong->data.filePath + "\" alias audiofile";
        mciSendStringA(openCommand.c_str(), NULL, 0, NULL);
        mciSendStringA("play audiofile", NULL, 0, NULL);
        
        char buffer[256];
        mciSendStringA("status audiofile length", buffer, sizeof(buffer), NULL);
        long totalLength = atol(buffer);

        // Limpia la línea antes de escribir el nuevo nombre de la canción
        posicion(7, 12); std::cout << "                                                  ";
        posicion(7, 12); std::cout << "Reproduciendo: " << currentSong->data.name;
        
        bool songPlaying = true;
        
        while (songPlaying) {
            // ---> CAMBIO 1: Lógica no bloqueante para leer los clics <---
            DWORD eventsAvailable;
            GetNumberOfConsoleInputEvents(hInput, &eventsAvailable);

            if (eventsAvailable > 0) {
                INPUT_RECORD record;
                DWORD eventsRead;
                ReadConsoleInput(hInput, &record, 1, &eventsRead); // Solo leemos si sabemos que hay algo

                if (record.EventType == MOUSE_EVENT) {
                    MOUSE_EVENT_RECORD mer = record.Event.MouseEvent;
                    // ---> CAMBIO 2: Añadimos el filtro de dwEventFlags para evitar falsos clics <---
                    if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mer.dwEventFlags == 0) {
                        int mouseX = mer.dwMousePosition.X;
                        int mouseY = mer.dwMousePosition.Y;

                        // ---> CAMBIO 3: Coordenadas de los botones corregidas <---
                        if (mouseY == filaControles) {
                            // Clic en el boton de Play
                            if (mouseX >= inicioColumna && mouseX <= inicioColumna + 1) {
                                mciSendStringA("resume audiofile", NULL, 0, NULL);
                            // Clic en el boton de Pausa
                            } else if (mouseX >= inicioColumna + 5 && mouseX <= inicioColumna + 6) {
                                mciSendStringA("pause audiofile", NULL, 0, NULL);
                            // Clic en el boton de Detener
                            } else if (mouseX >= inicioColumna + 10 && mouseX <= inicioColumna + 12) {
                                mciSendStringA("stop audiofile", NULL, 0, NULL);
                                songPlaying = false; // Detiene la canción actual, pero la lista continúa
                            // Clic en el boton de Siguiente
                            } else if (mouseX >= inicioColumna + 15 && mouseX <= inicioColumna + 16) {
                                songPlaying = false; // Termina el bucle de esta canción para pasar a la siguiente
                            }
                        }
                        // Clic en la X para salir
                        else if (mouseY == 5 && mouseX >= 108 && mouseX <= 109) {
                            songPlaying = false;
                            currentSong = nullptr; // Termina la reproducción de toda la lista
                        }
                    }
                }
            }

            // El resto del bucle se ejecuta continuamente
            mciSendStringA("status audiofile position", buffer, sizeof(buffer), NULL);
            long currentPosition = atol(buffer);
            if (totalLength > 0) {
                 double progress = (double)currentPosition / totalLength;
                 int barLength = (int)(progress * 40);
                 
                 posicion(25, 40); Colorea(15, 0); std::cout << "[";
                 for (int i = 0; i < 40; ++i) {
                     std::cout << (i < barLength ? "#" : " ");
                 }
                 std::cout << "]";
            }

            // Verificar si la canción ha terminado
            mciSendStringA("status audiofile mode", buffer, sizeof(buffer), NULL);
            if (strcmp(buffer, "stopped") == 0 && currentPosition > 0) {
                songPlaying = false;
            }

            Sleep(100); // Pausa para no sobrecargar el CPU
        }
        
        mciSendStringA("close audiofile", NULL, 0, NULL);

        if (currentSong == nullptr) {
            break; // Salir del bucle principal si se hizo clic en la 'X'
        }

        currentSong = currentSong->next;
    }
    
    SetConsoleMode(hInput, prevMode);
    posicion(24, 17); std::cout << "Fin de la lista de reproduccion.";
    Sleep(2000); // Espera 2 segundos antes de volver
}
