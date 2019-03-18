#! /bin/tcsh -f
#


set VALUES             = (2.0 2.1 2.2 2.3 2.4 2.5 2.6 2.7 2.8 2.9 3.0)
set START         = $1
set LAST          = $2
set MATRIX        = $3
set CRITICALPROTO = $4

set INC   = 1

@ VALUE = $START
    while($VALUE <= $LAST)
	@ DEC = 0
	while($DEC < 10) 
	    set DECNUM = $VALUE.$DEC
	    echo $DECNUM
	    set OUTFILE = series.$DECNUM.out
            set REGIONSFILE = regions.$DECNUM.out
	    echo $OUTFILE

            subcommand.sh $MATRIX $DECNUM $CRITICALPROTO $OUTFILE $REGIONSFILE
	    @ DEC++
	end
	@ VALUE = $VALUE + $INC
    end
    echo $LAST.0




