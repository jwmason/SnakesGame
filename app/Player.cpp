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
    return "Player couldn't move; player stands.";
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
