#include "Player.hpp"
#include <iostream>

Player::Player(Plane* plane, unsigned r, unsigned c)
:  onWhichPlane{plane}, m_row{r}, m_col{c}, m_dead{false}
{
    if (plane == nullptr)
    {
        std::cerr << "***** The player must be created in some Plane!" << std::endl;
        exit(1);
    }
    if (r < 1  ||  r > plane->rows()  ||  c < 1  ||  c > plane->cols())
    {
        std::cerr << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << std::endl;
        exit(1);
    }
}

unsigned Player::row() const
{
    // Return what row this is at.
    return m_row;
}

unsigned Player::col() const
{
    // Return Player column
    return m_col;
}

std::string Player::push()
{   
    // TODO: IMPLEMENT ME
    // Cause the player to push, as per the spec.
    return "Player pushed.";
}

std::string Player::move(int dir)
{
    // Attempt to have the player move.
    // If it fails, return "Player couldn't move;  player stands."
    
    // A player who walks onto a snake dies, and this returns
    // "Player walked into a snake and died."
    
    // Otherwise, return one of "Player moved north.", "Player moved east.", 
    // "Player moved south.", or "Player moved west."

    if (dir == 0 && m_col < onWhichPlane->cols())
    {
        m_col += 1; // move up
    }
    else if (dir == 1 && m_row < onWhichPlane->rows())
    {
        m_row += 1; // move right
    }
    else if (dir == 2 && m_col > 1)
    {
        m_col -= 1; // move down
    }
    else if (dir == 3 && m_row > 1)
    {
        m_row -= 1; // move left
    }
    // Check if the new position is same as a snake
    return "Player couldn't move; player stands.";
}

bool Player::isDead() const
{
    // Check if already dead
    if (m_dead)
    {
        return true;
    }
    return false;
}

void Player::setDead()
{
    // Set player to be dead
    m_dead = true;
}