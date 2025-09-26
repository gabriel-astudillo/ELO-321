#include <global.hh>

#include <csignal>
#include <unistd.h> 

void signal_handler( int signal_num ) { 
	//static int contador = 1;
	std::cout << "Interrupt signal is (" << signal_num << ").\n";

	
	//if(contador++ >= 3){
	//	exit(EXIT_SUCCESS);
	//}
} 


int main(int argc, char* argv[])
{
	int count = 0; 
	
	// register the signals and the signal handler   
	std::signal(SIGTERM, signal_handler);   
	std::signal(SIGINT, signal_handler);  
	std::signal(SIGKILL, signal_handler);  
	   
	  
	while(++count) { 
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Hello ... PID=" << getpid() << std::endl; 
		if( count == 10 ) {
			std::raise(SIGKILL); 
		} 
	}
	
	return EXIT_SUCCESS;
}
