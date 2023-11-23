#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// set the board size
#define BOARD_SIZE 4

// Dit defineert een stukje geheugen dat je kan gebruiken om een stukje van het bord te representeren
typedef struct {
    int value;
    int is_visible;
} Piece;


void initializeBoardCellsToNull(Piece *board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = NULL; // Initialize all cells to NULL
        }
    }
}
//Deze functie zorgt ervoor dat alle cellen van het bord geinitialiseerd worden naar NULL. Dit is nodig omdat je anders niet kan checken of een cel leeg is of niet.

Piece *create_piece(int value, int is_visible) {
    Piece *new_piece = (Piece *)malloc(sizeof(Piece)); //Je maakt een nieuw stukje geheugen aan dat groot genoeg is om een Piece te bevatten. Dit stukje geheugen wordt dan toegewezen aan de pointer new_piece.
    new_piece->value = value; //Je stelt de value van het stukje geheugen in op de waarde die je meegeeft aan de functie.
    new_piece->is_visible = is_visible; //Je stelt de is_visible van het stukje geheugen in op de waarde die je meegeeft aan de functie.
    return new_piece; //Je geeft de pointer terug zodat je het stukje geheugen kan gebruiken.
}

int random() {
    // Generate a random number between 1 and 10
    return rand() % 10 + 1;

}

void createBoard(Piece *board[BOARD_SIZE][BOARD_SIZE]) {
    initializeBoardCellsToNull(board);

    board[3][1] = create_piece(random(), 1); // je plaatst een pointer naar een stukje geheugen op het bord. Dit stukje geheugen bevat een Piece met een value en een is_visible. zo set je dus niet een heel opject op het bord maar alleen een pointer naar een stukje geheugen waar een Piece in zit. zo blijft je array 2d en kan je makkelijk door het bord heen loopen en gebruikt het minder geheugen.
    board[3][2] = create_piece(random(), 1);


    board[0][1] = create_piece(random(), 0);
    board[0][2] = create_piece(random(), 0);
}

void display_board(Piece *board[BOARD_SIZE][BOARD_SIZE]) {
    printf("Game Board:\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == NULL) {
                printf("0 ");
            } else if (board[i][j]->is_visible) { // board[i][j] is een pointer naar een stukje geheugen waar een Piece in zit. je kan met -> de daadwerkelijke value van het waar de pointer naar wijst ophalen.
                printf("%d ", board[i][j]->value);
            } else {
                printf("* ");
            }
        }
        printf("\n");
    }
}




int main() {
    srand(time(NULL));  // zorg dat random niet steedd dezelfde getallen genereert

    Piece *board[BOARD_SIZE][BOARD_SIZE];
    createBoard(board);
    display_board(board);


    return 0;
}
