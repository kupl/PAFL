import sys
import ast
import json


"""
{
    "module" = [
        
        // stmt
        {
            "type": "branch"        // branch | func | stmt
            "toks": [
                ["if", "if", 12],   // [ type, name, line ]
                ...
            ],
            "then": [
                stmt1,
                stmt2,
                ...
            ]
            "else": []
        },
        ...
    ]
}
"""


class ASTIterator(ast.NodeVisitor):

    def __init__(self):
        self.tree = list()
        self.tokens: list


    def visit(self, node: ast.Module):
        for stmt in node.body:
            self.visit_stmt(stmt)
            


    def visit_stmt(self, node: ast.stmt):
        match type(node):
            case ast.FunctionDef:
                node = ast.FunctionDef()
                self.tokens
                for arg in node.args.args:
                    arg.arg
            case ast.AsyncFunctionDef:
                pass
            case ast.ClassDef:
                pass
            case ast.Return:
                pass
            case ast.Delete:
                pass
            case ast.Assign:
                pass
            case ast.TypeAlias:
                pass
            case ast.AugAssign:
                pass
            case ast.AnnAssign:
                pass
            case ast.For:
                pass
            case ast.AsyncFor:
                pass
            case ast.While:
                pass
            case ast.If:
                pass
            case ast.With:
                pass
            case ast.AsyncWith:
                pass
            case ast.Match:
                pass
            case ast.Raise:
                pass
            case ast.Try:
                pass
            case ast.TryStar:
                pass
            case ast.Assert:
                pass
            case ast.Import:
                pass
            case ast.ImportFrom:
                pass
            case ast.Global:
                pass
            case ast.Nonlocal:
                pass
            case ast.Expr:
                pass
            case ast.Pass:
                pass
            case ast.Break:
                pass
            case ast.Continue:
                pass



    def visit_expr(self, node: ast.AST):
        pass



    def makeObject(self, type: str):
        return {"type": str, "toks": [], }



def main():
    code = """
if True:
    print('True')
elif True:
    print('True')
"""
    print(ast.dump(ast.parse(code), indent=4))
    return
    
    code = str()
    with open(sys.argv[1], 'r') as f:
        code = f.read()
    
    module = ast.parse(code, mode="exec")
    iter = ASTIterator()
    iter.visit(module)

    with open(sys.argv[2], 'w') as f:
        f.write(json.dump(iter.tree))

    tree = {'module': []}



if __name__ == '__main__':
    main()