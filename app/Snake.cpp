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
    // return what column this snake is at.
    return m_col;
}

bool Snake::isDead() const
{
    // A snake is dead if this returns true, and false otherwise
    if (m_dead == true)
    {
        return true;
    }
    return false;
}

void Snake::move()
{
    // Attempt a move in a random direction;  if it can't move, don't move.
    int dir = rand() % 4; // gets a random direction from 0-3

    // north - 0, east - 1, south - 2, west - 3
    if (dir == 0 && m_row > 1)
    {
        m_row --; // move north
    }
    else if (dir == 1 && m_row < onWhichPlane->cols())
    {
        m_col ++; // move east
    }
    else if (dir == 2 && m_row < onWhichPlane->rows())
    {
        m_row ++; // move south
    }
    else if (dir == 3 && m_col > 1)
    {
        m_col --; // move west
    }
}

void Snake::setDead()
{
    // Makes the snake dead
    m_dead = true; 
}

void Snake::push(int dir)
{
    // Pushes this snake in this direction.
    // north - 0, east - 1, south - 2, west - 3
    if (dir == 0)
    {
        m_row --; // move north
    }
    else if (dir == 1)
    {
        m_col ++; // move east
    }
    else if (dir == 2)
    {
        m_row ++; // move south
    }
    else if (dir == 3)
    {
        m_col --; // move west
    }

    if (m_row >= onWhichPlane->rows() || m_col >= onWhichPlane->cols() || m_row <= 1 || m_col <= 1)
    {
        m_dead = true;
    }
}
