#include <conio.h>
#include <bits/stdc++.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

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
    cout << endl << endl << endl << endl << endl << endl;
}

void setupDefaultFiles(FileProperties files[FILES][COLUMS]) {
    files[0][0].fileName = "Readme.txt";
    files[0][0].typeOfFile = FileType::TEXT;
    files[0][0].adminPriviledges = false;
    files[0][0].fileIcon = "📝";
    files[0][0].id = 0;

    files[1][0].fileName = "Documents";
    files[1][0].typeOfFile = FileType::FOLDER;
    files[1][0].adminPriviledges = false;
    files[1][0].fileIcon = "📁";
    
    files[2][0].fileName = "Photo.jpg";
    files[2][0].typeOfFile = FileType::IMG;
    files[2][0].adminPriviledges = false;
    files[2][0].fileIcon = "🖼️";

    files[4][0].fileName = "Trash Bin";
    files[4][0].typeOfFile = FileType::TRASH;
    files[4][0].adminPriviledges = true;
    files[4][0].fileIcon = "🗑️";
}

void checkAndPrintCellIcon(string desktop[FILES][COLUMS],int i, int j,FileProperties filesManager[FILES][COLUMS]){
    (filesManager[i][j].isEmpty() ? desktop[i][j] = "[ ]" : desktop[i][j] = filesManager[i][j].fileIcon);
}

void printCursorLocation(string desktop[FILES][COLUMS], string cursor, int i, int j){
    desktop[i][j] = "[" + cursor + "]";
}

void printDesktop(string desktop[FILES][COLUMS],int xCord, int yCord,FileProperties filesManager[FILES][COLUMS]){
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

void openContents(string opcion, FileProperties filesManager){
    if(opcion == "z"){
        if(filesManager.typeOfFile == FileType::TEXT){
            cout << "------------------------------------" << endl;
            cout << textFilesMessages[filesManager.id] << endl;
            cout << "------------------------------------" << endl;
        }
    }else if(opcion == "t" &&filesManager.typeOfFile == FileType::TEXT){

       getline(cin,textFilesMessages[filesManager.id]);
    }
}

void printAndAskOptions(FileProperties filesManager){
    string opcion;
    cout << "___________________________________" << endl;
    cout << "\t Opciones" << endl;
    cout << "\t Abrir archivo \t\t z" << endl;
    if(filesManager.typeOfFile == FileType::TEXT){
    cout << "\t Editar Texto \t\t t" << endl;
    }
    cout << "\t Borrar archivo \t d" << endl;
    cout << "\t Ver propiedades \t x" << endl;

    // Limpiar el buffer ANTES de usar ci

    getline(cin, opcion);

    openContents(opcion,filesManager);
    
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
        default:
            return KeySelected::NONE;
            break;
        }
}

int main(){

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

while (true){
    if(keyboardReader!= KeySelected::ENTER){
        printDesktop(desktop,xCellCoord,yCellCoord,filesManager);
        keyboardReader = getCurrentDirection();

    }else{
        desktopState = DesktopState::NAVEGATION;
        keyboardReader = KeySelected::NONE;
        printAndAskOptions(filesManager[yCellCoord][xCellCoord]);
    }
    calculateCellPosition(keyboardReader,xCellCoord,yCellCoord);
    clearScreen();
    }
}