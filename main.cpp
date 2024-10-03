#include <iostream>
#include <ctime>
#include <conio.h>
#include <vector>
#include <windows.h>

bool game_over;
const int width = 20;
const int height = 20;
int head_x, head_y, fruit_x, fruit_y, score;
int max_size = 100;
std::vector<int> tail_x(max_size), tail_y(max_size);
int length_tail;
bool print;
bool fruit_not_in_tail;
enum eDirection { 
    STOP = 0, 
    UP = 1, 
    LEFT = 2, 
    DOWN = 3,
    RIGHT = 4, 
};
eDirection dir;

void Setup();
void Draw();
void Input();
void Logic();

int main() {
    srand(time(NULL));
    Setup();
    while(!game_over)
    {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}

void Setup() {
    game_over = false;
    dir = STOP;
    head_x = width / 2;
    head_y = height / 2;
    fruit_x = rand() % (width-2) + 1;
    fruit_y = rand() % (height-2) + 1;
    score = 0;
}

void Draw() {
    system("cls");
    std::cout << '\n';
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (i==0 || i == width - 1 || j==0 || j == height -1) {
                std::cout << "#";
            }
            else if (i==head_x && j==head_y) {
                std::cout << "O";
            }
            else if (i==fruit_x && j==fruit_y) {
                std::cout << "F";
            }
            else {
                print = false;
                for (int k = 0; k < length_tail; k++) {
                    if (i == tail_x[k] && j == tail_y[k]) {
                        std::cout << "o";
                        print = true;
                    }
                }
                if (!print) {
                    std::cout << " ";
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << '\n';
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'z':
                if (dir != DOWN) {
                    dir = UP;
                }
                break;
            case 'q':
                if (dir != RIGHT) {
                    dir = LEFT;
                }
                break;
            case 's':
                if (dir != UP) {
                    dir = DOWN;
                }
                break;
            case 'd':
                if (dir != LEFT) {
                    dir = RIGHT;
                }
                break;
            case 'x':
                game_over = true;
                break;
            default:
                break;
        }
    }
}

void Logic() {

    int prev_x = head_x;
    int prev_y = head_y;
    int prev2_x, prev2_y;
    
    for (int i = 0; i < length_tail; i++) {
        prev2_x = tail_x[i];
        prev2_y = tail_y[i];
        tail_x[i] = prev_x;
        tail_y[i] = prev_y;
        prev_x = prev2_x;
        prev_y = prev2_y;
    }

    switch (dir) {
        case 1:
            head_y--;
            break;
        case 2:
            head_x--;
            break;
        case 3:
            head_y++;
            break;
        case 4:
            head_x++;
            break;
        default:
            break;
    }
    for (int k = 0; k < length_tail; k++) {
        if (tail_x[k] == head_x && tail_y[k] == head_y) {
            std::cout << "You've lost ! \n";
            std::cout << "Your score : " << score << '\n';
            game_over = true;
        }
    }
    if (head_x == 0 || head_x == width - 1|| head_y == 0 || head_y == height - 1) {
        std::cout << "You've lost ! \n";
        std::cout << "Your score : " << score << '\n';
        game_over = true;
    }
    else if (head_x == fruit_x && head_y == fruit_y) {
        score++;
        fruit_not_in_tail = true;
        do {
        fruit_x = rand() % (width-2) + 1;
        fruit_y = rand() % (height-2) + 1;
        for (int k = 0; k < length_tail; k++) {
            if ((tail_x[k] == fruit_x && tail_y[k] == fruit_y)) {
                fruit_not_in_tail = false;
            }
        }
        if (head_x == fruit_x && head_y == fruit_y) {
            fruit_not_in_tail = false;
        }
        } while(!fruit_not_in_tail);
        length_tail++;
        
        if (length_tail == max_size) {
            std::cout << "You've won ! \n";
            std::cout << "You've reached a score of " << max_size << " !";
            game_over = true;
        }
    }
}