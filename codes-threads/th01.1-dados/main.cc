#include <global.hh>

void rollDice(int id, int numMax){
	std::mt19937 mt(std::random_device{}());
	std::uniform_int_distribution<int> dist(1, numMax); 
	int value = dist(mt);
	
	std::cout << "Dice " << id << ": roll\n";
	std::cout << "Dice " << id << " value: " << value << "\n";
	
}


int main(int argc, char* argv[]){

	std::cout << "Total threads = " <<
		std::thread::hardware_concurrency() << 
		std::endl;
	
	std::thread t01(rollDice, 0, 6);
	std::thread t02(rollDice, 1, 6);
	
	t01.join();
	t02.join();

	return(EXIT_SUCCESS);
}

