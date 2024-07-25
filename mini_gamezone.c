#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int revealed;
    int mine;
    int value;
} Cell;

void initialize_board(Cell **board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j].revealed = 0;
            board[i][j].mine = 0;
            board[i][j].value = rand() % 10;  // Random value between 0 and 9
        }
    }
}

void place_mines(Cell **board, int size, int mines) {
    srand(time(0));
    for (int i = 0; i < mines; i++) {
        int x = rand() % size;
        int y = rand() % size;
        if (board[x][y].mine == 0) {
            board[x][y].mine = 1;
            board[x][y].value = 0;  // Ensure mines have a value of 0
        } else {
            i--;  // Retry if a mine is already placed here
        }
    }
}

void print_board(Cell **board, int size, int reveal) {
    printf("   ");
    for (int i = 0; i < size; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%d: ", i);
        for (int j = 0; j < size; j++) {
            if (reveal || board[i][j].revealed) {
                if (board[i][j].mine) {
                    printf("* ");
                } else {
                    printf("%d ", board[i][j].value);
                }
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int reveal_cell(Cell **board, int size, int x, int y, int *score) {
    if (x < 0 || x >= size || y < 0 || y >= size || board[x][y].revealed) {
        return 0;
    }

    board[x][y].revealed = 1;

    if (board[x][y].mine) {
        return -1;  // Hit a mine
    }

    *score += board[x][y].value;

    return 1;
}

void play_skipmine() {
    int size, mines;
    printf("Enter the size of the board: ");
    scanf("%d", &size);
    printf("Enter the number of mines: ");
    scanf("%d", &mines);

    Cell **board = malloc(size * sizeof(Cell *));
    for (int i = 0; i < size; i++) {
        board[i] = malloc(size * sizeof(Cell));
    }

    srand(time(0));  // Seed the random number generator
    initialize_board(board, size);
    place_mines(board, size, mines);

    int game_over = 0;
    int cells_to_reveal = size * size - mines;
    int revealed_cells = 0;
    int score = 0;

    while (!game_over && revealed_cells < cells_to_reveal) {
        print_board(board, size, 0);
        printf("Enter the coordinates to reveal (row col): ");
        int x, y;
        scanf("%d %d", &x, &y);
        
        int result = reveal_cell(board, size, x, y, &score);
        if (result == -1) {
            game_over = 1;
            printf("You hit a mine! Game over.\n");
        } else {
            revealed_cells++;
            if (revealed_cells == cells_to_reveal) {
                printf("Congratulations! You revealed all safe cells.\n");
            }
        }
    }

    print_board(board, size, 1);  // Reveal the entire board at the end
    printf("Your final score is: %d\n", score);

    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
}

void play_guess_number_game(int num_players) {
    int number, guess, attempts[num_players];
    int player, min_attempts = 1000, winner;
    int winner_count = 0; // Track number of players with minimum attempts

    printf("Welcome to the Number Guessing Game!\n");

    for (player = 0; player < num_players; player++) {
        attempts[player] = 0;
        srand(time(0) + player); // Seed the random number generator uniquely for each player
        number = rand() % 100 + 1;
        printf("Player %d's turn:\n", player + 1);
        do {
            printf("Enter your guess: ");
            scanf("%d", &guess);
            attempts[player]++;

            if (guess > number) {
                printf("Too high! Try again.\n");
            } else if (guess < number) {
                printf("Too low! Try again.\n");
            } else {
                printf("Congratulations Player %d! You guessed the number in %d attempts.\n", player + 1, attempts[player]);
                if (attempts[player] < min_attempts) {
                    min_attempts = attempts[player];
                    winner = player + 1;
                    winner_count = 1;
                } else if (attempts[player] == min_attempts) {
                    winner_count++;
                }
            }
        } while (guess != number);
    }

    if (winner_count > 1) {
        printf("\nIt's a draw! Multiple players guessed the number in %d attempts.\n", min_attempts);
    } else {
        printf("\nPlayer %d is the winner with %d attempts!\n", winner, min_attempts);
    }
}

int main() {
    int choice;

    printf("List Of Games\n");
    printf("1. Skipmine\n");
    printf("2. Guess it\n");
    printf("Enter the game number you want to play: ");
    scanf("%d", &choice);

    if (choice == 1) {
        play_skipmine();
    } else if (choice == 2) {
        int num_players;
        printf("Enter the number of players: ");
        scanf("%d", &num_players);
        play_guess_number_game(num_players);
    } else {
        printf("Invalid choice. Please restart the program and select a valid option.\n");
    }

    return 0;
}
