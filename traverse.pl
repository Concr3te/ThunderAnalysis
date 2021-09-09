use File::Find;

my @directories_to_search = ('.')

sub wanted {
   /^\.nfs.*\z/s &&
   (($dev, $ino, $mode, $nlink, $uid, $gid) = lstat($_)) &&
   int(-M _) > 7 &&
   unlink($_)
   ||
   ($nlink || (($dev, $ino, $mode, $nlink, $uid, $gid) = lstat($_))) &&
   $dev < 0 &&
   ($File::Find::prune = 1);
}

find(\&wanted, @directories_to_search);

#use File::Find;

finddepth(\&wanted, @directories_to_search);

#use File::Find;

find ({ wanted => \&process, follow => 1 }, '.');

