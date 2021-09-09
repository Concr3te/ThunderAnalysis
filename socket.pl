use IO::Socket::IP;

my $sock = IO::Socket::IP->new(
	PeerHost => "www.google.com",
	PeerPort => "http",
	Type => SOCK_STREAM,
) or die "Cannot construct socket = $@";

my $familyname = ($sock->sockdomain == PF_INET6 ) ? "IPv6" :
                 ($sock->sockdomain == PF_INET  ) ? "IPv4" :
		                                    "unknown";
printf "Connected to google via %s\n", $familyname;

