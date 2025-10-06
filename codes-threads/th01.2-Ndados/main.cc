#include <global.hh>

#include <vector>
#include <thread>

const int totalDados = 4;
int valores[totalDados];

std::vector<int> valorDados;

void tirarDado(int id, int numCaras){
	std::mt19937 mt(std::random_device{}());
	std::uniform_int_distribution<int> dist(1, numCaras); 
	std::uniform_int_distribution<int> deltaT(1, 10); 

	int valor = dist(mt);
	//int tiempoLanzamiento = deltaT(mt);

	//std::cout << "Dado " << id << ", tiempo lanzamiento: " << tiempoLanzamiento << "\n";

	//std::this_thread::sleep_for(std::chrono::seconds(tiempoLanzamiento));

	valores[id] = valor;	

	valorDados.push_back(valor);

	//std::cout << "Dado " << id << ", valor: " << valor << "\n";
	//std::cout << std::flush;
}


int main(int argc, char* argv[]){
	
	std::thread dados[totalDados];

	// se realiza el fork
	for(int idx=0; idx < totalDados; idx++){
		dados[idx] = std::thread(tirarDado, idx, 6);
	}
	
	// se realiza el join
	for(int idx=0; idx < totalDados; idx++){
		dados[idx].join();
	}

	// De nuevo el thread principal
	for(int idx=0; idx < totalDados; idx++){
		std::cout << valores[idx] << " ";
	}

	std::cout << "\n";

	exit(EXIT_SUCCESS);
}



