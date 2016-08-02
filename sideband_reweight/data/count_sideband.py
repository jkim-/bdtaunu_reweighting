#! /usr/bin/env python

import sys
import os
import subprocess
import time
import tempfile

if __name__ == '__main__':
    
    import argparse 
    parser = argparse.ArgumentParser(
            description='Download sideband data.')
    parser.add_argument('--data', action='store_true',
                        help='Download on peak side band. ')
    parser.add_argument('--mc', action='store_true',
                        help='Download off peak side band. ')
    parser.add_argument('--dbname', default='bdtaunuhad_lite',
                        help='Database name. ')
    parser.add_argument('--verbose', action='store_true',
                        help='Increase verbosity; mainly for debugging. ')

    args = parser.parse_args()

    if args.data == args.mc:
        print " + No action taken. Please supply either --data or --mc. "
        sys.exit(1)

    print "+ configurations: \n"
    print "  dbname = {0}".format(args.dbname)

    sql_script = None
    if args.data:
        sql_script = 'sql/count_sideband_data.sql'
        print "  sample type = data"
        print
        sys.stdout.flush()
    else:
        sql_script = 'sql/count_sideband_mc.sql'
        print "  sample type = mc"
        print
        sys.stdout.flush()

    print "+ computing."
    sys.stdout.flush()

    start = time.time()
    verbosity_flag = "-q"
    if args.verbose: 
        verbosity_flag = "-a"
    subprocess.check_call(["psql", 
                            verbosity_flag,
                            "-d", args.dbname, 
                            "-f", sql_script])
    end = time.time()

    print "  done. completed in {0} seconds. \n".format(round(end-start, 2))
    sys.stdout.flush()
