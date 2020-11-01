#!/usr/bin/perl

# CPU Watcher by Zach Stein
# This program writes the current CPU frequncy to a serial port.
# This code is licensed under the MIT license. (c) 2020.
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, 
# copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the 
# Software is furnished to do so, subject to the following conditions:
# the above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
# OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

use strict;
use Device::SerialPort;

#CONFIG:
my $device = '/dev/ttyACM1'; #serial device for the arduino
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
