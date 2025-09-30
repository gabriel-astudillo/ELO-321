#include <global.hh>

#include <thread>

void tirarDado(int id, int numCaras){
	std::mt19937 mt(std::random_device{}());
	std::uniform_int_distribution<int> dist(1, numCaras); 
	std::uniform_int_distribution<int> deltaT(1, 10); 

	int valor = dist(mt);
	int tiempoLanzamiento = deltaT(mt);

	std::cout << "Dado " << id << ", tiempo lanzamiento: " << tiempoLanzamiento << "\n";

	std::this_thread::sleep_for(std::chrono::seconds(tiempoLanzamiento));
	
	std::cout << "Dado " << id << ", valor: " << valor << "\n";
	std::cout << std::flush;
}


int main(int argc, char* argv[]){

	std::thread t01 = std::thread(tirarDado, 0, 6);
	std::thread t02 = std::thread(tirarDado, 1, 6);
	
	t01.join();
	t02.join();

	exit(EXIT_SUCCESS);
}



