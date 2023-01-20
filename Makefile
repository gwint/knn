knnclassifier:	dataparser.o main.o dataparser.hpp
	g++ -o knn dataparser.o main.o	

dataparser.hpp:
	g++ -c src/dataparser.cpp

dataparser.o:	src/dataparser.cpp
	g++ -c src/dataparser.cpp 

main.o:	src/main.cpp
	g++ -c src/main.cpp

clean:
	rm -rf knnclassifier ./**/*.o
