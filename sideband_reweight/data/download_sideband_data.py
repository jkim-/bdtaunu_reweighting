#! /usr/bin/env python

import sys
import os
import subprocess
import time
import tempfile

def instantiate_tempfile(in_fname, s):
    temp = tempfile.NamedTemporaryFile()
    with open(in_fname, 'r') as r:
        for line in r:
            temp.write(line.format(s))
    temp.flush()
    return temp


if __name__ == '__main__':
    
    import argparse 
    parser = argparse.ArgumentParser(
            description='Download sideband data.')
    parser.add_argument('--onpeak', action='store_true',
                        help='Download on peak side band. ')
    parser.add_argument('--offpeak', action='store_true',
                        help='Download off peak side band. ')
    parser.add_argument('--dbname', default='bdtaunuhad_lite',
                        help='Database name. ')
    parser.add_argument('--verbose', action='store_true',
                        help='Increase verbosity; mainly for debugging. ')

    args = parser.parse_args()

    if args.onpeak == args.offpeak:
        print " + No action taken. Please supply either --onpeak or --offpeak. "
        sys.exit(1)

    print "+ configurations: \n"
    print "  dbname = {0}".format(args.dbname)

    output_fname, mode_label = None, None
    sql_script_template = 'sql/download_sideband_data_template.sql'
    if args.onpeak:
        mode_label = 1
        output_fname = 'onpeak.csv'
        print "  sample type = onpeak"
        print
        sys.stdout.flush()
    else:
        mode_label = 0
        output_fname = 'offpeak.csv'
        print "  sample type = offpeak"
        print
        sys.stdout.flush()

    print "+ downloading data from database."
    sys.stdout.flush()

    temp = instantiate_tempfile(sql_script_template, output_fname)

    start = time.time()
    verbosity_flag = "-q"
    if args.verbose: 
        verbosity_flag = "-a"
    subprocess.check_call(["psql", 
                            verbosity_flag,
                            "-d", args.dbname, 
                            "-v", "mode_label={0}".format(mode_label),
                            "-f", temp.name])
    end = time.time()
    temp.close()

    print "  done. completed in {0} seconds. \n".format(round(end-start, 2))
    sys.stdout.flush()
