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
    if (m_dead)
    {
        return true;
    }
    return false;
}

void Snake::move()
{
    // Attempt a move in a random direction;  if it can't move, don't move.
    // Generate a random direction
    int direction = rand() % 4; // % 4 so it can be 0, 1, 2, or 3 (4 directions)

    // Check if snake is dead
    if (m_dead)
    {
        return;
    }
    // Depending on direction, move the Snake position. Check also if it can even move
    // 0 - up, 1 - right, 2 - down, 3 - left
    // Access the Plane row/col the Snake is on, and check that it can move
    onWhichPlane->attemptMove(direction, m_row, m_col);
}

void Snake::setDead()
{
    // set the Snake to be dead
    m_dead = true; 
}

void Snake::push(int dir)
{
    // Pushes this snake in this direction.
    // 0 - up, 1 - right, 2 - down, 3 - left

    // check if snake is dead
    if (m_dead)
    {
        return;
    }
    // Access the Plane row/col the Snake is on, and check that it can be pushed
    if (dir == 0)
    {
        m_row -= 1; // push up
    }
    else if (dir == 1)
    {
        m_col += 1; // push right
    }
    else if (dir == 2)
    {
        m_row += 1; // push down
    }
    else if (dir == 3)
    {
        m_col -= 1; // push left
    }
    // Check if Snake has been pushed off the Plane
    if (m_row > onWhichPlane->rows() || m_col > onWhichPlane->cols() || m_row < 1 || m_col < 1)
    {
        setDead();
    }
}