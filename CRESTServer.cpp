// Dependencies
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "HttpMessageHandler.h"
#include "fossa.h"
#include "Globals.h"
#include <sstream>

// Configuration properties
#define CREST2_VERSION "v0.3.0"
#define POLL_TIME_IN_MILLIS 17	// the pcars physics engine runs with 600Hz = 1.67ms interval
#define ESC_KEY 27
#define CREST_API_URL "/crest2/v1/api"

// Constants
#define HTTP_RESPONSE_404 "{\r\n  \"status\": \"404 Not found, please use the correct URL: " CREST_API_URL "\"\r\n}"

// Server variables
static const char *s_http_port_default = "8180";
static struct ns_serve_http_opts s_http_server_opts;

// Variables for integrity checks, definition in Globals.h
SharedMemory* localCopy;
SharedMemory* localCopyTmp;
unsigned int updateIndex;
unsigned int indexChange;
// Debug Mode
bool debug = false;

// Response generator
static HttpMessageHandler httpMessageHandler = HttpMessageHandler();

// Server request handler method
static void ev_handler(struct ns_connection *nc, int ev, void *ev_data) {
	struct http_message *hm = (struct http_message *) ev_data;

	switch (ev) {
	case NS_HTTP_REQUEST:
		// Only handle HTTP requests on the API url
		if (ns_vcmp(&hm->uri, CREST_API_URL) == 0) {
			httpMessageHandler.handle(nc, hm);
		}else{
			// Unknown URI, return a 404
			ns_printf(nc, "HTTP/1.1 404 Not found\r\n"
				"Content-Type: application/json\r\n"
				"Cache-Control: no-cache\r\n"
                "Access-Control-Allow-Origin: *\r\n"
				"Content-Length: %d\r\n\r\n%s",
				(int)strlen(HTTP_RESPONSE_404), HTTP_RESPONSE_404);
		}
		break;
	default:
		break;
	}
}

int main()	{

	// Handling of command line arguments
	LPWSTR* szArgList;
	int argCount;
	int port = -1;
	int PollInt = -1;
	bool help = false;
	
	szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount);

	for (int i = 1; i < argCount; i++)
	{
		//printf("%d: %ws\n", i, szArgList[i]);
		if (i + 1 != argCount)
		{
			if (wcscmp(szArgList[i], L"-p") == 0 )
			{
				port = _wtoi(szArgList[i + 1]);
				//printf("\nPort: %i\n",port);
				
			}
			else if (wcscmp(szArgList[i], L"-i") == 0)
			{
				PollInt = _wtoi(szArgList[i + 1]);
				//printf("\nPollInt: %i\n", PollInt);
			}	
		}
		if (wcscmp(szArgList[i], L"-d") == 0)
		{
			debug = true;
			//printf("\nDebug: %d\n", debug);
		}
		if (wcscmp(szArgList[i], L"-h") == 0)
		{
			help = true;
			//printf("\nDebug: %d\n", debug);
		}
	}

	LocalFree(szArgList);

	if (help) {
		printf("# CREST2 - CARS2 REST API %s\n", CREST2_VERSION);
		printf("# (c) 2015 Lars Rosenquist\n");
		printf("#          updated by Viper\n\n");
		printf("Usage:\n");
		printf("CREST2.exe [-p 8180] [-i 17] [-d] [-h]\n");
		printf("  -p	Change TCP Port, default: 8180, allowed: 1025-65534\n");
		printf("  -i	Change Memory Polling Interval im ms, default: 17, allowed: 2-999\n");
		printf("  -d	Debug Mode, show some more info for Integrity Checks\n");
		printf("  -h	Help\n");
	}
	else {

		//convert port from int to char*
		std::string s = std::to_string(port);
		static const char* s_http_port;// = s.c_str();

		// set HTTP Port
		if (port >= 1025 && port <= 65534) {
			s_http_port = s.c_str();
		}
		else {
			s_http_port = s_http_port_default;
		}

		// set poll interval
		if (PollInt < 2 || PollInt > 999) {
			PollInt = POLL_TIME_IN_MILLIS;
		}



		// Setup the server
		struct ns_mgr mgr;
		struct ns_connection* nc;
		ns_mgr_init(&mgr, NULL);
		nc = ns_bind(&mgr, s_http_port, ev_handler);
		ns_set_protocol_http_websocket(nc);
		s_http_server_opts.document_root = ".";

		localCopy = new SharedMemory;
		localCopyTmp = new SharedMemory;
		updateIndex = 0;
		indexChange = 0;

		// Print some information on the console
		printf("# CREST2 - CARS2 REST API %s\n", CREST2_VERSION);
		printf("# (c) 2015 Lars Rosenquist\n");
		printf("#          updated by Viper\n\n");
		printf("# Server started on TCP port: %s\n", s_http_port);
		printf("# Memory Polling Interval: %i ms\n", PollInt);
		if (debug) { printf("# Debug Mode\n"); }
		printf("# API is available at http://localhost:%s%s \n", s_http_port, CREST_API_URL);
		printf("# Press ESC to terminate\n");

		// Keep polling until ESC is hit
		while (true) {

			ns_mgr_poll(&mgr, PollInt);

			if (_kbhit() && _getch() == ESC_KEY) {
				break;
			}
		}

		// We're done, free up the server and exit
		ns_mgr_free(&mgr);
		delete localCopy;
		delete localCopyTmp;
	} 

	return 0;
}
