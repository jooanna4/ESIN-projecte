OPCIONS = -g -O0 -Wall -Wextra -Wno-sign-compare -std=c++11 -Wno-deprecated

program.exe: driver_easydial.o phone.o call_registry.o easy_dial.o dialog.o
	g++ -o program.exe driver_easydial.o phone.o call_registry.o easy_dial.o dialog.o -lesin

driver_easydial.o: driver_easydial.cpp
	g++ -c driver_easydial.cpp $(OPCIONS) 

phone.o: phone.cpp phone.hpp
	g++ -c phone.cpp $(OPCIONS)

call_registry.o: call_registry.cpp call_registry.hpp phone.cpp phone.hpp
	g++ -c call_registry.cpp $(OPCIONS)

easy_dial.o: easy_dial.cpp easy_dial.hpp call_registry.cpp call_registry.hpp phone.cpp phone.hpp
	g++ -c easy_dial.cpp $(OPCIONS)

dialog.o: dialog.cpp dialog.hpp
	g++ -c dialog.cpp $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rmma *.gch
