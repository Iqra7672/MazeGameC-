#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h> // For _getch()
#include <cctype> // For toupper()

using namespace std;

const int MAZE_SIZE = 10;
const char MAZES[8][MAZE_SIZE][MAZE_SIZE + 1] = {
    {
        "S#########",
        ".........#",
        "#.######.#",
        "#.#....#.#",
        "#.#.##.#.#",
        "#.#.##.#.#",
        "#.#....#.#",
        "#.######.#",
        "#........#",
        "########E#"
    },
    {
        "#S########",
        "#.........",
        "#.#####.##",
        "#.#...#..#",
        "#.#.#.####",
        "#...#....#",
        "#.#.####.#",
        "#.#......#",
        "#.######.#",
        "#.#.....E#"
    },
    {
        "S.########",
        "#..#......",
        "#.#####.##",
        "#.....#..#",
        "#.#.#.####",
        "#.#.#....#",
        "#.#.#.####",
        "#.#......#",
        "#..#####.#",
        "#.#.....E#"
    },
    {
        "###S######",
        "#.#.......",
        "#.#.#.#.##",
        "#.#.#.#..#",
        "#.#.#.#.##",
        "#.#.#.#.##",
        "#.#.#.#.##",
        "#.#...#.##",
        "#.##..#.##",
        "#...#.E.##"
    },
    {
        "S..#######",
        "#.#####...",
        "#.#####.#.",
        "#.#.....#.",
        "#.#####.#.",
        "#.......#.",
        "#.###.###.",
        "#.........",
        "#########.",
        "E........."
    },
    {
        "S#########",
        "....#....#",
        "#.###.##.#",
        "#.#.#....#",
        "#.#.######",
        "#.#......#",
        "#.#.####.#",
        "#........#",
        "#.#######.",
        "#.......E#"
    },
    {
        "S#########",
        "....#....#",
        "#.###.##.#",
        "#.#......#",
        "#.#.#.####",
        "#.#.......",
        "#.#.####.#",
        "#...#....E",
        "#.#######.",
        "#.......##"
    },
    {
        "S#########",
        "..#.....##",
        "#.#.#.#.##",
        "#.#.#.#..#",
        "#.#.#.#.##",
        "#.#.#.#.##",
        "#.#.#.#.##",
        "#.#...#.##",
        "#.###.#.##",
        "#.....#E##"
    }
};

void displayMaze(const char maze[MAZE_SIZE][MAZE_SIZE + 1], int playerX, int playerY) {
    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            if (i == playerY && j == playerX) {
                cout << 'P';
            }
            else {
                cout << maze[i][j];
            }
        }
        cout << endl;
    }
}

void displayRules() {
    cout << "Welcome to the Maze Game!" << endl;
    cout << "Use W to move up, A to move left, S to move down, D to move right." << endl;
    cout << "Your goal is to navigate from the Start (S) to the End (E)." << endl;
    cout << "Press any key to start the game..." << endl;
    _getch();
}

void saveScore(const string& username, int score) {
    ofstream scoreFile("scoreboard.txt", ios::app);
    if (scoreFile.is_open()) {
        scoreFile << username << " : " << score << "!" << endl;
        scoreFile.close();
    }
    else {
        cout << "Unable to open scoreboard file!" << endl;
    }
}

void displayScores() {
    ifstream scoreFile("scoreboard.txt");
    string line;
    if (scoreFile.is_open()) {
        cout << "Scoreboard:" << endl;
        while (getline(scoreFile, line)) {
            cout << line << endl;
        }
        scoreFile.close();
    }
    else {
        cout << "Unable to open scoreboard file!" << endl;
    }
}

int main() {
    srand(time(0));

    string username;
    cout << "Enter your username: ";
    cin >> username;

    char play;
    cout << "Do you want to play the maze game? (Y/N): ";
    cin >> play;

    if (toupper(play) != 'Y') {
        cout << "Maybe next time. Goodbye!" << endl;
        return 0;
    }

    displayRules();

    // Randomly select a maze
    int mazeIndex = rand() % 8;
    const char(*selectedMaze)[MAZE_SIZE + 1] = MAZES[mazeIndex];

    // Find the start position
    int playerX = 0, playerY = 0;
    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            if (selectedMaze[i][j] == 'S') {
                playerX = j;
                playerY = i;
                break;
            }
        }
    }

    char move;
    bool gameRunning = true;

    while (gameRunning) {
        system("cls"); // Clear the console
        displayMaze(selectedMaze, playerX, playerY);

        move = _getch(); // Get user input
        int newX = playerX, newY = playerY;

        switch (toupper(move)) {
        case 'W': newY--; break;
        case 'A': newX--; break;
        case 'S': newY++; break;
        case 'D': newX++; break;
        default: break;
        }

        if (newX >= 0 && newX < MAZE_SIZE && newY >= 0 && newY < MAZE_SIZE &&
            selectedMaze[newY][newX] != '#') {
            playerX = newX;
            playerY = newY;
        }

        if (selectedMaze[playerY][playerX] == 'E') {
            system("cls");
            displayMaze(selectedMaze, playerX, playerY);
            cout << "Congratulations, " << username << "! You have reached the end of the maze!" << endl;
            saveScore(username, 10); // Pass the score of 10
            gameRunning = false;
        }
    }

    cout << "Do you want to view the scoreboard? (Y/N): ";
    cin >> play;

    if (toupper(play) == 'Y') {
        displayScores();
    }

    return 0;
}