#include "app.h"
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Functions\Functions.h"
#include "Functions\GraphFunctions.h"
#include "ResourceManager.h"
#include "prefs.h"

#include "Widgets/SimpleButton.h"
#include "Widgets/TexturedButton.h"
#include "Widgets/Layout.h"

std::string dtoa( double a )
{
	std::stringstream ss;
	ss << a;
	return ss.str(  );
}

void app::init( )
{
	SDL_Init( SDL_INIT_EVERYTHING );
	IMG_Init( IMG_INIT_PNG );
	TTF_Init(  );

	wnd = SDL_CreateWindow( "SimpleLab for Smartphones", 100, 100, SCR_W, SCR_H, 0 );
	rnd = SDL_CreateRenderer( wnd, -1, SDL_RENDERER_SOFTWARE );
	global = new Namescope(  );
	spriteFont.init( rnd, "data/images/Bisasam_20x20_ascii.png", 16, 16 );
	global->setVar( std::make_shared< TypedValue<double> >( 3.141592653589793 ), "pi" );
	global->setVar( std::make_shared< TypedValue<double> >( 2.718281828459045 ), "exp" );

	SDL_Rect txtInp;
	txtInp.x = 0;
	txtInp.y = 860;
	txtInp.w = 720;
	txtInp.h = 64;

	SDL_RenderDrawRect( rnd, &txtInp );

	parser.operatorMapInit();

	global->installFunction( f_sin,			1, "d",		"sin"	);
	global->installFunction( f_cos,			1, "d",		"cos"	);
	global->installFunction( f_tan,			1, "d",		"tan"	);
	global->installFunction( f_ctan,		1, "d",		"ctan"	);
	global->installFunction( f_sinh,		1, "d",		"sinh"	);
	global->installFunction( f_cosh,		1, "d",		"cosh"	);
	global->installFunction( f_tanh,		1, "d",		"tanh"	);
	global->installFunction( f_ctanh,		1, "d",		"ctanh" );
	global->installFunction( f_logn,		1, "d",		"ln"	);
	global->installFunction( f_log,			2, "dd",	"log"	);
	global->installFunction( f_lengthStr,	1, "s",		"strlen");
	global->installFunction( f_random,		2, "dd",	"rand"	);
	global->installFunction( f_integral,	3, "sdd",	"int"	);
	global->installFunction( f_minFunc,		3, "sdd",	"minF"	);
	global->installFunction( f_maxFunc,		3, "sdd",	"maxF"	);

	global->installFunction( f_arcsin,		1, "d",		"asin"	);
	global->installFunction( f_arccos,		1, "d",		"acos"	);
	global->installFunction( f_arctan,		1, "d",		"atan"	);
	global->installFunction( f_arcctan,		1, "d",		"actan"	);
	global->installFunction( f_arcsinh,		1, "d",		"asinh"	);
	global->installFunction( f_arccosh,		1, "d",		"acosh"	);
	global->installFunction( f_arctanh,		1, "d",		"atanh"	);
	global->installFunction( f_arcctanh,	1, "d",		"actanh");

	global->installFunction(f_backlogn, 1, "d", "backlogn");
	global->installFunction(f_backlog, 2, "dd", "backlog");

	global->installFunction(f_graph, 3, "sdd", "graph");

	global->registerBackFunction("sin", "asin");
	global->registerBackFunction("asin", "sin");
	global->registerBackFunction("cos", "acos");
	global->registerBackFunction("acos", "cos");
	global->registerBackFunction("tan", "atan");
	global->registerBackFunction("atan", "tan");
	global->registerBackFunction("ctan", "actan");
	global->registerBackFunction("actan", "ctan");
	global->registerBackFunction("sinh", "asinh");
	global->registerBackFunction("asinh", "sinh");
	global->registerBackFunction("cosh", "acosh");
	global->registerBackFunction("acosh", "cosh");
	global->registerBackFunction("tanh", "atanh");
	global->registerBackFunction("atanh", "tanh");
	global->registerBackFunction("ctanh", "actanh");
	global->registerBackFunction("actanh", "ctanh");
	global->registerBackFunction("ln", "backlogn");
	global->registerBackFunction("log", "backlog");

	initWidgets();

	AppRef::InitGraphSystem(&widgets);
}
void app::destroyApp( )
{
	delete global;
	SDL_DestroyRenderer( rnd );
	SDL_DestroyWindow( wnd );
	TTF_Quit(  );
	IMG_Quit(  );
	SDL_Quit(  );
}

void app::event( SDL_Event *evt )
{
	switch (appState)
	{
	case MainAppState::LOGO:
	{
		switch (evt->type)
		{
#ifdef _ANDROID_
		case SDL_FINGERDOWN:
		{
#else
		case SDL_MOUSEBUTTONDOWN:
		{
#endif
			appState = MainAppState::RUN;
			break;
		}
		break;
		}

	case MainAppState::RUN:
	{
		switch (evt->type)
		{
		case SDL_QUIT:
			appState = MainAppState::EXIT;
			break;
#ifdef _ANDROID_
		case SDL_FINGERDOWN:
		{
#else
		case SDL_MOUSEBUTTONDOWN:
		{
#endif
			if (!SDL_IsTextInputActive())
			{
				SDL_StartTextInput();
				keyboard = true;
			}
			//spriteFont.draw(rnd, text.c_str(  ), vec2(720, 64), vec2(1.f, 1.f), ColorRGBA8(255, 255, 0, 255), FontAlign::LEFT);

			break;
		}

		case SDL_KEYDOWN:
			if (evt->key.keysym.sym == SDLK_RETURN)
			{
				double result;
				try
				{
					result = parser.parse(workspace->getLastLine(), global);
				}
				catch (std::exception &ex)
				{
					workspace->writeLine(ex.what());
					break;
				}
				std::string varName = "  " + parser.getLastVar();
				varName += " = " + dtoa(result);
				workspace->writeLine(varName);
			}
			break;
		}

		for (auto widget = widgets.rbegin(); widget != widgets.rend(); ++widget)
			if (widget->first->onEvent(evt)) return;
		break;
	}
	}
	}
}

void app::loop( )
{
	switch (appState)
	{
	case MainAppState::LOGO:
	{
		switch (logoState)
		{
		case LogoState::INCREASE:
			logoTimer += 0.01;
			if (logoTimer >= 1.f) logoState = LogoState::DECREASE;
			break;
		case LogoState::DECREASE:
			logoTimer -= 0.01;
			if (logoTimer <= 0 ) appState = MainAppState::RUN;
			break;
		}
	}	break;

	case MainAppState::RUN:
		for (auto widget = widgets.begin(); widget != widgets.end(); ++widget)
			widget->first->onUpdate(1.f);
		break;
	}
}

void app::rend( )
{
	SDL_SetRenderDrawColor( rnd, 0, 0, 0, 255 );
	SDL_RenderClear( rnd );

	renderTexture(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Background.png"), rnd, 0, 0, SCR_W, SCR_H);
	SDL_Rect screenRect = { 0, 0, SCR_W, SCR_H };
	SDL_SetRenderDrawColor(rnd, 24, 24, 25, 255);
	SDL_RenderFillRect(rnd, &screenRect);
	SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);

	switch (appState)
	{
	case MainAppState::LOGO:
	{
		SDL_Texture *logoTexture = ResourceManager::getTexture(rnd, "data/textures/bigLogo.png");
		int logoW, logoH;

		SDL_QueryTexture(logoTexture, nullptr, nullptr, &logoW, &logoH);
		SDL_SetTextureBlendMode(ResourceManager::getTexture(rnd, "data/textures/bigLogo.png"), SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(logoTexture, 255 * logoTimer);
		SDL_Rect foxRect;
		foxRect.x = 0;
		foxRect.w = SCR_W;
		SDL_RenderCopy(rnd, logoTexture, 0, &foxRect);
		//renderTexture(logoTexture, rnd, 0, SCR_H / 2 - logoH / 2, logoW, SCR_H / 2 + logoH / 2);
	}	break;

	case MainAppState::RUN:
	{
		for (auto widget : widgets)
			widget.first->render(rnd, spriteFont);
	}	break;
	}

	SDL_RenderPresent( rnd );
}

void app::initWidgets()
{
	std::vector<TexturedButton*> buttons;
	int posX = 64;

	// Undo
	buttons.push_back(new TexturedButton());
	buttons.back()->init(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Unpressed_Undo.png"),
						 ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Pressed_Undo.png"));
	buttons.back()->setRect(vec2(posX, 0), vec2(100, 60));
	posX += 77;

	// Redo
	buttons.push_back(new TexturedButton());
	buttons.back()->init(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Unpressed_Redo.png"),
						 ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Pressed_Redo.png"));
	buttons.back()->setRect(vec2(posX, 0), vec2(100, 60));
	posX += 77;

	// Cls
	buttons.push_back(new TexturedButton());
	buttons.back()->init(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Unpressed_CLS.png"),
						 ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Pressed_CLS.png"));
	buttons.back()->setRect(vec2(posX, 0), vec2(100, 60));
	posX += 77;

	// Save
	buttons.push_back(new TexturedButton());
	buttons.back()->init(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Unpressed_Save.png"),
						 ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Pressed_Save.png"));
	buttons.back()->setRect(vec2(posX, 0), vec2(100, 60));
	posX += 77;

	// X
	buttons.push_back(new TexturedButton());
	buttons.back()->init(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Unpressed_EXIT.png"),
						 ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Pressed_EXIT.png"),
						 [this]() { appState = MainAppState::EXIT; });
	buttons.back()->setRect(vec2(SCR_W - 10 - 84, 6), vec2(84, 54));

	Layout *layout = new Layout;
	layout->init(ResourceManager::getTexture(rnd, "data/textures/layout.png"));
	layout->setInnerStartPosition(vec2(10, 10));
	layout->setRect(vec2(SCR_W, 0), vec2(280, SCR_H));

	for (auto button : buttons)
		widgets.push_back(std::make_pair(button, 0.f));

	widgets.push_back(std::make_pair(layout, 1.f));

	float y = 0;
	for (auto it = global->functionsBegin(); it != global->functionsEnd(); ++it)
	{
		TexturedButton *button = new TexturedButton(layout);
		button->setText(it->first, ColorRGBA8(43, 200, 200, 255));
		button->init(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Unpressed.png"),
					 ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Pressed.png"),
		[this, it]() {
			std::string autoWriteLine = it->first + "(";
			size_t dCurPos = autoWriteLine.length();
			bool firstString = false;
			for (int i = 0; i < it->second->argnum - 1; ++i)
			{
				if (it->second->argTypes[i] == 's')
				{
					autoWriteLine += "\"\"";
					if (i == 0) firstString = true;
				}
				autoWriteLine += ", ";
			}
			autoWriteLine += ')';
			workspace->insertToCursor(autoWriteLine);
			workspace->shiftCursor(firstString ? dCurPos + 1 : dCurPos);
		});
		button->setRect(vec2(0.f, y), vec2(180, 60));
		y += 64;
		widgets.push_back(std::make_pair(button, 2.f));
	}

	workspace = new MultilineEdit;
	workspace->init(spriteFont.getFontWidth(), spriteFont.getFontHeight());
	workspace->setRect(vec2(0, 0), vec2(SCR_W, SCR_H));

	widgets.push_back(std::make_pair(workspace, -1.f));

	std::stable_sort(widgets.begin(), widgets.end(), [](const std::pair<Widget*, float>& a, const std::pair<Widget*, float>& b) { return a.second < b.second; });
}

int app::execute( )
{
	init(  );
	SDL_Event evt;
	while ( appState != MainAppState::EXIT )
	{
		while ( SDL_PollEvent( &evt ) )
			event ( &evt );
		loop(  );	//Логика
		rend(  );	//Отрисовка
		SDL_Delay( 10 );
	}
	destroyApp(  );
	return 0;
}

app::app( )
{ }


app::~app( )
{ }
