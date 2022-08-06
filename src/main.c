// SPDX-License-Identifier: AGPL-3.0-only
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <inttypes.h>

#include <netlink/netlink.h>
#include <netlink/cache.h>
#include <netlink/route/link.h>

int getdata(char *interface)
{
	struct rtnl_link *link;
	struct nl_sock *socket;
	uint64_t bytes_in;
	uint64_t bytes_out;
	uint64_t bytes_in_last;
	uint64_t bytes_out_last;
	uint64_t rate_in;
	uint64_t rate_out;

	socket = nl_socket_alloc();
	nl_connect(socket, NETLINK_ROUTE);

	while (1) {
		if (rtnl_link_get_kernel(socket, 0, interface, &link) >= 0) {
			bytes_in = rtnl_link_get_stat(link, RTNL_LINK_RX_BYTES);
			bytes_out =
				rtnl_link_get_stat(link, RTNL_LINK_TX_BYTES);

			rate_in = bytes_in - bytes_in_last;
			rate_out = bytes_out - bytes_out_last;

			printf("bytes_in=%" PRIu64 ",bytes_out=%" PRIu64
			       ",rate_in=%" PRIu64 ",rate_out=%" PRIu64 "\n",
			       bytes_in, bytes_out, rate_in, rate_out);
			rtnl_link_put(link);

			bytes_in_last = bytes_in;
			bytes_out_last = bytes_out;

			sleep(1);
		}
	}

	nl_socket_free(socket);
}

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
