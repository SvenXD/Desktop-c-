#include <conio.h>
#include <cstdlib>
#include <bits/stdc++.h>
#ifdef _WIN32 
#include <Windows.h>
#define SET_CONSOLE_UTF8 SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8); //Set console output to UTF-8.
#endif // _WIN32 

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

#define COLUMS 10
#define FILES 5

string fileTypeString[5] = {"Text","Folder","Calc","Img","None"};
string textFilesMessages[49] = {"Hello World!"};

enum class KeySelected{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    ESC,
    NONE
};

enum class DesktopState{
    NAVEGATION,
    COMMANDS
};

enum class FileType{
    TEXT,
    FOLDER,
    CALC,
    IMG,
    TRASH,
    NONE
};

class FileProperties{
public:
    string fileName;
    FileType typeOfFile;
    bool adminPriviledges;
    string fileIcon;
    int id;

    bool isEmpty(){
        return fileName.empty();
    }
};

void clearScreen() {
    system("cls");
}

void setupDefaultFiles(FileProperties files[FILES][COLUMS]) {
    files[0][0].fileName = "Readme.txt";
    files[0][0].typeOfFile = FileType::TEXT;
    files[0][0].adminPriviledges = false;
    files[0][0].fileIcon = u8"📝";
    files[0][0].id = 0;

    files[1][0].fileName = "Documents";
    files[1][0].typeOfFile = FileType::FOLDER;
    files[1][0].adminPriviledges = false;
    files[1][0].fileIcon = u8"📁";
    
    files[2][0].fileName = "Photo.jpg";
    files[2][0].typeOfFile = FileType::IMG;
    files[2][0].adminPriviledges = false;
    files[2][0].fileIcon = u8"🖼️";

    files[4][0].fileName = "Trash Bin";
    files[4][0].typeOfFile = FileType::TRASH;
    files[4][0].adminPriviledges = true;
    files[4][0].fileIcon = u8"🗑️";
}

void checkAndPrintCellIcon(string desktop[FILES][COLUMS],int i, int j, FileProperties filesManager[FILES][COLUMS]){
    (filesManager[i][j].isEmpty() ? desktop[i][j] = "[ ]" : desktop[i][j] = filesManager[i][j].fileIcon);
}

void printCursorLocation(string desktop[FILES][COLUMS], string cursor, int i, int j){
    desktop[i][j] = "[" + cursor + "]";
}

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

            if(j+1 == COLUMS && i == 0){
              cout << "\t" << filesManager[yCord][xCord].fileName;
            }else if(j+1 == COLUMS && i == 1){
              cout << "\t\t" << filesManager[yCord][xCord].fileIcon;
            }else if(j+1 == COLUMS && i == 2){
                //Placeholder will check if i will do stuff
            }
        }
        cout <<endl;
    }
}

void openContents(string opcion, FileProperties &filesManager, int yCellCord, int xCellCord){
    if(opcion == "z"){
        if (filesManager.isEmpty()) {
            string name;
            cout << "Introduzca el nómbre de su archivo: ";
            cin >> name;
            filesManager.fileName = name;
            filesManager.adminPriviledges = false;
            if (name.substr(name.length() - 4) == ".txt") {
                filesManager.typeOfFile = FileType::TEXT;
                filesManager.id = yCellCord + xCellCord + (yCellCord*10);
                filesManager.fileIcon = u8"📝";
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
        cout << "Eliminando archivo..." << endl;
        if(filesManager.typeOfFile == FileType::TEXT) 
            textFilesMessages[filesManager.id] = "";
        FileProperties fileEmpty;
        filesManager = fileEmpty;
    }
}


void printAndAskOptions(FileProperties &filesManager, int yCellCord, int xCellCord){
    string opcion;
    cout << "___________________________________" << endl;
    cout << "\t Opciones" << endl;
    if (!filesManager.isEmpty()) {
        cout << "\t Abrir archivo \t\t z" << endl;
        if(filesManager.typeOfFile == FileType::TEXT){
            cout << "\t Editar Texto \t\t t" << endl;
        }
        cout << "\t Borrar archivo \t d" << endl;
        cout << "\t Ver propiedades \t x" << endl;   
    } else {  
        cout << "\t Crear archivo \t\t z" << endl;
    }

    cout << "___________________________________" << endl;
    // Limpiar el buffer ANTES de usar ci
    cout << "Introduzca la opción: " << endl;
    getline(cin, opcion);
    
    cout << "------------------------------------" << endl;   
    openContents(opcion, filesManager, yCellCord, xCellCord);
    cout << "------------------------------------" << endl;
    system("pause");
}


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

KeySelected getCurrentDirection(){
    int c = 0;
        switch((c=getch())) {
        case KEY_UP:
            return KeySelected::UP;
            break;
        case KEY_DOWN:
            return KeySelected::DOWN;
            break;
        case KEY_LEFT:
            return KeySelected::LEFT;
            break;
        case KEY_RIGHT:
            return KeySelected::RIGHT;
            break;
        case KEY_ENTER:
            return KeySelected::ENTER;
            break;
        case KEY_ESC:
            return KeySelected::ESC;
            break;
        default:
            return KeySelected::NONE;
            break;
        }
}

int main(){
#ifdef _WIN32
    SET_CONSOLE_UTF8
#endif

int xCellCoord = 1;
int yCellCoord = 0;

string desktop[FILES][COLUMS];
FileProperties filesManager[FILES][COLUMS];

KeySelected keyboardReader = KeySelected::NONE;
DesktopState desktopState = DesktopState::NAVEGATION;

for(int i = 0; i<5; i++){
    for(int j = 0; j<10; j++){
        desktop[i][j] = "[ ]";
    }
}

setupDefaultFiles(filesManager);
    do {
    if(keyboardReader!= KeySelected::ENTER){
        printDesktop(desktop,xCellCoord,yCellCoord,filesManager);
        keyboardReader = getCurrentDirection();

    }else{
        desktopState = DesktopState::NAVEGATION;
        keyboardReader = KeySelected::NONE;
        printAndAskOptions(filesManager[yCellCoord][xCellCoord], yCellCoord, xCellCoord);
    }
    calculateCellPosition(keyboardReader,xCellCoord,yCellCoord);
    clearScreen();
    } while (keyboardReader != KeySelected::ESC);
     
}