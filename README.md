# Mini Game Zone: Skipmine and Guess it

This project contains two fun console games: Skipmine and Guess it. The program will prompt you to choose which game you want to play and then guide you through playing that game.

## Games

### Skipmine

Skipmine is a simple minesweeper-like game. The player must reveal cells on the board without hitting any mines. Each cell has a random value between 0 and 9, which contributes to the player's score. The game ends when all safe cells are revealed or the player hits a mine.

### Guess it

Guess it is a number guessing game. Each player takes turns guessing a randomly generated number between 1 and 100. The player who guesses the number in the fewest attempts wins. If multiple players guess the number in the same number of attempts, the game is a draw.

## How to Play

1. Clone this repository to your local machine.
    ```sh
    git clone https://github.com/jigarpatell/mini_gamezone.git
    ```

2. Navigate to the project directory.
    ```sh
    cd mini_gamezone
    ```

3. Compile the program using a C compiler, for example, `gcc`.
    ```sh
    gcc -o game mini_gamezone.c
    ```

4. Run the compiled program.
    ```sh
    ./game
    ```

5. Follow the on-screen instructions to choose and play a game.

## Code Structure

- `mini_gamezone.c`: Contains the code for both Skipmine and Guess it games, as well as the main menu to select which game to play.

## Contributing

If you would like to add more games to this project, please fork the repository and submit a pull request. You can also report issues or request features by opening an issue.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.
