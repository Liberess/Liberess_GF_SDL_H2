#include "Player.h"
#include "Game.h"
#include "GameObject.h"
#include "TextureManager.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
  m_shotTime = 0.0f;
  m_moveSpeed = 3;
  m_jumpSpeed = 5;
  m_jumpHeight = 0.0f;
  m_maxJumpHeight = 50.0f;
  m_gravity = 9.8f;

  m_isJumping = false;

  m_flipX = SDL_FLIP_NONE;

  m_leftObstacle = false;
  m_rightObstacle = false;
  m_upObstacle = false;
  m_downObstacle = false;
}

void Player::draw()
{
  //TheTextureManager::Instance()->drawFrame(m_textureID, m_position.getX() - TheGame::Instance()->getCameraRect().x, m_position.getY() - TheGame::Instance()->getCameraRect().y, m_width, m_height, m_currentRow, m_currentFrame, m_destRect, TheGame::Instance()->getRenderer(), m_flipX);
  SDLGameObject::draw();
}

void Player::update()
{
  checkCollision();
  move();
  jump();
  shoot();

  if(m_velocity.getX() != 0 || m_velocity.getY() != 0)
    m_currentFrame = (SDL_GetTicks() / 100) % 6;
  else
    m_currentFrame = 0;

  SDLGameObject::update();
}

void Player::move()
{
  if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
  {
    if(m_position.getX() + m_width < TheGame::Instance()->getScreenWidth() && !m_rightObstacle)
    {
      m_velocity.setX(m_moveSpeed);
      m_flipX = SDL_FLIP_NONE;
    }
    else
    {
      m_velocity.setX(0);
    }
  }
  else if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
  {
    if(m_position.getX() > 0 && m_leftObstacle)
    {
      m_velocity.setX(m_moveSpeed * -1);
      m_flipX = SDL_FLIP_HORIZONTAL;
    }
    else
    {
      m_velocity.setX(0);
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
  static int prePosY = 0;

  currentVelocityY += 0.02f * m_gravity;

  // Jump Input
  if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP) && !m_isJumping && m_isGround)
  {
    m_isJumping = true;
    m_isGround = false;

    prePosY = m_position.getY();
    m_acceleration.setY(m_jumpSpeed * -1);
  }

  // If Grounded
  if(m_isGround)
  {
    m_isJumping = false;

    m_jumpHeight = 0.0f;
    m_velocity.setY(0);
    m_acceleration.setY(0);
    currentVelocityY = 0.0f;
    return;
  }

  // 만약 최대 점프 높이에 도달했으면 아래로 가속도
  if(abs(m_position.getY() - prePosY) >= m_maxJumpHeight && m_isJumping)
    m_acceleration.setY(m_jumpSpeed * 0.5f);

  if(m_isJumping && !m_upObstacle)
    m_acceleration.setY(m_jumpSpeed * 0.5f);

  m_velocity.setY(currentVelocityY);
}

void Player::shoot()
{
  if(m_shotTime >= 2.0f)
  {
    if(TheInputHandler::Instance()->GetMouseBtnState(TheInputHandler::LEFT))
    {
      std::cout << "총알 발사" << std::endl;
      TheGame::Instance()->instantiateBullet(m_position);
      m_shotTime = 0.0f;
    }
  }
  else
  {
    m_shotTime += 0.02f;
  }
}

void Player::checkCollision()
{
  if(TheGame::Instance()->m_gameObjects["enemy"] != 0)
  {
    if(SDLGameObject::checkCollision(TheGame::Instance()->m_gameObjects["enemy"]->getDestRect()))
    {
      std::cout << "enemy랑 닿음" << std::endl;
    }
  }

  if(TheGame::Instance()->m_gameObjects["ground1"] != 0)
  {
    if(SDLGameObject::checkCollision(TheGame::Instance()->m_gameObjects["ground1"]->getDestRect()))
      m_isGround = true;
    else
      m_isGround = false;
  }

  if(TheGame::Instance()->m_gameObjects["wall"] != 0)
  {
    if(SDLGameObject::checkCollision(TheGame::Instance()->m_gameObjects["wall"]->getDestRect()))
      m_isObstacle = true;
    else
      m_isObstacle = false;
  }
}

void Player::clean()
{
  
}