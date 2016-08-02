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
    parser.add_argument('--comb', action='store_true',
                        help='Download on peak side band. ')
    parser.add_argument('--dbname', default='bdtaunuhad_lite',
                        help='Database name. ')
    parser.add_argument('--verbose', action='store_true',
                        help='Increase verbosity; mainly for debugging. ')

    args = parser.parse_args()

    if not args.comb:
        print " + No action taken. Please supply --comb. "
        sys.exit(1)

    print "+ configurations: \n"
    print "  dbname = {0}".format(args.dbname)

    output_fname, sql_script_template = None, None
    if args.comb:
        sql_script_template = 'sql/download_sideband_comb.sql'
        output_fname = 'comb.csv'
        print "  sample type = comb"
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
                            "-f", temp.name])
    end = time.time()
    temp.close()

    print "  done. completed in {0} seconds. \n".format(round(end-start, 2))
    sys.stdout.flush()
