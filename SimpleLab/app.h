/**
 * \file	app.h
 * \brief	Заголовочный файл с описанием класса приложения
 */
#pragma once
#include <SDL2/SDL.h>
#include "SpriteFont.h"
#include <stack>
#include <sstream>

class BaseState;

/**
 * \brief Главный класс приложения
 * 
 * Класс app управляет основными ресурсами приложения, созданием окна,
 * выбором графических устройств, управляет стеком состояний
 * через главный цикл приложения
 */
class app
{
private:
	SDL_Window *wnd = nullptr;		///< Окно приложения
	SDL_Renderer *rnd = nullptr;	///< Hardware рендерер

	void init(  );
	void destroyApp(  );
	void onEvent(SDL_Event *event);
	void onLoop(float deltaTime);
	void rend(  );

	SpriteFont spriteFont;			///< Рендерер шрифтов

	float fps = 60;					///< Ограничение FPS

	std::stack<BaseState*> m_states; ///< Стек состояний

public:
	/**
	 * Запуск приложения
	 *
	 * \return 0 либо 1, если произошла критическая ошибка
	 */
	int execute(  );

	/**
	 * Помещает состояние в стек
	 *
	 * \param[in] state Объект дочернего класса BaseState
	 */
	void pushState(BaseState *state);

	/**
	 * Удаляет текущее состояние
	 */
	void popState();

	app(  );
	~app(  );

	template <typename T>
	static std::string toString(T a)
	{
		std::stringstream ss;
		ss << a;
		return ss.str();
	}
};

