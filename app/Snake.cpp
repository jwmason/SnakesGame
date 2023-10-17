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
    // TODO: IMPLEMENT ME
    return false;
}

void Snake::move()
{
    // TODO: IMPLEMENT ME
    // Attempt a move in a random direction;  if it can't move, don't move.
}

void Snake::setDead()
{
    // TODO: IMPLEMENT ME   
}

void Snake::push(int dir)
{
    // TODO: IMPLEMENT ME
    // Pushes this snake in this direction.
}