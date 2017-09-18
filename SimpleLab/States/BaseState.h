/**
 * \file	BaseState.h
 * \brief	Заголовочный файл с описанием интерфейса классов состояний
 *
 * Класс BaseState определяет интерфейс для всех состояний приложения.
 */
#pragma once
#include <SDL2/SDL.h>
#include "../SpriteFont.h"

class app;

/**
 * \brief Интерфейс для Состояний
 * 
 * Класс BaseState - базовый абстрактный класс и определяет интерфейс для всех
 * состояний приложения.
 */
class BaseState
{
public:
	/**
	 * Конструктор
	 * 
	 * \param[in] appPtr Указатель на класс-приложение
	 */
	BaseState(app *appPtr) : m_appPtr(appPtr) { }
	
	/**
	 * Инициализация состояния, вызывается при добавлении
	 * состояния в стек Менеджера
	 * 
	 * \param[in] renderer 		Указатель на рендерер
	 * \param[in] spriteFont 	Указатель на рендерер шрифтов
	 */
	virtual void onInit(SDL_Renderer *renderer, SpriteFont *spriteFont) = 0;

	/**
	 * Обработчик событий, вызывается при возникновении неперехваченного
	 * события
	 * 
	 * \param[in] event Указатель на события
	 */
	virtual void onEvent(SDL_Event *event) = 0;

	/**
	 * Основной логический цикл события, вызывается каждый фрейм,
	 * если состояние активно
	 * 
	 * \param[in] deltaTime Количество секунд, прошедшие в предыдущего фрейма
	 */
	virtual void onLoop(float deltaTime) = 0;

	/**
	 * Метод отрисовки данного состояния, вызывается каждый фрейм,
	 * если состояние активно
	 * 
	 * \param[in] renderer 		Указатель на рендерер
	 * \param[in] spriteFont 	Указатель на рендерер шрифтов
	 */
	virtual void onRender(SDL_Renderer *renderer, SpriteFont *spriteFont) = 0;

	/**
	 * Удаление состояния, вызывается при удалении состояния из стека
	 */
	virtual void onExit() = 0;

protected:
	app *m_appPtr = nullptr; ///< указатель на приложение,
							 // для управлением стеком состояний
};