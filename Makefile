
laIN:=ex01.in
gaIN:=gaRuleFile.in

gaOUT.txt: laOUT.txt ga.out $(gaIN)
	cat laOUT.txt | ./ga.out  $(gaIN) > gaOUT.txt
laOUT.txt: la.out $(laIN)
	./la.out $(laIN) > laOUT.txt
la.out: la.h la.cpp
	g++ la.cpp -o la.out
ga.out: la.h ga.h ga.cpp
	g++ ga.cpp -o ga.out

.PHONY: clean cleanall rebuild
rebuild: cleanall gaOUT.txt
clean:
	rm -rf la.out ga.out
cleanall:
	rm -rf la.out ga.out laOUT.txt gaOUT.txt