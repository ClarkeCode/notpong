
RAYLIB_OBJ_FILES=`ls raylib/*.o`

all:
	echo $(RAYLIB_OBJ_FILES)
	echo $('ls raylib/*.o')
	g++ -g src/pong_main.cpp $(RAYLIB_OBJ_FILES) -o build/pong_main.exe
