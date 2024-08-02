
all: gshare hashed_perceptron tage_sc_l

gshare: gshare.cc
	g++ -c -fPIC gshare.cc -o gshare.o
	g++ -shared -Wl,-soname,libgshare.so -o libgshare.so  gshare.o
	
hashed_perceptron: hashed_perceptron.cc
	g++ -c -fPIC hashed_perceptron.cc -o hashed_perceptron.o
	g++ -shared -Wl,-soname,libhashed_perceptron.so -o libhashed_perceptron.so  hashed_perceptron.o
	
tage_sc_l: tage_sc_l.cc
	g++ -c -fPIC tage_sc_l.cc -o tage_sc_l.o
	g++ -shared -Wl,-soname,libtage_sc_l.so -o libtage_sc_l.so  tage_sc_l.o
	
clean:
	rm *.o *.so
