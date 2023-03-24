CC = clang++
CFLAGS = -Iinclude -Wall -Ipreprocessor/include -Ilexer/include -Ierrors/include -Iparser/include

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp)) 
OBJS_PREPROCESSOR = $(notdir $(patsubst %.cpp,%.o,$(wildcard preprocessor/*.cpp)))
OBJS_LEXER = $(notdir $(patsubst %.cpp,%.o,$(wildcard lexer/*.cpp)))
OBJS_ERROR = $(notdir $(patsubst %.cpp,%.o,$(wildcard errors/*.cpp)))
OBJS_PARSER = $(notdir $(patsubst %.cpp,%.o,$(wildcard parser/*.cpp)))

SRC_PREPROCESSOR = $(wildcard preprocessor/*.cpp)
SRC_LEXER = $(wildcard lexer/*.cpp)
SRC_ERROR = $(wildcard errors/*.cpp)
SRC_PARSER = $(wildcard parser/*.cpp)

OUTPUT = mic
$(OUTPUT): $(OBJS) $(OBJS_PREPROCESSOR) $(OBJS_LEXER) $(OBJS_ERROR) $(OBJS_PARSER)
	$(CC) $(CFLAGS) $(patsubst %.o,build/%.o,$^) -lstdc++fs -o $@

clean:
	rm $(patsubst %.o,build/%.o,$(OBJS) $(OBJS_PREPROCESSOR) $(OBJS_LEXER) $(OBJS_ERROR) $(OBJS_PARSER)) $(OUTPUT)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o build/$@

$(OBJS_PREPROCESSOR): $(SRC_PREPROCESSOR)
	$(CC) $(CFLAGS) -c preprocessor/$(patsubst %.o,%.cpp,$@) -o build/$@

$(OBJS_LEXER): $(SRC_LEXER)
	$(CC) $(CFLAGS) -c lexer/$(patsubst %.o,%.cpp,$@) -o build/$@

$(OBJS_ERROR): $(SRC_ERROR)
	$(CC) $(CFLAGS) -c errors/$(patsubst %.o,%.cpp,$@) -o build/$@

$(OBJS_PARSER): $(SRC_PARSER)
	$(CC) $(CFLAGS) -c parser/$(patsubst %.o,%.cpp,$@) -o build/$@

