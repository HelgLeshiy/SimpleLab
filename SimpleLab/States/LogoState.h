/**
 * \file	LogoState.h
 * \brief	Заголовочный файл с описанием состояния заставки
 *
 * Заставка появляется на некоторое время, затем плавно исчезает,
 * после чего управление передается основному состоянию приложения
 */
#pragma once
#include "BaseState.h"

// Перечисление состояний логотипа
enum class LogoStateType
{
	INCREASE, //< Появляющееся
	DECREASE  //< Убывающее
};

/**
 * \brief Состояние заставки
 * 
 * Класс LogoState - реализация интерфейса BaseState для состояния заставки.
 */
class LogoState : public BaseState
{
public:
	LogoState(app *appPtr) : BaseState(appPtr) { }
	
	void onInit(SDL_Renderer *renderer, SpriteFont *spriteFont) override;
	void onEvent(SDL_Event *event) override;
	void onLoop(float deltaTime) override;
	void onRender(SDL_Renderer *renderer, SpriteFont *spriteFont) override;
	void onExit() override;

public:
	LogoStateType logoState = LogoStateType::INCREASE; ///< Состояние логотипа
	float logoTimer = 0.f; ///< Таймер
};