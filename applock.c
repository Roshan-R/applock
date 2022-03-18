#include "proc.h"

int main(int argc, char **argv)
{
	struct Config *c = (struct Config *)malloc(sizeof(struct Config));
	read_config_file(c);
	setup_proc_events(c);
	return 0;
}
