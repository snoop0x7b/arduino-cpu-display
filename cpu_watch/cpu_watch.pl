#!/usr/bin/perl

use strict;
use Device::SerialPort;

#CONFIG:
my $device = '/dev/ttyACM0'; #serial device for the arduino
my $poll_frequency = 2; #in seconds



my $port = Device::SerialPort->new($device);

$port->baudrate(9600); 
$port->databits(8);
$port->parity("none");

while(1) {
open(FH, '<', '/proc/cpuinfo') or die $!;
# Open up the CPU info file (Which contains the speed) and iterate it
	while(<FH>) {
		# Look for the right line
		if ($_ =~ /cpu MHz/) {
			my $mhz = $_;
			# Strip the extra crap from the line
			$mhz =~ s/cpu MHz\s+\:\s//;
			chomp($mhz);
			# Write the line to the serial port
			$port->write( sprintf('%.3fmhz', $mhz) );
			last;
		}	
	}
	close(FH);
	sleep($poll_frequency);
}
