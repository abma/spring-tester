
springtester:
	g++ main.cpp -g -Wall -O0 -o springtester

clean:
	rm -rf springtester

run:
	./springtester --spring /home/abma/local/spring/master/bin/spring-headless

