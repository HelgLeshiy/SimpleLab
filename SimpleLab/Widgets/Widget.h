/**
 * \file	Widget.h
 * \brief	Заголовочный файл с описанием интерфейса классов виджетов
 *
 * Класс Widget определяет интерфейс для всех виджетов приложения.
 */
#pragma once

#include <SDL2/SDL.h>

#include <string>
#include <functional>
#include "../GUI/gfx.h"
#include "../SpriteFont.h"

/**
 * \brief Интерфейс виджетов
 * 
 * Виджеты - графические элементы упаравления и взаимодействия с пользовотелями
 */
class Widget
{
public:
	/**
	 * Конструктор
	 * 
	 * \param[in] parent Родитель данного виджета по иерархии или nullptr
	 * 					 если его нет
	 */
	Widget(Widget *parent = nullptr) : m_parent(parent) { }
	virtual ~Widget() { }

	/**
	 * Отрисовка виджета
	 * 
	 * \param[in] renderer 		Указатель на рендерер
	 * \param[in] spriteFont 	Указатель на рендерер шрифтов
	 */
	virtual void render(SDL_Renderer *renderer, SpriteFont& spriteFont) = 0;

	/**
	 * Обработчик события
	 * 
	 * \param[in] event Событие
	 *
	 * \return true, если событие было перехвачено виджетом
	 */
	bool onEvent(SDL_Event *event);

	/**
	 * Обновление виджета, вызывается каждый фрейм для анимации
	 * 
	 * \param[in] deltaTime Количество секунд, прошедшие в предыдущего фрейма
	 */
	virtual void onUpdate(float deltaTime) { }

	/**
	 * Установка положения и размеров виджета
	 * 
	 * \param[in] pos  Координаты
	 * \param[in] dims Размеры
	 */
	void setRect(const vec2& pos, const vec2& dims) { m_position = pos; m_dimensions = dims; }

	/**
	 * Установка смещения относительно родительских координат
	 * 
	 * \param[in] pos  Координаты относительно родителя
	 */
	void setInnerStartPosition(const vec2& pos) { m_innerStartPos = pos; }

	/**
	 * Перемещает виджет в экранной плоскости
	 * 
	 * \param[in] velocity  Смещение
	 */
	void move(const vec2& velocity) { m_position += velocity; }

	/**
	 * \return Координаты виджета
	 */
	const vec2& getPosition() const { return m_position; }

	/**
	 * \return Размеры виджета
	 */
	const vec2& getDimensions() const { return m_dimensions; }

	/**
	 * \return Смещение относительно родителя виджета
	 */
	const vec2& getInnerStartPos() const { return m_innerStartPos; }

private:
	virtual void onTouch(int x, int y) { }
	virtual void onDetouch(int x, int y) { }
	virtual void onKeyDown(int key) { }
	virtual void onKeyUp(int key) { }
	virtual void onSwipe(int x, int y, float dx, float dy) { }
	virtual void onTextInput(const char *text) { }

protected:
	Widget *m_parent = nullptr;

	vec2 m_position;
	vec2 m_innerStartPos;
	vec2 m_dimensions;

	bool m_pressed = false;
};





