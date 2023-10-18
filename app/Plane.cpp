#include "Plane.hpp"
#include "display.hpp"
#include "rand.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

Plane::Plane(unsigned nRows, unsigned nCols)
: m_rows{nRows}, m_cols{nCols}, m_player{nullptr}, m_nSnakes{0}, m_turns{0}
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        std::cerr << "***** Plane created with invalid size " << nRows << " by "
             << nCols << "!" << std::endl;
        exit(1);
    }
    for (unsigned r = 1; r <= m_rows; r++)
        for (unsigned c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Plane::~Plane()
{
    // TODO: IMPLEMENT ME
}

unsigned Plane::rows() const
{
    // Returns the Plane Rows
    return m_rows;
}

unsigned Plane::cols() const
{
    // Returns the Plane Columns
    return m_cols;
}

unsigned Plane::snakeCount() const
{
    // Returns the total amount of Snakes on the Plane
    return m_nSnakes;
}

unsigned Plane::numberOfSnakesAt(unsigned r, unsigned c) const
{
    // Returns the number of Snakes at specificed row and col
    // Intialize the number of snakes
    int snakes = 0;
    // Loop through each snake in m_snakes to see if they are in specified row and col
    for (unsigned i{0}; i < m_nSnakes; ++i)
    {
        // Get the row and col that each Snake is and compare to given ones
        if (m_snakes[i]->row() == r && m_snakes[i]->col() == c)
        {
            // The snake is at the row and col
            snakes += 1;
        }
    }
    // Return the amount of snakes at the row and col
    return snakes;
}

void Plane::moveSnakes()
{
    // Move all snakes.  Mark the player as dead if necessary.
    // Loop through all snakes and move them. Check if same row and col as Player
    for (unsigned i{0}; i < m_nSnakes; ++i)
    {
        // move each Snake
        m_snakes[i]->move();
        // If snake is moved to Player position, kill Player
        if (m_player != nullptr && m_snakes[i]->row() == m_player->row() && m_snakes[i]->col() == m_player->col())
        {
            m_player->setDead();
        }
    }
}

void Plane::pushAllSnakes(unsigned r, unsigned c, int dir)
{
    // Pushes all snakes at [r,c] in the given direction
    // Loop through for every snake
    for (unsigned i{0}; i < m_nSnakes; ++i)
    {
        // Call on snake push function
        m_snakes[i]->push(dir);
    }
}

bool Plane::attemptMove(int dir, unsigned& r, unsigned& c)
{
    // Return false without changing anything if moving one step from (r,c)
    // in the indicated direction would hit a run off the edge of the plane.
    // Otherwise, update r and c to the position resulting from the move and
    // return true.

    // Initialize variables
    int test_r = 0;
    int test_c = 0;

    // Change accordingly
    if (dir == 0)
    {
        test_r -= 1; // move north
    }
    else if (dir == 1)
    {
        test_c += 1; // move east
    }
    else if (dir == 2)
    {
        test_r += 1; // move south
    }
    else if (dir == 3)
    {
        test_c -= 1; // move west
    }
    // Add back to original row and col
    int test_rows = r + test_r;
    int test_cols = c + test_c;
    // Check if the new position is within the Plane's bounds
    if (isPosInBounds(test_rows, test_cols))
    {
        r = test_rows; // Update r
        c = test_rows; // Update c
        return true;
    }
    return false;
}


bool Plane::recommendMove(unsigned r, unsigned c, int& bestDir)
{
    // Recommend a move for a player at (r,c):  A false return means the
    // recommendation is that the player should push and not move;
    // otherwise, this function sets bestDir to the recommended direction
    // to move and returns true.

    // Intialize variables
    unsigned danger_lv = MAX_SNAKES; // the worse case scernario in a position
    int bestDirection = -1;

    // Loop through every direction and find best direction
    for (unsigned dir{0}; dir < NUMDIRS; ++dir)
    {
        // Intialize variables to be replaced for attemptMove()
        unsigned test_r = 0;
        unsigned test_c = 0;
        // Use attemptMove to make sure new position is in bounds, and if so replace r and c
        if (attemptMove(dir, test_r, test_c))
        {
            // Compute danger level with test position
            unsigned new_danger = computeDanger(test_r, test_c);
            // Check if position is better than pushing
            if (new_danger < danger_lv)
            {
                // Set the lower danger level and given direction
                danger_lv = new_danger;
                bestDirection = dir;
            }
        }
    }
    // If no direction was better than pushing, return false
    if (bestDirection == -1)
    {
        return false;
    }
    // If not, give best direction and return true
    bestDir = bestDirection;
    return true;
}

Player* Plane::player() const
{
    return m_player;
}

int Plane::getCellStatus(unsigned r, unsigned c) const
{
    checkPos(r, c);
    return m_grid[r-1][c-1];
}

void Plane::display(std::string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    unsigned r, c;
    
      // Fill displayGrid with dots (empty)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

        // Indicate each snake's position
    for (unsigned k = 0; k < m_nSnakes; k++)
    {
        const Snake * vp = m_snakes[k];
        char& gridChar = displayGrid[vp->row()-1][vp->col()-1];
        switch (gridChar)
        {
          case '.':  gridChar = 'S'; break;
          case 'S':  gridChar = '2'; break;
          case '9':  break;
          default:   gridChar++; break;  // '2' through '8'
        }
    }

      // Indicate player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            std::cout << displayGrid[r-1][c-1];
        std::cout << std::endl;
    }
    std::cout << std::endl;

      // Write message, snake, and player info
    if (msg != "")
        std::cout << msg << std::endl;
    std::cout << "There are " << snakeCount() << " snakes remaining." << std::endl;
    if (m_player == nullptr)
        std::cout << "There is no player!" << std::endl;
    else if (m_player->isDead())
        std::cout << "The player is dead." << std::endl;
    std::cout << m_turns << " turns have been taken." << std::endl;
}

void Plane::setCellStatus(unsigned r, unsigned c, int status)
{
    checkPos(r, c);
    m_grid[r-1][c-1] = status;
}

bool Plane::addSnake(unsigned r, unsigned c)
{
    if (! isPosInBounds(r, c))
        return false;
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    if (m_nSnakes == MAX_SNAKES)
        return false;
    m_snakes[m_nSnakes] = new Snake(this, r, c);
    m_nSnakes++;
    return true;
}

bool Plane::addPlayer(unsigned r, unsigned c)
{
    if (m_player != nullptr  or  ! isPosInBounds(r, c))
        return false;
    if (numberOfSnakesAt(r, c) > 0)
        return false;
    m_player = new Player(this, r, c);
    return true;
}

bool Plane::isPosInBounds(unsigned r, unsigned c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Plane::checkPos(unsigned r, unsigned c) const
{
    if (!isPosInBounds(r, c))
    {
        std::cerr << "***** " << "Invalid plane position (" << r << ","
             << c << ")" << std::endl;
        exit(1);
    }
}

void Plane::turnTaken() { m_turns++; }

unsigned Plane::computeDanger(unsigned r, unsigned c)
{
      // Our measure of danger will be the number of snakes that might move
      // to position r,c.  If a snake is at that position, it is fatal,
      // so a large value is returned.

    if (numberOfSnakesAt(r,c) > 0)
        return MAX_SNAKES+1;

    unsigned danger = 0;
    if (r > 1)
        danger += numberOfSnakesAt(r-1,c);
    if (r < rows())
        danger += numberOfSnakesAt(r+1,c);
    if (c > 1)
        danger += numberOfSnakesAt(r,c-1);
    if (c < cols())
        danger += numberOfSnakesAt(r,c+1);

    return danger;
}
