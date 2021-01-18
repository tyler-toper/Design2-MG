SFMLDIR = C:/SFML-2.5.1
SFML = -I$(SFMLDIR)/include -L$(SFMLDIR)/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network 

main: 
	Xcopy C:\SFML-2.5.1\bin build
	g++ -o ./build/MonsterGenome *.cpp $(SFML)
	./build/MonsterGenome