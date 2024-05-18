CC = clang++
CFLAGS = -Iinclude -Wall -Ipreprocessor/include -Ilexer/include -Ierrors/include -Iparser/include -Iutils/include

OBJS              = $(patsubst %.cpp,%.o,$(wildcard *.cpp)) 
OBJS_UTILS        = $(notdir $(patsubst %.cpp,%.o,$(wildcard utils/*.cpp)))
OBJS_PREPROCESSOR = $(notdir $(patsubst %.cpp,%.o,$(wildcard preprocessor/*.cpp)))
OBJS_LEXER        = $(notdir $(patsubst %.cpp,%.o,$(wildcard lexer/*.cpp)))
OBJS_ERROR        = $(notdir $(patsubst %.cpp,%.o,$(wildcard errors/*.cpp)))
OBJS_PARSER       = $(notdir $(patsubst %.cpp,%.o,$(wildcard parser/*.cpp)))

SRC_UTILS        = $(wildcard utils/*.cpp)
SRC_PREPROCESSOR = $(wildcard preprocessor/*.cpp)
SRC_LEXER        = $(wildcard lexer/*.cpp)
SRC_ERROR        = $(wildcard errors/*.cpp)
SRC_PARSER       = $(wildcard parser/*.cpp)
DEBUG            = 

OUTPUT = mic
$(OUTPUT): $(OBJS) $(OBJS_UTILS) $(OBJS_PREPROCESSOR) $(OBJS_LEXER) $(OBJS_ERROR) $(OBJS_PARSER)
	$(CC) $(CFLAGS) $(patsubst %.o,build/%.o,$^) -lstdc++fs -o $@

format:
	clang-format -i $(SRC_UTILS) $(SRC_PREPROCESSOR) $(SRC_LEXER) $(SRC_ERROR) $(SRC_PARSER) --style=file:"./.clang-format"

clean:
	rm $(patsubst %.o,build/%.o,$(OBJS) $(OBJS_UTILS) $(OBJS_PREPROCESSOR) $(OBJS_LEXER) $(OBJS_ERROR) $(OBJS_PARSER)) $(OUTPUT)

%.o: %.cpp
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o build/$@

$(OBJS_UTILS): $(SRC_UTILS)
	$(CC) $(DEBUG) $(CFLAGS) -c utils/$(patsubst %.o,%.cpp,$@) -o build/$@

$(OBJS_PREPROCESSOR): $(SRC_PREPROCESSOR)
	$(CC) $(DEBUG) $(CFLAGS) -c preprocessor/$(patsubst %.o,%.cpp,$@) -o build/$@

$(OBJS_LEXER): $(SRC_LEXER)
	$(CC) $(DEBUG) $(CFLAGS) -c lexer/$(patsubst %.o,%.cpp,$@) -o build/$@

$(OBJS_ERROR): $(SRC_ERROR)
	$(CC) $(DEBUG) $(CFLAGS) -c errors/$(patsubst %.o,%.cpp,$@) -o build/$@

$(OBJS_PARSER): $(SRC_PARSER)
	$(CC) $(DEBUG) $(CFLAGS) -c parser/$(patsubst %.o,%.cpp,$@) -o build/$@

