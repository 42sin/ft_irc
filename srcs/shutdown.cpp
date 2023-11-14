#include "../inc/shutdown.hpp"

bool online = true;

void shutdown(int sig) {
	(void)sig;
	online = false;
}