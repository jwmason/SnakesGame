#include "Snake.hpp"
#include <iostream>

Snake::Snake(Plane* plane, unsigned r, unsigned c)
: onWhichPlane{plane}, m_row{r}, m_col{c}, m_dead{false}
{
    if (plane == nullptr)
    {
        std::cerr << "***** A snake must be created in some plane!" << std::endl;
        exit(1);
    }
    if (r < 1  ||  r > plane->rows()  ||  c < 1  ||  c > plane->cols())
    {
        std::cerr << "***** Snake created with invalid coordinates (" << r << ","
             << c << ")!" << std::endl;
        exit(1);
    }
}

unsigned Snake::row() const
{
    // Return what row this snake is at
    return m_row;
}

unsigned Snake::col() const
{
    // Return what column this snake is at
    return m_col;
}

bool Snake::isDead() const
{
    // Check if Snake is dead, return true if dead and false if not
    // Use given boolean that is in each Snake object
    return m_dead;
}

void Snake::move()
{
    // Attempt a move in a random direction;  if it can't move, don't move.
    // Generate a random direction
    int direction = rand() % 4; // % 4 so it can be 0, 1, 2, or 3 (4 directions)

    // Depending on direction, move the Snake position. Check also if it can even move
    // 0 - up, 1 - left, 2 - down, 3 - right
    // Access the Plane row/col the Snake is on, and check that it can move
    if (direction == 0 && m_col < onWhichPlane->cols())
    {
        m_col += 1; // move up
    }
    else if (direction == 1 && m_row > 1)
    {
        m_row -= 1; // move left
    }
    else if (direction == 2 && m_col > 1)
    {
        m_col -= 1; // move down
    }
    else if (direction == 3 && m_row < onWhichPlane->rows())
    {
        m_row += 1; // move right
    }
}

void Snake::setDead()
{
    // set the Snake to be dead
    m_dead = true; 
}

void Snake::push(int dir)
{
    // TODO: IMPLEMENT ME
    // Pushes this snake in this direction.
}