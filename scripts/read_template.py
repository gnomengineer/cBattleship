
def read_template(file, vars):
    f = open(file, "r")
    contents = f.read()
    f.close()
    for var, value in vars.items():
        contents = contents.replace("@" + var + "@", value)

    return contents

