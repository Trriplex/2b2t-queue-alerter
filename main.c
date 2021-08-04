#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <curl/curl.h>

// Simple delay function, thx stackoverflow
void wait(int secs) {
	unsigned int retTime = time(0) + secs;
	while (time(0) < retTime);
}

// store the http response and send a notification if the number of ppl in the queue is under 200
void store_res(char* res) {
	char* token = strtok(res, ",");
	token = strtok(NULL, ",");
	token[strlen(token) - 2] = '\0';
	if (atoi(token) < 200) {
		system("notify-send \"GO ON 2B2T.ORG NOOOOW !!\"");
	}
}

// Needed by cb()
struct memory {
	char* response;
	size_t size;
};

// A callback function used by the curl request. Found int the libcurl doc
static size_t cb(void *data, size_t size, size_t nmemb, void *userp) {
	// Get the real size of the data and init the memory
	size_t realsize = size * nmemb;
	struct memory *mem = (struct memory*)userp;

	// Adds the new data to the response
	char* ptr = realloc(mem->response, mem->size + realsize + 1);
	if (ptr == NULL) {
		return 0;
	}

	// Store the response into the memory response, update the size, call store_res() and reset the memory
	mem->response = ptr;
	memcpy(&(mem->response[mem->size]), data, realsize);
	mem->size += realsize;
	store_res(mem->response);
	mem->response[mem->size] = 0;

	return realsize;
}

// The memory where the response will be stored
struct memory chunk = {0};

int main(void) {
	while (1) {
		CURL* curl;
		CURLcode res;

		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, "https://www.2b2t.io/api/queue?last=true");
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
		}
		// Clean the chunk struct
		memset(&chunk, 0, sizeof(chunk));
		// Wait 2 minutes
		wait(120);
	}
	return 0;
}
