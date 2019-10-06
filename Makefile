build:
	g++ --std=c++11 -Wall -Wextra -g   main.cpp -o tema2

.PHONY: clean

run:
	./main

clean:

	#rm out//
	#rm tema2
	cat time.out