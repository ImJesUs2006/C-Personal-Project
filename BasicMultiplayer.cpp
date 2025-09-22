#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Comdlg32.lib")

#include <iostream>
#include "Disenio.h"
#include <mmsystem.h>
#include "playlist.h"

using namespace std;


int main() {
    ocultarCursor();
    system("mode con: cols=120 lines=35");
    
    Node* playlist = nullptr;
    
    vector<string> misOpciones = {
        "1.- Add songs",
        "2.- AutoSound",
        "3.- Salir "
    };

    vector<string> SongsOpc = {
        "1.- Agregar cancion",
        "2.- Ver lista",
        "3.- Eliminar cancion",
        "4.- Volver"
    };
    
    int opcion = 0;
    while (true) {
        system("cls");
        Marco(6, 10, 30, 100);
       

        Colorea(14, 0);                                   
  posicion(8,12);cout << "                                ##########      ";
  posicion(9,12);cout << "                      ####################";      
  posicion(10,12);cout << "                ##########################" ; Colorea(12, 0);     
  posicion(11,12);cout << "                ########################## "; Colorea(15, 0);Colorea(14, 0);       
  posicion(12,12);cout << "                ##########################  " ; Colorea(14, 0);    
  posicion(13,12);cout<<  "                ########################## ";Colorea(14,0);     
  posicion(14,12);cout<<  "                ##############        ####";Colorea(5,0);      
  posicion(15,12);cout<<  "                ####                    ##" ;Colorea(14,0);     
  posicion(16,12);cout<<  "                ####                    ##" ;Colorea(14,0);     
  posicion(17,12);cout<<  "                ####                    ## ";Colorea(14,0);     
  posicion(18,12);cout<<  "                ####                    ## ";Colorea(7,0);     
  posicion(19,12);cout<<  "                ####                    ##";Colorea(5,0);      
  posicion(20,12);cout<<  "                ####                    ## ";Colorea(14,0);     
  posicion(21,12);cout<<  "                ####                    ## ";Colorea(5,0);     
  posicion(22,12);cout<<  "                ####                  #### " ;Colorea(14,0);    
  posicion(23,12);cout<<  "                ####          ############";Colorea(14,0);      
  posicion(24,12);cout<<  "              ######        ##############";Colorea(14,0);      
  posicion(25,12);cout<<  "      ##############        ##############";Colorea(7,0);      
  posicion(26,12);cout<<  "    ################        ##############";Colorea(14,0);      
  posicion(27,12);cout<<  "    ################          ########## " ;Colorea(5,0);      
  posicion(28,12);cout<<  "      ############                       " ;Colorea(14,0);      
  posicion(29,12);cout<<  "      ##########                         " ;Colorea(9,0);      
                                                

    // Restaurar color normal
    Colorea(15, 0);
        Marco(15, 70, 29, 95); 
        Colorea(12,7);positioncenter("Bienvenido de Nuevo", 16, 70, 95);
        Colorea(15, 0);
        
          limpiarEventosMouse();
        Menu(opcion, misOpciones);
        opcion = Click(misOpciones);

        if (opcion == 3) {
            // Liberar la memoria de la lista antes de salir
              while (playlist != nullptr) {
                Node* temp = playlist;
                playlist = playlist->next;
                delete temp;
              }
            break;
        }

       

        switch (opcion) {
            case 1: {
                int Sopc = 0;
                while (true) {
                    system("cls"); // Limpiar para el submenú
                    // Dibuja el marco de la ventana de canciones
                    Marco(6, 10, 30, 110);
                    Marco(4, 10, 6, 110);
                    Marco(4, 105, 6, 110);
                    posicion(5, 108); cout << "X";
                     Colorea(14, 0);
        posicion(2, 15); cout << R"(        .7)";
        posicion(3, 15); cout << R"(       .'/)";
        posicion(4, 15); cout << R"(      / /)";
        posicion(5, 15); cout << R"(     / /)";
        posicion(6, 15); cout << R"(    / /)";
        posicion(7, 15); cout << R"(   / /)";
        posicion(8, 15); cout << R"(  / /)";
        posicion(9, 15); cout << R"( / /)";
        posicion(10, 15); cout << R"(/ /)";
        posicion(11, 15); cout << R"( / /)";
        posicion(12, 15); cout << R"( __|/)";
        posicion(13, 15); cout << R"(,-\__\)";
        posicion(14, 15); cout << R"(|f-"Y\|)";
        posicion(15, 15); cout << R"(\()7L/)";
        posicion(16, 15); cout << R"( cgD               __ _)";
        posicion(17, 15); cout << R"( |\(             .'  Y '&gt;,)";
        posicion(18, 15); cout << R"(  \ \           / _  _   \)";
        posicion(19, 15); cout << R"(   \\         )(_) (_)(|})";
        posicion(20, 15); cout << R"(   \\        {  4A   } /)";
        posicion(21, 15); cout << R"(    \\        \uLuJJ/\l)";
        posicion(22, 15); cout << R"(    \\        |3   p)/)";
        posicion(23, 15); cout << R"(     \\___ __________   /nnm_n//)";
        posicion(24, 15); cout << R"(     c7___-__,__-)\,__)(". \_&gt;-<_/D)";
        posicion(25, 15); cout << R"(           //V   \_"-._.__G G_c__.-__<"/ ( \)";
        posicion(26, 15); cout << R"(                 <"-._>__-,G_.___)\   \7\)";
        posicion(27, 15); cout << R"(                ("-.__.| \"<.__.-" )   \ \)";
        posicion(28, 15); cout << R"(                |"-.__"\  |"-.__.-".\   \ \)";
        posicion(29, 15); cout << R"(                ("-.__"". \"-.__.-".|    \_\)";
        posicion(30, 15); cout << R"(                \"-.__""|!|"-.__.-".)     \ \)";
        posicion(31, 15); cout << R"(                 "-.__""\_|"-.__.-"./      \ l)";
        posicion(32, 15); cout << R"(                  ".__"">G&gt;-.__.-"&gt;      .--,_)";
        posicion(33, 15); cout << R"(                       ""  G)";
                    positioncenter("Menu de Canciones", 5, 10, 110);
            
                        
                       limpiarEventosMouse();
                    Menu(Sopc, SongsOpc);
                    Sopc = Click(SongsOpc);
                   

                    if (Sopc == 4) { // Opcion para volver al menu principal
                        break;
                    }
                    
                    system("cls"); // Limpiar de nuevo para los resultados
                    Marco(6, 10, 30, 110);
                    Marco(4, 10, 6, 110);
                    Marco(4, 105, 6, 110);
                    posicion(5, 108); cout << "X";
                    positioncenter(SongsOpc[Sopc - 1], 5, 10, 110);
                    

                    
                    switch (Sopc) {
                        case 1: { // Agregar cancion
                            string filePath = seleccionarArchivo();
                            if (!filePath.empty()) {
                                string fileName = filePath.substr(filePath.find_last_of("\\") + 1);
                                Song nuevaCancion = {fileName, "Desconocido", filePath};
                                agregarCancion(playlist, nuevaCancion); 
                                posicion(10, 12); cout << "Cancion agregada: " << fileName;

 posicion(11, 12); cout<< "                                     .--.                  .---.   ";
 posicion(12, 12); cout<< "                                 .---|__|         .-.     |~~~|   ";
 posicion(13, 12); cout<< "                              .--|===|--|_        |_|     |~~~|--.";
 posicion(14, 12); cout<< "                              |  |===|  |'\    .---!~|  .--|   |--|";
 posicion(15, 12); cout<< "                              |%%|   |  |.'\   |===| |--|%%|   |  |";
 posicion(16, 12); cout<< "                              |%%|   |  |\.'\   |   | |__|  |   |  |";
 posicion(17, 12); cout<< "                              |  |   |  | \  \  |===| |==|  |   |  |";
 posicion(18, 12); cout<< "                              |  |   |__|  \.'\ |   |_|__|  |~~~|__|";
 posicion(19, 12); cout<< "                              |  |===|--|   \.'\|===|~|--|%%|~~~|--|";
 posicion(20, 12); cout<< "                              ^--^---'--^    `-'`---^-^--^--^---'--'";
                            } else {
                                posicion(10, 12); cout << "No se selecciono ningun archivo.";
                               esperar_clic_cerrar(); 
                            }
                            break;
                        }
                        case 2: // Ver lista
                            mostrarLista(playlist);
                            break;
                        case 3: { // Eliminar cancion
                            mostrarLista(playlist);
                            posicion(20, 12); cout << "Ingresa el numero de cancion a eliminar: ";
                            int num;
                            cin >> num;
                            eliminarCancion(playlist, num);
                            break;
                        }
                    }
                    esperar_clic_cerrar();
                }
                break;
            }
            case 2:
                   
                // Lógica para AutoSound
                reproducirLista(playlist);
                 esperar_clic_cerrar();
                break;
        }
       
    }
    return 0;
}
