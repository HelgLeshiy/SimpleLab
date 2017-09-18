/**
 * \file	RunState.h
 * \brief	Заголовочный файл с описанием основного рабочего состояния
 *
 * Рабочая область для выполнения математических расчетов
 */
#pragma once
#include "BaseState.h"
#include "../Parser/Parser.h"
#include "../Widgets/MultilineEdit.h"

/**
 * \brief Основное состояние приложение
 * 
 * Класс RunState - реализация интерфейса BaseState для математических расчетов.
 */
class RunState : public BaseState
{
public:
	RunState(app *appPtr) : BaseState(appPtr) { }
	
	void onInit(SDL_Renderer *renderer, SpriteFont *spriteFont) override;
	void onEvent(SDL_Event *event) override;
	void onLoop(float deltaTime) override;
	void onRender(SDL_Renderer *renderer, SpriteFont *spriteFont) override;
	void onExit() override;

public:
	/**
	 * Инициализация виджетов
	 */
	void initWidgets(SDL_Renderer *renderer, SpriteFont *spriteFont);

public:
	Namescope *global = nullptr; ///< Глобальная область видимости
	Parser parser; ///< Парсер
	std::string text; ///< Набираемый текст

	MultilineEdit *workspace = nullptr; ///< Виджет рабочей области

	bool touch = false; ///< Нажатие пальца/мыши
	vec2 touchPos; ///< Координаты пальца/курсора

	bool keyboard = false; ///< Виртуальная клавиатура вкл/выкл

	std::vector< std::pair<Widget*, float> > widgets; ///< Остальные виджеты
};