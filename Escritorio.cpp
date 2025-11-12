#include <conio.h>
#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define COLUMS 10
#define FILES 5

enum class ArrowDirection{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

enum class FileType{
    TEXT,
    FOLDER,
    CALC,
    IMG,
    NONE
};

class fileProperties{
    string fileName;
    FileType typeOfFile;
    bool adminPriviledges;
    char fileIcon;
};

void clearScreen() {
    cout << endl << endl << endl << endl << endl << endl;
}

void printDesktop(string desktop[FILES][COLUMS],int xCord, int yCord){
    string cursor = " ";
    for(int i = 0; i<FILES; i++){
        for(int j = 0; j<COLUMS; j++){
            cursor = " ";
            if(xCord == j && yCord == i){
                cursor ="a";
                desktop[i][j] = "[" + cursor + "]";
            }else{
                desktop[i][j] = "[ ]";
            }
            cout << desktop[i][j] << "  ";
        }
        cout << endl;
    }
}

void calculateCellPosition(ArrowDirection currentDirection, int &xCellCord, int &yCellCord){
    if(currentDirection == ArrowDirection :: UP && yCellCord != 0){
        yCellCord -= 1;
    }else if(currentDirection == ArrowDirection :: DOWN && yCellCord != 4){
        yCellCord += 1;
    }else if(currentDirection == ArrowDirection :: LEFT && xCellCord != 0){
        xCellCord -= 1;
    }else if(currentDirection == ArrowDirection :: RIGHT && xCellCord != 9){
        xCellCord += 1;
    }
}

ArrowDirection getCurrentDirection(){

    int c = 0;
        switch((c=getch())) {
        case KEY_UP:
            return ArrowDirection::UP;
            break;
        case KEY_DOWN:
            return ArrowDirection::DOWN;
            break;
        case KEY_LEFT:
            return ArrowDirection::LEFT;
            break;
        case KEY_RIGHT:
            return ArrowDirection::RIGHT;
            break;
        default:
            return ArrowDirection::NONE;
            break;
        }
    
}

int main(){
int xCellCoord = 0;
int yCellCoord = 0;

string desktop[FILES][COLUMS];
ArrowDirection desktopMovement = ArrowDirection::NONE;
for(int i = 0; i<5; i++){
    for(int j = 0; j<10; j++){
        desktop[i][j] = "[ ]";
    }
}

while (true){
    printDesktop(desktop,xCellCoord,yCellCoord);
    desktopMovement = getCurrentDirection();
    calculateCellPosition(desktopMovement,xCellCoord,yCellCoord);
    clearScreen();
    }
}