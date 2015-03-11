import pystache
import os

def read_template(file, vars):
    f = open(file, "r")
    contents = f.read()
    f.close()
    rendered = pystache.render(contents, vars)
    return rendered


def write_template(file, string):
    f = open(file, "w")
    f.write(string)
    f.close()


def eval_template(file_src, file_dst, vars):
    print "create file", file_dst, "from template", file_src, "..."
    write_template(file_dst, read_template(file_src, vars))

def change_to_source_dir():
    abspath = os.path.abspath(__file__)
    dname = os.path.dirname(abspath)
    dname = os.path.dirname(dname)
    os.chdir(dname)
