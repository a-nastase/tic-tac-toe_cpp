#include <iostream>

char x[255];
char com;

int game[3][3];

void resetGame() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            game[i][j] = -1;
        }
    }
}

void displayGame() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(game[i][j] == 0) {
                std::cout << "O";
            } else if(game[i][j] == 1) {
                std::cout << "X";
            } else {
                std::cout << " ";
            }
            if(j < 2) {
                std::cout << "|";
            }
        }
        std::cout << "\n-----\n";
    }
}

void getCom() {
    std::cin.getline(x, 255); com = x[0];
    com = tolower(com);
}

void place(int xp, int yp, bool turn) {
    if(turn) {
        game[xp][yp] = 1;
    } else {
        game[xp][yp] = 0;
    }
}

bool checkGame(int turn) {
    for(int i = 0; i < 3; i++) {
        if(game[i][0] == game[i][1] && game[i][1] == game[i][2] && game[i][2] == turn) {
            return true;
        }
    }
    for(int j = 0; j < 3; j++) {
        if(game[0][j] == game[1][j] && game[1][j] == game[2][j] && game[2][j] == turn) {
            return true;
        }
    }
    if(game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[2][2] == turn) {
        return true;
    }
    if(game[2][0] == game[1][1] && game[1][1] == game[0][2] && game[0][2] == turn) {
        return true;
    }
    return false;
}

void tP() {
    resetGame();
    displayGame();
    std::cout << "First player, X\n";
    bool g = true;
    for(int i = 0; i < 9 && g; i++) {
        std::cout << "Coordinates: x -, y |\n";
        int xp, yp; std::cin >> xp >> yp; xp--, yp--;
        while(game[yp][xp] != -1) {
            std::cout << "Already occupied! Try again...\n";
            std::cin >> xp >> yp; xp--; yp--;
        }
        if(i%2 != 0) {
            place(yp, xp, 0);
        } else {
            place(yp, xp, 1);
        }
        displayGame();
        if(checkGame((i+1)%2)) {
            if(i%2 == 0) {
                std::cout << "X won!\n";
            } else {
                std::cout << "O won!\n";
            }
            g = false;
        }
    }
}
int px = -1, py = -1;
void check2(int c) {
    bool f = true;
    for(int i = 0; i < 3 && f; i++) {
        if(game[i][0] == game[i][1] && game[i][0] == c) {
            if(game[i][2] == -1) {
                px = i, py = 2;
                f = false;
            }
        }
        if(game[i][1] == game[i][2] && game[i][1] == c) {
            if(game[i][0] == -1) {
                px = i, py = 0;
                f = false;
            }
        }
        if(game[i][0] == game[i][2] && game[i][0] == c) {
            if(game[i][1] == -1) {
                px = i, py = 1;
                f = false;
            }
        }
    }
    for(int j = 0; j < 3; j++) {
        if(game[0][j] == game[1][j] && game[0][j] == c) {
            if(game[2][j] == -1) {
                px = 2; py = j;
                f = false;
            }
        }
        if(game[1][j] == game[2][j] && game[1][j] == c) {
            if(game[0][j] == -1) {
                px = 0; py = j;
                f = false;
            }
        }
        if(game[0][j] == game[2][j] && game[0][j] == c) {
            if(game[1][j] == -1) {
                px = 1; py = j;
                f = false;
            }
        }
    }
    if(game[0][0] == game[1][1] && game[0][0] == c && game[2][2] == -1) {
        px = 2, py = 2;
    } else if(game[1][1] == game[2][2] && game[1][1] == c && game[0][0] == -1) {
        px = 0, py = 0;
    } else if(game[0][0] == game[2][2] && game[0][0] == c && game[1][1] == -1) {
        px = 1, py = 1;
    } else if(game[2][0] == game[1][1] && game[2][0] == c && game[0][2] == -1) {
        px = 0, py = 2;
    } else if(game[1][1] == game[0][2] && game[1][1] == c && game[2][0] == -1) {
        px = 2, py = 0;
    } else if(game[2][0] == game[0][2] && game[2][0] == c && game[1][1] == -1) {
        px = 1, py = 1;
    }
}

void debug() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            std::cout << game[i][j];
        } std::cout << "\n";
    }
}

void bot() {
    //debug();
    check2(0);
    if(px != -1 && py != -1) {
        place(px, py, 0);
        px = -1, py = -1;
        displayGame();
        if(checkGame(0)) {
            std::cout << "Bot won!\n";
        }
        return;
    }
    check2(1);
    if(px != -1 && py != -1) {
        place(px, py, 0);
        px = -1, py = -1;
        displayGame();
        if(checkGame(0)) {
            std::cout << "Bot won!\n";
        }
        return;
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(game[i][j]==-1) {
                place(i, j, 0);
                displayGame();
                if(checkGame(0)) {
                    std::cout << "Bot won!\n";
                }
                return;
            }
        }
    }
}

void bP() {
    resetGame();
    displayGame();
    //debug();
    std::cout << "Play, x\n";
    for(int i = 0; i < 5; i++) {
        std::cout << "Coordinates: x, y\n";
        int xp, yp; std::cin >> xp >> yp; xp--, yp--;
        while(game[yp][xp]!=-1) {
            std::cout << "Already occupied! Try again...\n";
            std::cin >> xp >> yp; xp--; yp--;
        }
        place(yp, xp, 1);
        displayGame();
        if(checkGame(1)) {
            std::cout << "You won!\n";
        }
        bot();
        if(checkGame(0)) {
            return;
        }
    }
}

int main() {
    std::cout << "Hello and welcome to this game, enter p to start playing\n";
    getCom();
    if(com!='p') {
        return 0;
    }
    std::cout << "Use t to play in two and b to play against a medium bot\n";
    while(com != 'q') {
        getCom();
        switch(com) {
            case 't': tP();
            case 'b': bP();
        }
    }
    return 0;
}
