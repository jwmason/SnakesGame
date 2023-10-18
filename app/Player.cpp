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
    // Cause the player to push, as per the spec.
     // Check if there are snakes in each of the four adjacent cells
    if (onWhichPlane->numberOfSnakesAt(m_row - 1, m_col) > 0) // North
    {
        onWhichPlane->pushAllSnakes(m_row - 1, m_col, 0); // Push snakes up
    }
    if (onWhichPlane->numberOfSnakesAt(m_row, m_col + 1) > 0) // East
    {
        onWhichPlane->pushAllSnakes(m_row, m_col + 1, 1); // Push snakes to the right
    }
    if (onWhichPlane->numberOfSnakesAt(m_row + 1, m_col) > 0) // South
    {
        onWhichPlane->pushAllSnakes(m_row + 1, m_col, 2); // Push snakes down
    }
    if (onWhichPlane->numberOfSnakesAt(m_row, m_col - 1) > 0) // West
    {
        onWhichPlane->pushAllSnakes(m_row, m_col - 1, 3); // Push snakes to the left
    }
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

    // Initialize string
    std::string msg = "Player couldn't move; player stands.";

    // Update the player's position and msg based on the direction.
    if (dir == 0 && m_row > 1)
    {
        m_row -= 1; // move up
        msg = "Player moved north.";
    }
    else if (dir == 1 && m_col < onWhichPlane->cols())
    {
        m_col += 1; // move right
        msg = "Player moved east.";
    }
    else if (dir == 2 && m_row < onWhichPlane->rows())
    {
        m_row += 1; // move down
        msg = "Player moved south.";
    }
    else if (dir == 3 && m_col > 1)
    {
        m_col -= 1; // move left
        msg = "Player moved west.";
    }

    // Check if the player has walked into a snake and died.
    if (onWhichPlane->numberOfSnakesAt(m_row, m_col) != 0)
    {
        return "Player walked into a snake and died.";
    }

    // Return the message
    return msg;
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