#include <cstdlib>
#include <iostream>
#include <string>


int main (int argc, char** argv)
{
	std::vector<std::string> lines;
	
	for (std::string line; std::getline(std::cin, line); ){
		lines.push_back(line);
	}
	
	for(auto l : lines){
		std::cout << l << "\n";
	}

	return(EXIT_SUCCESS);
}
