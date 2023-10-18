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
    // TODO: IMPLEMENT ME 
    // return what column this  is at.
    // Delete the following line and replace it with the correct code.
    return 1;
}

unsigned Player::col() const
{
    // TODO: IMPLEMENT ME 
    // Delete the following line and replace it with the correct code.
    return 1;
}

std::string Player::push()
{
    // Go through every direction
    if (m_row > 1 && onWhichPlane->numberOfSnakesAt(m_row - 1, m_col) > 0)
    {
        onWhichPlane->pushAllSnakes(m_row - 1, m_col, 0); // Push snakes up
    }
    if (m_col < onWhichPlane->cols() && onWhichPlane->numberOfSnakesAt(m_row, m_col + 1) > 0)
    {
        onWhichPlane->pushAllSnakes(m_row, m_col + 1, 1); // Push snakes to the right
    }
    if (m_row < onWhichPlane->rows() && onWhichPlane->numberOfSnakesAt(m_row + 1, m_col) > 0)
    {
        onWhichPlane->pushAllSnakes(m_row + 1, m_col, 2); // Push snakes down
    }
    if (m_col > 1 && onWhichPlane->numberOfSnakesAt(m_row, m_col - 1) > 0)
    {
        onWhichPlane->pushAllSnakes(m_row, m_col - 1, 3); // Push snakes to the left
    }
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
    // TODO: IMPLEMENT ME 
    return false;
}

void Player::setDead()
{
    // TODO: IMPLEMENT ME 
}
