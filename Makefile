all:
	g++ -o build/application -Idependencies/include/ src/*.cpp -Ldependencies/lib -lglfw3 -lGLEW -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	build/application