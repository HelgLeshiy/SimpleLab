CC=g++
CFLAGS=-c -std=c++11 -Wl,-subsystem,windows
LDFLAGS=-LC:/deps/lib/Release -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
IDFLAGS=-Ideps/include
SOURCES=main.cpp app.cpp ResourceManager.cpp SpriteFont.cpp TextureCache.cpp Functions/Functions.cpp GUI/guiFuncs.cpp Parser/Lexer.cpp Parser/Namescope.cpp Parser/Parser.cpp Widgets/Cursor.cpp Widgets/Layout.cpp Widgets/MultilineEdit.cpp Widgets/SimpleButton.cpp Widgets/TexturedButton.cpp Widgets/Widget.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Release/SimpleLab.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(IDFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(LDFLAGS) $(IDFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -rf **/*.o Release/SimpleLab.exe