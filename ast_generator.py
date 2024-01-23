import sys
import ast


def main():
    code = str()
    with open(sys.argv[1], 'r') as f:
        code = f.read()
    parser = ast.parse(code)

    with open(sys.argv[2], 'w') as f:
        f.write(ast.dump(parser, indent=4))



if __name__ == '__main__':
    main()