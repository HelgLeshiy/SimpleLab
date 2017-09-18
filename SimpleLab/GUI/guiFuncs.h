/**
 * \file	guiFuncs.h
 * \brief	Вспомогательные функции для отрисовки текстур и текста
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

/**
 * Рендерит текстуру в указанную область видеопамяти с указанием
 * координат и размеров текстуры
 *
 * \param[in] tex 	Указатель на текстуру
 * \param[in] rend 	Указатель на рендерер
 * \param[in] x		x координата назначения
 * \param[in] y		y координата назначения
 * \param[in] w		Ширина области
 * \param[in] h		Высота области
 */
void renderTexture( SDL_Texture *tex, SDL_Renderer *rend, int x, int y, int w, int h );

/**
 * Рендерит текстуру в указанную область видеопамяти с указанием
 * координат. Высота и ширина выбираются автоматически исходя из
 * рамеров текстуры.
 *
 * \param[in] tex 	Указатель на текстуру
 * \param[in] rend 	Указатель на рендерер
 * \param[in] x		x координата назначения
 * \param[in] y		y координата назначения
 */
void renderTexture( SDL_Texture *tex, SDL_Renderer *ren, int x, int y );

/**
 * Рендерит текст на текстуру, 
 * для быстрого доступа к ним из видеопамяти.
 *
 * \param[in] text 		Текст 
 * \param[in] fontFile 	Путь к файлу шрифта .ttf
 * \param[in] textColr	Цвет текста
 * \param[in] fontSize	Размер шрифта
 * \param[in] rend      Рендерер
 */
SDL_Texture *renderText( char *text, char *fontFile, SDL_Color textColr, int fontSize, SDL_Renderer *rend );