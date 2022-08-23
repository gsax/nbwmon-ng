// SPDX-License-Identifier: AGPL-3.0-only
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
/* #include <unistd.h> */
/* #include <inttypes.h> */

/* #include <netlink/netlink.h> */
/* #include <netlink/cache.h> */
/* #include <netlink/route/link.h> */

#include "getdata.h"

int main(int argc, char *argv[])
{
	int opt;
	char *interface;

	while ((opt = getopt(argc, argv, "i:")) != -1) {
		switch (opt) {
		case 'i':
			interface = optarg;
			break;
		}
	}

	printf("interface=%s\n", interface);
	getdata(interface);

	exit(EXIT_SUCCESS);
}
