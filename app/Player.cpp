#include "Player.hpp"
#include <iostream>
#include <sstream>

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
    // return what row this is at.
    return m_row;
}

unsigned Player::col() const
{
    // Return what col the player is at
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
    // TODO: IMPLEMENT ME 
    // Attempt to have the player move.
    // If it fails, return "Player couldn't move;  player stands."
    
    // A player who walks onto a snake dies, and this returns
    // "Player walked into a snake and died."
    
    // Otherwise, return one of "Player moved north.", "Player moved east.", 
    // "Player moved south.", or "Player moved west."

    // Initialize message
    std::string msg = "Player couldn't move; player stands.";

    // north - 0, east - 1, south - 2, west - 3
    
    if (dir == 0 && m_row > 1)
    {
        m_row --; // move north
        msg = "Player moved north.";
    }
    else if (dir == 1 && m_col < onWhichPlane->cols())
    {
        m_col ++; // move east
        msg = "Player moved east.";
    }
    else if (dir == 2 && m_row < onWhichPlane->rows())
    {
        m_row ++; // move south
        msg = "Player moved south.";
    }
    else if (dir == 3 && m_col > 1)
    {
        m_col --; // move west
        msg = "Player moved west.";
    }

    if (onWhichPlane->numberOfSnakesAt(m_row, m_col) > 0)
    {
        msg = "Player walked into a snake and died.";
    }

    return msg;
}

bool Player::isDead() const
{
    // Check if Player is Dead or Not and return T/F
    if (m_dead == true)
    {
        return true;
    }
    return false;
}

void Player::setDead()
{
    // Set Player dead
    m_dead = true;
}
