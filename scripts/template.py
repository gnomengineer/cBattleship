"""helper functions for templating and I/O for the generate-* scripts in this folder"""

import pystache
import os

def read_template(filepath, variables):
    """read a template file and insert variables"""
    handle = open(filepath, "r")
    contents = handle.read()
    handle.close()
    rendered = pystache.render(contents, variables)
    return rendered


def write_template(filepath, string):
    """write a template file. string is already evaluated"""
    handle = open(filepath, "w")
    handle.write(string)
    handle.close()


def eval_template(file_src, file_dst, variables):
    """copy a template file to an other location while inserting variables"""
    print "create file", file_dst, "from template", file_src, "..."
    write_template(file_dst, read_template(file_src, variables))

def change_to_source_dir():
    """change the current working directory to the location of the project"""
    abspath = os.path.abspath(__file__)
    dname = os.path.dirname(abspath)
    dname = os.path.dirname(dname)
    os.chdir(dname)
