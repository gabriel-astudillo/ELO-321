#include <global.hh>

#include <thread>

void threadMain(std::string sym, const uint64_t cMax){
	
	double total = 1.0;
	for(size_t i = 0; i < cMax; ++i) {
		//std::cout << sym;
		total *= 1.0000001* sin(i);
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(10000));

}


int main(int argc, char* argv[]){

	int total = atoi(argv[1]);

	uint64_t iteraciones = 20000000000;
    
	std::thread hilos[500];

	for(int i=0; i < total; i++){
		hilos[i] = std::thread(threadMain, "*", iteraciones);
	}

	for(int i=0; i < total; i++){
		hilos[i].join();
	}

	/*std::thread t01(threadMain, "." , cantidadSimbolos);
	std::thread t02(threadMain, "*", cantidadSimbolos);
    std::thread t03(threadMain, "+", cantidadSimbolos);

	t01.join();
	t02.join();
    t03.join();*/
	
	std::cout << std::endl;
	
	return(EXIT_SUCCESS);
}



/*
std::mutex g_mux;
//g_mux.lock();
//g_mux.unlock();

*/
