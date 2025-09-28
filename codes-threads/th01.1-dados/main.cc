#include <global.hh>

void rollDice(int id, int numMax){
	std::mt19937 mt(std::random_device{}());
	std::uniform_int_distribution<int> dist(1, numMax); 
	int value = dist(mt);
	
	std::cout << "Dice " << id << ": roll\n";
	std::cout << "Dice " << id << " value: " << value << "\n";
	
}


int main(int argc, char* argv[]){

	const int MAX_DADOS = 5; // Número de dados a lanzar
	int MAX_SIDES = 6; // Número de caras por dado

	std::thread threadsDice[MAX_DADOS];

	for (int i = 0; i < MAX_DADOS; ++i) {
        threadsDice[i] = std::thread(rollDice, i + 1, MAX_SIDES);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < MAX_DADOS; ++i) {
        threadsDice[i].join();
    }
	
	std::cout << "Total threads = " <<
		std::thread::hardware_concurrency() << 
		std::endl;
	
	std::thread t01(rollDice, 0, 6);
	std::thread t02(rollDice, 1, 6);
	
	t01.join();
	t02.join();

	return(EXIT_SUCCESS);
}

