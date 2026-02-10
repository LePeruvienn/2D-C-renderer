#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "glad/glad.h"

int main(int argc, char** argv)
{
	if (create_window() != 0)
	{
		fprintf(stderr, "%s: Failed to create a windows.\n", argv[0]);
		exit(1);
	}

	while(keep_running)
	{
		update_window();
	}

	destroy_window();

	return 0;
}
