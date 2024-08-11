.PHONY:ALL
ALL:mysignal loop

mysignal:mysignal.cc
	g++ -o $@ $^ -std=c++11
loop:loop.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f mysignal loop