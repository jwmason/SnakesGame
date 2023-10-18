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
    // TODO: IMPLEMENT ME
    return 1;
}

unsigned Plane::cols() const
{
    // TODO: IMPLEMENT ME
    return 1;
}

unsigned Plane::snakeCount() const
{
    // TODO: IMPLEMENT ME
    return 0;
}

unsigned Plane::numberOfSnakesAt(unsigned r, unsigned c) const
{
    // TODO: IMPLEMENT ME
    return 0;
}

void Plane::moveSnakes()
{
    // TODO: IMPLEMENT ME
    // Move all snakes.  Mark the player as dead if necessary.
}

void Plane::pushAllSnakes(unsigned r, unsigned c, int dir)
{
    // TODO: IMPLEMENT ME
    // Pushes all snakes at [r,c] in the given direction
}

bool Plane::attemptMove(int dir, unsigned& r, unsigned& c)
{
    // TODO: IMPLEMENT ME
    // Return false without changing anything if moving one step from (r,c)
    // in the indicated direction would hit a run off the edge of the plane.
    // Otherwise, update r and c to the position resulting from the move and
    // return true.
    return true;
}


bool Plane::recommendMove(unsigned r, unsigned c, int& bestDir)
{
    // TODO: IMPLEMENT ME

    // Recommend a move for a player at (r,c):  A false return means the
    // recommendation is that the player should push and not move;
    // otherwise, this function sets bestDir to the recommended direction
    // to move and returns true.
    return false; 
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
    for (unsigned k = 0; k < Plane::MAX_SNAKES; k++)
    {
        const Snake * vp = m_snakes[k];
        if (vp && !vp->isDead()) {
          char& gridChar = displayGrid[vp->row()-1][vp->col()-1];
          switch (gridChar)
          {
            case '.':  gridChar = 'S'; break;
            case 'S':  gridChar = '2'; break;
            case '9':  break;
            default:   gridChar++; break;  // '2' through '8'
          }
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
