#include "cppngrok.h"


/*
* AUTHOR : demon-i386 / KB1te
* LICENSE : GPL v3.0
* VERSION : 0.1.0
*/

using namespace std;
bool log_handler;
const char* path;



//  return type = struct address_handler declared in cppngrok.h
address_handler CppngrokHandler::UrlBuilder(std::string regcheck) { // address_handler alocator, this will alocate address_handler structure with data and return address_handler
	std::regex httpsrgx("http://[a-zA-Z0-9.ngrok.io]+[^a-zA-Z/:localhost]io");
	std::regex httprgx("https://[a-zA-Z0-9.ngrok.io]+[^a-zA-Z/:localhost]io");
	std::regex tcprgx("(tcp://)[a-zA-Z0-9.]+[^a-zA-Z/:localhost]io");
	std::regex tlsrgx("(tls://)[a-zA-Z0-9.]+[^a-zA-Z/:localhost]io");
	std::smatch match;
	address_handler addr_handler;
	if (std::regex_search(regcheck, match, httpsrgx)) {
		addr_handler.ext_https = match[0];
		cout << "MATCH :: " << match[0] << endl;
		cout << "GOTCHA :: " << addr_handler.ext_https << endl;
	}

	if (std::regex_search(regcheck, match, httprgx)) {
		addr_handler.ext_http = match[0];
		cout << "MATCH :: " << match[0] << endl;
		cout << "GOTCHA :: " << addr_handler.ext_http << endl;  
	} 

	if (std::regex_search(regcheck, match, tcprgx)) {
		addr_handler.ext_tcp = match[0];
	} 

	if (std::regex_match(regcheck, match, tlsrgx)) {
		addr_handler.ext_tls = match[0];
	} 
	return addr_handler;
}

address_handler CppngrokHandler::bind() { // return type = struct address_handler declared in cppngrok.h
	char *buff;
	buff = (char *) path;
	std::string response = "";
	strncat(buff," http 80 --log stdout", 21);


	redi::ipstream is(buff);

	cout << "BUFF WITH ARGS :: " << buff << endl;
	// FILE *pPipe = popen(buff, "r");
	// if(pPipe == NULL){
	//	cout << "[!] PIPE ERROR" << endl;
	//}

	char buf[512];
	memset(buf, 0, sizeof(buf));
	unsigned int i = 0;
	struct address_handler pAddr;

	//for(i; i<512;i++){
	//	if(fgets(buf, sizeof(buf), pPipe) != NULL){
	//		size_t len = strlen(buf);
	//		if (len > 0 && buf[len-1] == '\n') {
	//			buf[--len] = '\0';
	//		}
	//	}
	std::string outBuff;
	for(i; i<7; i++){
		std::getline(is, outBuff);
		cout << "[ " << i << " ] " << outBuff << endl;
		address_handler pAddr;;
		pAddr = CppngrokHandler::UrlBuilder(outBuff);
	}
	is.close();
	cout << pAddr.ext_http;
	return pAddr;
}


int CppngrokHandler::bind(int port, methods ngrokmethod) {
	switch (ngrokmethod) {
	case methods::ngrokhttp:
		//do shit
		break;
	case methods::ngrokhttps :
		//do shit
		break;
	case methods::ngroktcp:
		//do shit
		break;
	case methods::ngroktls:
		//do shit
		break;
	}
	return 0;
}


int CppngrokHandler::logger(std::string message, int log_level, bool log_handler) {
	printf("[%d]", log_handler);
	if (log_handler == false) {
		return 0;
	}
	switch (log_level) {
	case 1:
		cout << "[NOTE] " << message << endl;
		break;
	case 2:
		cout << "[WARNING] " << message << endl;
		break;
	case 3:
		cout << "[ERROR] " << message << endl;
		break;
	case 4:
		cout << "[CRITICAL] " << message << endl;
		break;
	case 5:
		cout << "[DEBUG] " << message << endl;
		break;
	case 0:
		break;
	}
	return 0;
}




CppngrokHandler::CppngrokHandler(bool log_opt) {
	log_handler = log_opt;
	char *buff = { std::getenv("HOME") };
	strncat(buff, "/.local/bin/ngrok", 17);
	path = buff;
	cout << "NGROK PATH :: " << path << endl;;
	cout << "BUFFER :: " << buff << endl;
	if (FILE *file = fopen(buff, "rb")) {
		fclose(file);
	}
	else {
		if (std::getenv("NGROK_PATH")) {
			buff = std::getenv("NGROK_PATH");
		}
		else {
			CppngrokHandler::logger("PLEASE SET NGROK PATH TO ENV 'NGROK_PATH' AND TRY AGAIN", 3, log_handler);
		}
	}
}


