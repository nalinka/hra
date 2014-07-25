all: main 

main: main.cpp sorter.o 
	g++ $^ -o main `allegro-config --libs` 

sorter.o: sorter.cpp sorter.h 
	g++ -c sorter.cpp -o sorter.o `allegro-config --libs` 

clean:
	 rm -f main sorter.o 

