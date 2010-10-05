#!/usr/bin/perl

#how to use: place this in the same directory as 'winequality-both-hilo.arff' type "perl maketest.pl [attribute numbers other than 13]"

if (@ARGV==0) 
{
	die("please enter the file to parse");
}

if (@ARGV==1) 
{
	die("please enter the number of attributes to keep");
}

open(ORIGARFF, $ARGV[0]) || die("can't open main arff file");

shift(@ARGV);

undef %attri_keep;
for(@ARGV)
{
	$attri_keep{$_}=1;
}

$start=0;
$mode=0;
$attricount=0;
$ind=0;
foreach $line (<ORIGARFF>) {

        #Revise the header
        if ($start==0){
                chomp($line);
                @firstline=split(/\./,$line);
                $firstline[@firstline-1]=~ s/[1-9]+//;
                $newline=join(".",@firstline);
                $num=@ARGV+1;
                print ("$newline$num\n\n");
                $start=$start+1;
        }


	#get attribute set
	if ($line=~/\@attribute/) {
		$mode=1;
		$attricount=$attricount+1;
		if (($attri_keep{$attricount})||($attricount==13)) {
			print ("$line");
			$keeper[$ind]=$attricount;
			$ind++;
		}
	}
	elsif ($mode==1){
		print ("$line");
		if ($line eq "\@data\n") {
			$mode=2;
			next;
		}
	}

	#keep data
	if($mode==2){
		@dataset=split(/,/,$line);
		$I=0;
		for(@keeper){
			$newdata[$I]=$dataset[$_-1];
			$I++;
		}
		$newline=join(",",@newdata);
		print ("$newline");
	}
}
close(ORIGARFF);
