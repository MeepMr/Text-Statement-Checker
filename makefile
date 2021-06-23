run: Text-Statement-Checker.sh
	./Text-Statement-Checker.sh ./test-candidates

Text-Statement-Checker.sh: main.cpp ./zzz_compiler-output/file-management.o ./zzz_compiler-output/directory-management.o ./zzz_compiler-output/constraint-manager.o
	g++ -o Text-Statement-Checker.sh main.cpp ./zzz_compiler-output/file-management.o ./zzz_compiler-output/directory-management.o ./zzz_compiler-output/constraint-manager.o

./zzz_compiler-output/file-management.o: ./file-manger/file-management.cpp
	g++ -o ./zzz_compiler-output/file-management.o -c ./file-manger/file-management.cpp

./zzz_compiler-output/directory-management.o: ./file-manger/directory-management.cpp
	g++ -o ./zzz_compiler-output/directory-management.o -c ./file-manger/directory-management.cpp

./zzz_compiler-output/constraint-manager.o: ./constraint-manager/constraint-manager.cpp
	g++ -o ./zzz_compiler-output/constraint-manager.o -c ./constraint-manager/constraint-manager.cpp