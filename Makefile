knn:	dataparser.o src_main.o src/dataparser.hpp src/distancemetric.hpp euclideandistancemetric.o knnclassifier.o statsutils.o
	g++ -o knn dataparser.o euclideandistancemetric.o src_main.o knnclassifier.o statsutils.o

knntest: dataparser.o test_main.o src/dataparser.hpp src/distancemetric.hpp euclideandistancemetric.o knnclassifier.o statsutils.o
	g++ -o knntest dataparser.o euclideandistancemetric.o test_main.o knnclassifier.o statsutils.o -lgtest

knnclassifier.o:	src/knnclassifier.cpp
	g++ -c src/knnclassifier.cpp

dataparser.hpp:
	g++ -c src/dataparser.cpp

distancemetric.hpp:
	g++ -c src/euclideandistancemetric.cpp

dataparser.o:	src/dataparser.cpp
	g++ -c src/dataparser.cpp 

euclideandistancemetric.o:	src/euclideandistancemetric.cpp
	g++ -c src/distancemetric.hpp src/euclideandistancemetric.cpp 

statsutils.o:	src/statsutils.cpp
	g++ -c src/statsutils.cpp

src_main.o:	src/main.cpp
	g++ -c src/main.cpp -o src_main.o

test_main.o:	test/main.cpp
	g++ -c test/main.cpp -o test_main.o

clean:
	rm -rf knn knntest ./**/*.o *.o *.swp
