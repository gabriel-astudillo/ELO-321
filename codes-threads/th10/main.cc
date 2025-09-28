#include <global.hh>
#include <checkArgs.hpp>

std::vector<uint64_t> g_V;


std::mutex g_incMutex;

void sumaParcial(uint64_t &suma,\
                 size_t beginIndex,\
                 size_t endIndex)
{
	suma = 0;
	for (size_t i = beginIndex; i < endIndex; ++i) {
		suma += g_V[i];		
	}
}

void llenado(const uint64_t& e)
{
	g_V.push_back(e);
}

void llenadoParcial(size_t beginIdx, size_t endIdx) {

	/*
		La estructura vector, debido a que es una lista enlazada,
		no es thread safe, por lo que sólo un thread puede realizar
		un push_back()  ==> cuello de botella
	*/
	for(size_t i = beginIdx; i < endIdx; ++i){
		g_incMutex.lock();
		g_V.push_back(i);
		g_incMutex.unlock();
	}

};


int main(int argc, char** argv)
{

	uint64_t totalElementos;

	auto argumentos = (std::shared_ptr<checkArgs>) new checkArgs(argc, argv);
	
	totalElementos = argumentos->getArgs().totalElementos;
	

	uint64_t sumaSerial = 0;
	uint64_t suma1 = 0;
	uint64_t suma2 = 0;
	uint64_t sumaThreads = 0;

	auto start = std::chrono::high_resolution_clock::now();
	
	/*
	for(size_t i=0; i <= totalElementos; i++) {
		llenado(i);
	}
	*/
	
	std::thread llenado_t1(llenadoParcial, 0, totalElementos / 2);
	std::thread llenado_t2(llenadoParcial, totalElementos / 2, totalElementos);	
	llenado_t1.join();
	llenado_t2.join();
	
	std::cout << std::endl;
	
	auto end     = std::chrono::high_resolution_clock::now(); 
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTime00 = elapsed.count();

	//======SERIAL======
	start = std::chrono::high_resolution_clock::now();
	
	sumaParcial( std::ref(sumaSerial), 0, g_V.size() );
	
	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTime01 = elapsed.count();

	//======THREADS======
	//(1) Separación del trabajo
	start = std::chrono::high_resolution_clock::now();
	
	std::thread t1(sumaParcial, std::ref(suma1), 0, g_V.size() / 2);
	std::thread t2(sumaParcial, std::ref(suma2), g_V.size() / 2, g_V.size());

	t1.join();
	t2.join();

	//(2) Reducción (Consolidación de resultados parciales)
	sumaThreads = suma1 + suma2;
	
	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTime02 = elapsed.count();
	
	
	std::cout << "====Llenado arreglo====" << std::endl;
	std::cout << "Tiempo        :"  << totalTime00<< "[ms]" << std::endl;
	

	std::cout << "====Serial====" << std::endl;
	std::cout << "sumaSerial    : " << sumaSerial << std::endl;
	std::cout << "Tiempo serial :"  << totalTime01 << "[ms]" << std::endl;

	std::cout << "====Threads====" << std::endl;
	std::cout << "suma1           : " << suma1 << std::endl;
	std::cout << "suma2           : " << suma2 << std::endl;
	std::cout << "suma1 + suma2   : " << sumaThreads << std::endl;
	std::cout << "Tiempo paralelo :"  << totalTime02 << "[ms]" << std::endl;

	return(EXIT_SUCCESS);
}

