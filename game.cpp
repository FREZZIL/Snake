#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>
using namespace std;

bool game = false;
bool gameover;
const int width = 40;
const int height = 20;
int x, y, fruitx, fruity, score;
enum edur { STOP = 0, LEFT, RIGHT, UP, DOWN };
edur dir;
int tailx[100], taily[100];
int ntail;
int lvlt = 25;

void setup() {
    gameover = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitx = rand() % (width - 2) + 1;
    fruity = rand() % (height - 2) + 1;
    score = 0;
    ntail = 0;
}

void draw() {
    system("cls");
    for (int i = 0; i < width; i++)
        cout << '#';
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1)
                cout << '#';
            if (i == y && j == x)
                cout << '0';
            else if (i == fruity && j == fruitx)
                cout << 'G';
            else {
                bool print = false;
                for (int k = 0; k < ntail; k++) {
                    if (tailx[k] == j && taily[k] == i) {
                        print = true;
                        cout << 'o';
                    }
                }
                if (!print) {
                    cout << ' ';
                }
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++)
        cout << '#';
    cout << endl;
    cout << "Score: " << score << endl;
}

void input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
        case 'A':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
        case 'D':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
        case 'W':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
        case 'S':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
        case 'X':
            gameover = true;
            game = false;
            break;
        }
    }
}

void logic() {
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < ntail; i++) {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    if (x >= width - 1) x = 0;
    else if (x < 0) x = width - 2;
    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;

    for (int i = 0; i < ntail; i++) {
        if (tailx[i] == x && taily[i] == y) {
            gameover = true;
            game = false;
        }
    }

    if (x == fruitx && y == fruity) {
        score += 10;
        fruitx = rand() % (width - 2) + 1;
        fruity = rand() % (height - 2) + 1;
        ntail++;
    }
}

int level;
void menu() {
    system("cls");
    gameover = false;
    cout << "Level(1 - 3): ";
    while (!(cin >> level) || level < 1 || level > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter 1, 2 or 3: ";
    }
    game = true;
}

int main() {
    srand(time(0));

    while (true) {
        if (game) {
            if (level == 1) lvlt = 25;
            else if (level == 2) lvlt = 10;
            else if (level == 3) lvlt = 1;

            setup();
            while (!gameover) {
                draw();
                input();
                logic();
                this_thread::sleep_for(chrono::milliseconds(lvlt));
            }
        }
        else {
            menu();
        }
    }
    return 0;
}