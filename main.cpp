#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

// Add a variable to track game state

bool gameRunning = true;
// Board layout
int const SIZE = 5;

int board[SIZE][SIZE] ={
   {1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1},
   {1, 1, 0, -1, -1},
   {-1, -1, -1, -1, -1},
   {-1, -1,- 1, -1, -1}};
   

////////
bool win = 0;
int opponent;

// movement
bool validMove;
int clicked_col;
int clicked_row;
bool beadselected;
int selected_row;
int selected_col;
// Cell size
const int cellsize = 100;
// column constant
int const column_cons = 5;

// Players
const int player1 = 1;
const int player2 = -1;
const int EMPTY = 0;
int playerturn = 1;

////////

void switch_turn()
{
    playerturn = -playerturn;
    cout << " it is turn of" << (playerturn == 1 ? player1 : player2);
}

//// winning condition calculate function;

int win_check()
{

    if (playerturn == 1)
    {
        opponent = 1;
    }
    else
    {
        opponent = -1;
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == opponent)

            {
                win = false;
                return win;
            }
        }
    }
    win = true;
    return win;
}
///// winner text display
// Function to display the winner
void display_winner(Text &text)
{
    if (playerturn == 1)
    {
        text.setString("Player 2 Wins!");
    }
    else if (playerturn == -1)
    {
        text.setString("Player 1 Wins!");
    }
    else
    {
        text.setString("It's a Draw!");
    }
}
////////switch turn display
void switch_turn(Text &text)
{
    if (playerturn == 1)
    {
        text.setString("player 1");
    }
    else
    {
        text.setString("player 2");
    }
}
// function for movement
void right_move(int board[][column_cons], int row, int col)
{
    if (board[row][col + 1] == EMPTY)
    {
        board[row][col + 1] = playerturn;
        board[row][col] = EMPTY;

        switch_turn();
    }
    else if ((board[row][col + 2] == EMPTY) && (board[row][col + 1] * -1 == (board[row][col])))
    {

        board[row][col + 2] = playerturn;
        board[row][col] = EMPTY;
        board[row][col + 1] = EMPTY;
        switch_turn();
    }
}
void left_move(int board[][column_cons], int row, int col)
{

    if (board[row][col - 1] == EMPTY)
    {
        board[row][col - 1] = board[row][col];
        board[row][col] = EMPTY;
        switch_turn();
    }
    else if ((board[row][col - 2] == EMPTY) && (board[row][col - 1] * -1 == (board[row][col])))
    {
        board[row][col - 2] = board[row][col];
        board[row][col] = EMPTY;
        board[row][col - 1] = EMPTY;
        switch_turn();
    }
}
void up_move(int board[][column_cons], int row, int col)
{
    if (board[row - 1][col] == EMPTY)
    {
        board[row][col] = EMPTY;
        board[row - 1][col] = playerturn;
        switch_turn();
    }
    else if ((board[row - 2][col] == EMPTY) && (board[row - 1][col] * -1 == (board[row][col])))
    {
        board[row - 2][col] = playerturn;
        board[row][col] = EMPTY;
        board[row - 1][col] = EMPTY;

        switch_turn();
    }
}
void down_move(int board[][column_cons], int row, int col)
{
    if (board[row + 1][col] == EMPTY)
    {
        board[row][col] = EMPTY;
        board[row + 1][col] = playerturn;
        switch_turn();
    }
    else if ((board[row + 2][col] == EMPTY) && ((board[row + 1][col] * -1 == (board[row][col]))))
    {
        board[row][col] = EMPTY;
        board[row + 2][col] = playerturn;
        board[row + 1][col] = EMPTY;
        switch_turn();
    }
}
void down_right_move(int board[][column_cons], int row, int col)
{
    if (board[row + 1][col + 1] == 0)
    {
        if ((col + row) % 2 == 0)
        {
            board[row + 1][col + 1] = board[row][col];
            board[row][col] = EMPTY;
            switch_turn();
        }
    }
    if ((board[row + 2][col + 2] == 0) && (board[row + 1][col + 1] * -1 == (board[row][col])))
    {
        if ((row + col) % 2 == 0)
        {
            board[row + 2][col + 2] = board[row][col];
            board[row][col] = EMPTY;
            board[row + 1][col + 1] = EMPTY;
            switch_turn();
        }
    }
}
void down_left_move(int board[][column_cons], int row, int col)
{
    if (board[row + 1][col - 1] == 0)
    {
        if ((col + row) % 2 == 0)
        {
            board[row][col] = EMPTY;
            board[row + 1][col - 1] = playerturn;
            switch_turn();
        }
    }
    if ((board[row + 2][col - 2] == 0) && (board[row + 1][col - 1] * -1 == (board[row][col])))
    {
        if ((col + row) % 2 == 0)

        {

            board[row + 2][col - 2] = board[row][col];
            board[row][col] = EMPTY;
            board[row + 1][col - 1] = EMPTY;

            switch_turn();
        }
    }
}

void up_left_move(int board[][column_cons], int row, int col)
{
    if (board[row - 1][col - 1] == 0)
    {
        if ((col + row) % 2 == 0)
        {
            cout << "im up left move" << endl;

            board[row - 1][col - 1] = playerturn;
            board[row][col] = EMPTY;
            switch_turn();
        }
    }
    if ((board[row - 2][col - 2] == 0) && (board[row - 1][col - 1] * -1 == (board[row][col])))
    {
        if ((col + row) % 2 == 0)

        {
            cout << "im up left move" << endl;
            board[row - 2][col - 2] = board[row][col];

            board[row][col] = 0;
            board[row - 1][col - 1] = 0;
            switch_turn();
        }
    }
}
void up_right_move(int board[][column_cons], int row, int col)
{
    if (board[row - 1][col + 1] == 0)
    {
        if ((col + row) % 2 == 0)
        {
            cout << "im up left move" << endl;

            board[row - 1][col + 1] = playerturn;
            board[row][col] = EMPTY;
            switch_turn();
        }
    }
    if ((board[row - 2][col + 2] == 0) && (board[row - 1][col + 1] * -1 == (board[row][col])))
    {
        if ((col + row) % 2 == 0)
        {
            cout << "im up left move" << endl;
            board[row - 2][col + 2] = board[row][col];
            board[row][col] = 0;
            board[row - 1][col + 1] = 0;
            switch_turn();
        }
    }
}

///////////////////////
////////////////////////
//////////////////////
int main()
{
    RenderWindow window(VideoMode(450, 600), "My SFML Window");

    // load font
    Font font;
    if (!font.loadFromFile("roboto-regular.ttf"))
    {
        cout << "error could not load font" << endl;
    }
    // text object
    Text text;
    text.setFont(font);

    text.setCharacterSize(50);
    text.setFillColor(Color::Green);
    text.setPosition(100, 450);

    // Load textures
    Texture textureboard;
    textureboard.loadFromFile("c:/Users/sbato/Downloads/board.png");

    Texture bead1texture;
    bead1texture.loadFromFile("c:/Users/sbato/Downloads/green.jpg");

    Texture bead2texture;
    bead2texture.loadFromFile("c:/Users/sbato/Downloads/red.jpg");

    // Initialize sprites
    Sprite spriteboard(textureboard);
    Sprite sprite1bead(bead1texture);
    Sprite sprite2beads(bead2texture);

    // Main loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        { // close event
            if (event.type == Event::Closed)
            {
                window.close();
            }
            ////////
            if (gameRunning)
            {
                // mouse event for function

                if (event.type == Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button ==  Mouse::Left)
                    {
                        // Get mouse position relative to the window
                        int mouse_x = Mouse::getPosition(window).x;
                        int mouse_y = Mouse::getPosition(window).y;

                        // Calculate clicked cell
                        clicked_col = mouse_x / cellsize;
                        clicked_row = mouse_y / cellsize;

                        if (clicked_col >= 0 && clicked_row < 5)
                        {

                            if ((!beadselected && board[clicked_row][clicked_col] != EMPTY) && (board[clicked_row][clicked_col] == playerturn))
                            {
                                beadselected = true;
                                selected_row = clicked_row;
                                selected_col = clicked_col;
                                cout << mouse_x << endl;
                                cout << mouse_y << endl;
                            }
                            // check where the bead wants to move
                            else if (beadselected)
                            {
                                if ((selected_col == clicked_col - 1 && selected_row == clicked_row) || (selected_col == clicked_col - 2 && selected_row == clicked_row))
                                {
                                    right_move(board, selected_row, selected_col);
                                    validMove = true;
                                }
                                else if ((selected_col == clicked_col + 1 && selected_row == clicked_row) || (selected_col == clicked_col + 2 && selected_row == clicked_row))
                                {
                                    left_move(board, selected_row, selected_col);
                                    validMove = true;
                                }
                                else if ((selected_col == clicked_col && selected_row == clicked_row - 1) || (selected_col == clicked_col && selected_row == clicked_row - 2))
                                {
                                    down_move(board, selected_row, selected_col);
                                    validMove = true;
                                }
                                else if ((selected_col == clicked_col && selected_row == clicked_row + 1) || (selected_col == clicked_col && selected_row == clicked_row + 2))

                                {
                                    up_move(board, selected_row, selected_col);
                                    validMove = true;
                                }
                                else if ((selected_col == clicked_col - 1 && selected_row == clicked_row - 1) || (selected_col == clicked_col - 2 && selected_row == clicked_row - 2))
                                {
                                    down_right_move(board, selected_row, selected_col);
                                    validMove = true;
                                }
                                else if ((selected_col == clicked_col + 1 && selected_row == clicked_row - 1) || (selected_col == clicked_col + 2 && selected_row == clicked_row - 2))
                                {
                                    down_left_move(board, selected_row, selected_col);
                                    validMove = true;
                                }
                                else if ((selected_col == clicked_col - 1 && selected_row == clicked_row + 1) || (selected_col == clicked_col - 2 && selected_row == clicked_row + 2))
                                {
                                    up_right_move(board, selected_row, selected_col);
                                    validMove = true;
                                }
                                else if ((selected_col == clicked_col + 1 && selected_row == clicked_row + 1) || (selected_col == clicked_col + 2 && selected_row == clicked_row + 2))
                                {
                                    up_left_move(board, selected_row, selected_col);
                                    validMove = true;
                                }

                                // deubgging made easier
                                cout << "Selected: (" << selected_row << ", " << selected_col << ")\n";
                                cout << "Clicked: (" << clicked_row << ", " << clicked_col << ")\n";
                                cout << "Valid move: " << (validMove ? "Yes" : "No") << "\n";
                                cout << "Updated board state:\n";
                                beadselected = false;
                                for (int i = 0; i < 5; ++i)
                                {
                                    for (int j = 0; j < 5; ++j)
                                    {
                                        std::cout << board[i][j] << " ";
                                    }
                                    std::cout << "\n";
                                }
                                ////////////////////////////
                                ////////////////////////////
                                // switch display text
                                switch_turn(text);

                                //////////////////////////////////////////////////
                            }
                        }
                    }
                }

                // Clear the window
                window.clear(Color::White);

                // Draw the board
                window.draw(spriteboard);
                // Draw the text
                window.draw(text);

                // Place and draw beads

                for (int i = 0; i < 5; ++i)
                {
                    for (int j = 0; j < 5; ++j)
                    {
                        if (board[i][j] == player1)
                        {
                            sprite1bead.setPosition(j * cellsize, i * cellsize);
                            window.draw(sprite1bead);
                        }
                        else if (board[i][j] == player2)
                        {
                            sprite2beads.setPosition(j * cellsize, i * cellsize);
                            window.draw(sprite2beads);
                        }
                    }
                }

                // Display everything on the window
                window.display();
                //////////////
                //////////////////
                /////////////////
                if (validMove)
                {
                    
                    if (win_check())
                    {
                        display_winner(text);
                        gameRunning = false; // Stop the game

                        cout << "\n Winner is Player " << -playerturn << endl;
                    }
                }
            }
            else
            {
                // Render the winner message
                window.clear(Color::White);
                window.draw(text);
                window.display();
            }
        }
    }

    return 0;
}
//////////////////////
