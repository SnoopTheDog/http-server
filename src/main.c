#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>

#define PORT 8888

int print_out_key (void *cls, enum MHD_ValueKind kind, 
                   const char *key, const char *value)
{
  printf ("%s: %s\n", key, value);
  return MHD_YES;
}

int earthqake_record (int time)
{
	return 0;
}

int answer_to_connection (void *cls, struct MHD_Connection *connection,
                          const char *url,
                          const char *method, const char *version,
                          const char *upload_data,
                          size_t *upload_data_size, void **con_cls)
{
	printf ("\nNew %s request for %s using version %s\n", method, url, version);

	if (strcmp(method, "/potresi/rekordi/tedenski"))
		earthqake_record(240);

	const char* page = "<html><body style='background-color=#121212;'>Hello</body></html>";

	MHD_get_connection_values (connection, MHD_HEADER_KIND, &print_out_key, NULL);

	return MHD_YES;
}



int main (void)
{
	struct MHD_Daemon* daemon;

	daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL,
		NULL, &answer_to_connection, NULL, MHD_OPTION_END);

	if (NULL == daemon) return 1;

	printf(" localhost:8888\nEnter to close...");
	getchar();

	MHD_stop_daemon(daemon);

	return 0;
}