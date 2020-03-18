.PHONY: clean run  #Tell make that 'clean' and 'run' are not associated with building files

#Compile source files and produce executable
all : ok.o
	cc -o ok ok.c
#Remove object and temp files
clean : 
	rm ok *.o
#Enter word to search dict for with : make run word="____"
run :
	./ok "$(word)"
