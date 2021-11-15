#include "Player.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
  m_shotTime = 0.0f;
  m_moveSpeed = 2;
  m_jumpSpeed = 2;
  m_jumpHeight = 0.0f;
  m_maxJumpHeight = 5;
  m_gravity = 9.8f;
}

void Player::draw()
{
  SDLGameObject::draw();
}

void Player::update()
{
  move();
  jump();
  shoot();

  m_currentFrame = (SDL_GetTicks() / 100) % 6;

  SDLGameObject::update();
}

void Player::move()
{
  // Horizontal Movement
  if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
  {
    if(m_position.getX() + m_width < TheGame::Instance()->getScreenWidth())
    {
      m_velocity.setX(m_moveSpeed);
      m_flipX = SDL_FLIP_NONE;
    }
    else
    {
      m_velocity.setX(0);
      //m_velocity.setX(-m_moveSpeed);
    }
  }
  else if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
  {
    if(m_position.getX() > 0)
    {
      m_velocity.setX(-m_moveSpeed);
      m_flipX = SDL_FLIP_HORIZONTAL;
    }
    else
    {
      m_velocity.setX(0);
      //m_velocity.setX(m_moveSpeed);
    }
  }
  else
  {
    m_velocity.setX(0);
  }
}

void Player::jump()
{
  static float currentVelocityY = 0;

  currentVelocityY += 0.02f * m_gravity;

  // Jump Input
  if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_SPACE) && !m_isJumping)
  {
    m_isJumping = true;
    m_velocity.setY(currentVelocityY);
    //m_velocity.setY(m_velocity.getY() + m_jumpSpeed);
  }

  // Jump Up
  if(m_jumpHeight <= m_maxJumpHeight && m_isJumping)
    m_jumpHeight += 0.02f;

  std::vector<GameObject*> gameObjs = TheGame::Instance()->getGameObjsVector();
  std::vector<GameObject*>::iterator it;

  it = find(gameObjs.begin(), gameObjs.end(), )
  if()
  if(SDLGameObject::checkCollision())
  {

  }
}

void Player::shoot()
{
  if(m_shotTime >= 2.0f)
  {
    if(TheInputHandler::Instance()->GetMouseBtnState(TheInputHandler::LEFT))
    {
      std::cout << "shoot" << std::endl;
      m_shotTime = 0.0f;
    }
  }
  else
  {
    m_shotTime += 0.02f;
  }
  
  //Vector2D* vec = TheInputHandler::Instance()->GetMousePos();
  //m_velocity = (*vec - m_position) / 100;
}

void Player::checkCollision()
{
  if(m_position.getX() + m_height)
  {
    
  }
}

void Player::clean()
{
  
}