#include <global.hh>

#include <thread>

void tirarDado(int id, int numMax){
	std::mt19937 mt(std::random_device{}());
	std::uniform_int_distribution<int> dist(1, numMax); 
	int valor = dist(mt);
	
	std::cout << "Dado " << id << ", valor: " << valor << "\n";
}


int main(int argc, char* argv[]){

	std::thread t01 = std::thread(tirarDado, 0, 6);
	std::thread t02 = std::thread(tirarDado, 1, 6);
	
	t01.join();
	t02.join();

	exit(EXIT_SUCCESS);
}

