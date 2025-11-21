#include <conio.h>
#include <cstdlib>
#include <bits/stdc++.h>
#include <Windows.h>

using namespace std;

#define SET_CONSOLE_UTF8 SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8);
#ifdef _WIN32 
#endif // _WIN32 

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_Q 113
#define KEY_Q_MAYUS 81

#define COLUMS 10
#define FILES 5

string textFilesMessages[50] = {"Hello World!"};
bool isVscTerminal = true;

enum class KeySelected{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    ESC,
    Q,
    NONE
};

enum class FileType{
    TEXT,
    NONE
};

struct FileProperties{
public:
    string fileName;
    FileType typeOfFile;
    bool adminPriviledges;
    string fileIcon;
    int id;

    /**
     * @brief Verifica si el archivo está vacío
     */
    bool isEmpty(){
        return fileName.empty();
    }
};

/**
 * @brief Limpia la pantalla
 */
void clearScreen() {
    if (isVscTerminal) {
        cout << endl << endl << endl << endl << endl << endl;
    } else {
        system("cls");
    }
}

/**
 * @brief Crea y configura archivos que vendran por defecto en el escritorio
 */
void setupDefaultFiles(FileProperties files[FILES][COLUMS]) {
    files[0][0].fileName = "Readme.txt";
    files[0][0].typeOfFile = FileType::TEXT;
    files[0][0].adminPriviledges = false;
    files[0][0].fileIcon = u8"📝";
    files[0][0].id = 0;
}

/**
 * @brief Configura la terminal para soporte UTF-8 si es necesario
 */
void checkTerminal(){
    if(!isVscTerminal){
#ifdef _WIN32
    SET_CONSOLE_UTF8
#endif
    }
}

/**
 * @brief Decide qué icono mostrar en cada celda del escritorio
 */
void checkAndPrintCellIcon(string desktop[FILES][COLUMS],int i, int j, FileProperties filesManager[FILES][COLUMS]){
    (filesManager[i][j].isEmpty() ? desktop[i][j] = "[ ]" : desktop[i][j] = filesManager[i][j].fileIcon);
}

/**
 * @brief Muestra el cursor (a) en la posición actual del escritorio
 */
void printCursorLocation(string desktop[FILES][COLUMS], string cursor, int i, int j){
    desktop[i][j] = "[" + cursor + "]";
}

/**
 * @brief Muestra las características del archivo seleccionado
 */
void showFileCharacteristics(int j, int i, FileProperties filesManager){
    if(j+1 == COLUMS && i == 0){
        cout << "\t\t" << filesManager.fileName;
    }else if(j+1 == COLUMS && i == 1){
        cout << "\t\t  " << filesManager.fileIcon;
    }else if(j+1 == COLUMS && i == 2 && !filesManager.isEmpty()){
        filesManager.adminPriviledges ? cout << "\t Tiene privilegios de administrador" : cout << "\t\t No tiene privilegios de administrador";
    }
}

/**
 * @brief Elimina el archivo seleccionado y limpia su contenido
 */
void deleteFileSelected(FileProperties &filesManager){
    cout << "Eliminando archivo..." << endl;
    if(filesManager.typeOfFile == FileType::TEXT) 
        textFilesMessages[filesManager.id] = "";
    FileProperties fileEmpty;
    filesManager = fileEmpty;
}

/**
 * @brief Imprime el escritorio, archivos, cursor e información
 */
void printDesktop(string desktop[FILES][COLUMS],int xCord, int yCord, FileProperties filesManager[FILES][COLUMS]){
    string cursor = " ";
    for(int i = 0; i<FILES; i++){
        for(int j = 0; j<COLUMS; j++){
            cursor = " ";
            if(xCord == j && yCord == i && desktop[i][j] == "[ ]"){
                cursor ="a";
                printCursorLocation(desktop,cursor,i,j);
            }else{
                checkAndPrintCellIcon(desktop,i,j,filesManager);
            }
            cout << desktop[i][j] << "  ";
            showFileCharacteristics(j,i,filesManager[yCord][xCord]);
        }
        cout <<endl;
    }
}

/**
 * @brief Abre la opción seleccionada del menú
 */
void openContents(string opcion, FileProperties &filesManager, int yCellCord, int xCellCord){
    //Transforma todas las letras a minusculas
    transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
    
    if(opcion == "z"){
        if (filesManager.isEmpty()) {
            string name;
            cout << "====================================" << endl;   
            cout << "Introduzca el nombre de su archivo:" << endl;
            getline(cin, name);
            filesManager.fileName = name;
            filesManager.adminPriviledges = false;
            if (name.size() >= 4 && name.substr(name.size()-4) == ".txt") {
                filesManager.typeOfFile = FileType::TEXT;
                filesManager.id = xCellCord + yCellCord*10;
                filesManager.fileIcon = u8"📝";
            }else {
            filesManager.typeOfFile = FileType::NONE;
            filesManager.id = xCellCord + yCellCord*10;
            filesManager.fileIcon = u8"📄";  
            }
            cout << "Archivo creado con éxito!" << endl;
        } else {
            if(filesManager.typeOfFile == FileType::TEXT){
                cout << textFilesMessages[filesManager.id] << endl;
            }
        }
    }else if(opcion == "t" &&filesManager.typeOfFile == FileType::TEXT){
        getline(cin,textFilesMessages[filesManager.id]);
    }else if(opcion == "d") {
        deleteFileSelected(filesManager);
    }
}

/**
 * @brief Muestra el menú de opciones disponibles para el archivo
 */
void selectWhatToPrint(FileProperties &filesManager, string &opcion){
    cout << "====================================" << endl;
    cout << "\t Opciones" << endl;
    if (!filesManager.isEmpty()) {
        cout << "\t Abrir archivo \t\t z" << endl;
        if(filesManager.typeOfFile == FileType::TEXT){
            cout << "\t Editar Texto \t\t t" << endl;
        }
        cout << "\t Borrar archivo \t d" << endl;
    } else {  
        cout << "\t Crear archivo \t\t z" << endl;
    }
    
    cout << "====================================" << endl;
    cout << "Introduzca la opción:" << endl;

    getline(cin, opcion);
}

/**
 * @brief Maneja la interacción completa de opciones con el usuario
 */
void printAndAskOptions(FileProperties &filesManager, int yCellCord, int xCellCord){
    string opcion;

    selectWhatToPrint(filesManager,opcion);

    cout << "====================================" << endl;   
    openContents(opcion, filesManager, yCellCord, xCellCord);
    cout << "====================================" << endl;
    if(!isVscTerminal) system("pause");
}

/**
 * @brief Muestra instrucciones de como utilizar el escritorio
 */
void showInstructions(){
    cout << "=== INSTRUCCIONES ===" << endl;
    cout << "Flechas: Mover cursor" << endl;
    cout << "Enter: Seleccionar archivo" << endl;
    cout << "z: Crear/Abrir archivo" << endl;
    cout << "t: Editar texto (archivos .txt)" << endl;
    cout << "d: Eliminar archivo" << endl;
    cout << "q: Ver instrucciones" << endl;
    cout << "ESC: Salir" << endl;
    cout << "=====================" << endl;
}

/**
 * @brief Calcula la nueva posición del cursor según la dirección
 */
void calculateCellPosition(KeySelected currentDirection, int &xCellCord, int &yCellCord){
    if(currentDirection == KeySelected :: UP && yCellCord != 0){
        yCellCord -= 1;
    }else if(currentDirection == KeySelected :: DOWN && yCellCord != 4){
        yCellCord += 1;
    }else if(currentDirection == KeySelected :: LEFT && xCellCord != 0){
        xCellCord -= 1;
    }else if(currentDirection == KeySelected :: RIGHT && xCellCord != 9){
        xCellCord += 1;
    }
}

/**
 * @brief Detecta y regresa la tecla presionada por el usuario
 */
KeySelected getCurrentDirection(){
    switch((getch())) {
        case KEY_UP:
            return KeySelected::UP;
        case KEY_DOWN:
            return KeySelected::DOWN;
        case KEY_LEFT:
            return KeySelected::LEFT;
        case KEY_RIGHT:
            return KeySelected::RIGHT;
        case KEY_ENTER:
            return KeySelected::ENTER;
        case KEY_ESC:
            return KeySelected::ESC;
        case KEY_Q_MAYUS:
            return KeySelected::Q;
        case KEY_Q:
            return KeySelected::Q;
        default:
            return KeySelected::NONE;
    }
}

int main(){
    checkTerminal();
    int xCellCoord = 1;
    int yCellCoord = 0;
    string desktop[FILES][COLUMS];
    FileProperties filesManager[FILES][COLUMS];
    KeySelected keyboardReader = KeySelected::NONE;

    for(int i = 0; i<5; i++){
        for(int j = 0; j<10; j++){
            desktop[i][j] = "[ ]";
        }
    }

    setupDefaultFiles(filesManager);
    cout << "Presiona Q para ver instrucciones" << endl;
    do {
        if(keyboardReader!= KeySelected::ENTER){
            if(keyboardReader == KeySelected::Q){
                showInstructions();
            }
            printDesktop(desktop,xCellCoord,yCellCoord,filesManager);
            keyboardReader = getCurrentDirection();
        }else{
            keyboardReader = KeySelected::NONE;
            printAndAskOptions(filesManager[yCellCoord][xCellCoord], yCellCoord, xCellCoord);
        }
        calculateCellPosition(keyboardReader,xCellCoord,yCellCoord);
        clearScreen();
        if(isVscTerminal){stdin;}
    } while (keyboardReader != KeySelected::ESC);
}