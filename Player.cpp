#pragma once
#include "Player.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "Vector2D.h"

//Constructor y destructor
Player::Player() {
	m_velocity.setX(0);
	m_velocity.setY(0);
};
Player::~Player() {};

void Player::load(const LoaderParams* pParams) {
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_position.setX(pParams->getX());
	m_position.setY(pParams->getY());
	m_textureID = pParams->getTextureID();
	m_fileName = pParams->getFileName();
	m_spriteNum = pParams->getSpriteNum();
	m_currentRow = pParams->getRowNum();
	TextureManager::Instance()->load(m_fileName, m_textureID, Game::Instance()->getRenderer());

};

//Funcion para mostrar por pantalla la textura mediante la clase TextureManager
void Player::draw() {

	if (dreta) {
		TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), SDL_FLIP_NONE);
	}
	else {

		TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
	}
};

void Player::update()
{
		if (!isCollisionWithTile(m_position)) {
			double velo = 0.1 + (m_velocity.getY() - 0.01);
			m_velocity.setY(velo);
		}
		else {
			m_velocity.setY(0);
		}
		

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
			//m_position.setX(m_position.getX() + 1);
			dreta = true;

				double velo = 0.1 + (m_velocity.getX() - 0.01);
				m_velocity.setX(velo);

				if (m_velocity.getX() >= m_maxVelocity.getX()) {
					m_velocity.setX(3);
				}		

			m_currentFrame = (int)(((Game::Instance()->getTicks()) / 100) % m_spriteNum);

		}
		else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
			//m_position.setX(m_position.getX() - 1);

			dreta = false;
			double velo = -0.1 + (m_velocity.getX() + 0.01);

			m_velocity.setX(velo);

			if (m_velocity.getX() <= -3) {
				m_velocity.setX(-3);
			}

			m_currentFrame = (int)(((Game::Instance()->getTicks()) / 100) % m_spriteNum);
		}
		else {
			if (m_velocity.getX() != 0 && dreta) {
				m_velocity.setX(m_velocity.getX() - 0.2);
				if (m_velocity.getX() <= 0) {
					m_velocity.setX(0);
				}
			}
			else if (m_velocity.getX() != 0 && !dreta) {
				m_velocity.setX(m_velocity.getX() + 0.2);
				if (m_velocity.getX() >= 0) {
					m_velocity.setX(0);
				}
			}
			else if (m_velocity.getX() == 0) {
				m_velocity.setX(0);
			}
			m_currentFrame = 3;

		}	
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
		{
			saltoMax += 0.1;
			if (saltoMax < 1.5)
			{
				double velo = (m_velocity.getY() - 0.3);
				m_velocity.setY(velo);
			}
		}
	//Variable para dar animacion a la textura

	GameObject::update();
	CollisionObject::update();
};

void Player::clean() {}


;