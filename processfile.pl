use strict;
use warnings;

sub Analyze()
{
	my $text_file = 'file_text.txt';
	my $count = 0;

	open my $text_lines, $text_file or die "Could not open $text_file: $!";

	my @lines = <$text_lines>;

	foreach(@lines)
	{
		$count = $count + 1;
	}

	print($count);
	print("\n");
	
}

Analyze()
