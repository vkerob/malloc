#include "../../includes/malloc.h"

pthread_mutex_t lock;

void initialize_mutex()
{
	if (data == NULL)
	{
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&lock, &attr);
		pthread_mutexattr_destroy(&attr);
	}
}