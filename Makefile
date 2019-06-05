
laIN:=ex01.in
GA:=ga3

gaOUT.txt: laOUT.txt $(GA).out
	cat laOUT.txt | ./$(GA).out > gaOUT.txt
laOUT.txt: la.out $(laIN)
	./la.out $(laIN) > laOUT.txt
la.out: la.h la.cpp
	g++ la.cpp -o la.out
$(GA).out: la.h ga.h $(GA).cpp
	g++ $(GA).cpp -o $(GA).out

.PHONY: clean cleanall rebuild
rebuild: cleanall gaOUT.txt
clean:
	-rm -rf *.out
cleanall:
	-rm -rf *.out *.txt