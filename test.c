#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "cb.h"

void *read_and_print(void *vargp)
{

	clock_t last_update = clock();
	byte out;
	while(true)
	{
		if(read_buffer((circular_buffer*) vargp, &out) == OK_SIGNAL)
		{
			printf("%c", out);
			last_update = clock();
		}

		if(((clock() - last_update) * 1000 / CLOCKS_PER_SEC) > 1000)
			break;
	}
}

void *write(void *vargp)
{
	char str[] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!', '\n'};

	write_buffer((circular_buffer*) vargp, str, 14);
}

int main(int argc, char** argv)
{
	circular_buffer cb;
       	if(init_circular_buffer(512, &cb) != OK_SIGNAL)
		return ERROR_SIGNAL;

	pthread_t thread_id_read;
	pthread_create(&thread_id_read, NULL, read_and_print, (void*)&cb);

	pthread_t thread_id_write;
	for(int i = 0; i < 10; i++)
	{
		pthread_create(&thread_id_write, NULL, write, (void*)&cb);
		pthread_join(thread_id_write, NULL);
	}

	pthread_join(thread_id_read, NULL);

	return OK_SIGNAL;
}
