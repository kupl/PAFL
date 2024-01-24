#
# version = 3.10
#
import sys
import ast
import json


"""
{
    "module" = [
        
        // stmt
        {
            "type": "BRANCH"        // CLASS | FUNC | BRANCH | STMT
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

"""
unique python token type =
    | async             async
    | matmul            @
    | starstar          **
    | slashslash        //
    | slashslashequal   //=
    | with              with
    | from              from
    | in                in
"""


class ASTIterator:

    def __init__(self):
        self.tree = list()
        self.tree_ref = self.tree


    def visit(self, node: ast.Module):
        for stmt in node.body:
            self.visitStmt(stmt)



    def visitStmt(self, node: ast.stmt):
        match type(node):

            case ast.FunctionDef:
                self.caseDef(node, [['identifier', node.name, node.lineno]])

            case ast.AsyncFunctionDef:
                self.caseDef(node, [['async', 'async', node.lineno], ['identifier', node.name, node.lineno]])

            case ast.ClassDef:
                obj = self.makeObject('CLASS', [['identifier', node.name, node.lineno]])
                self.resolveThen(obj, node.body)

            case ast.Return:
                tokens = [['return', 'return', node.lineno]]
                self.visitExpr(node.value, tokens)
                self.makeObject('STMT', tokens)

            case ast.Delete:
                tokens = [['delete', 'del', node.lineno]]
                for expr in node.targets:
                    self.visitExpr(expr, tokens)
                self.makeObject('STMT', tokens)

            case ast.Assign:
                tokens = []
                for expr in node.targets:
                    self.visitExpr(expr, tokens)
                self.visitExpr(node.value, tokens)
                self.makeObject('STMT', tokens)

            #case ast.TypeAlias:
            #    pass
                
            case ast.AugAssign:
                tokens = []
                self.visitExpr(node.target, tokens)
                tokens.append(self.toTokenFromOpAug(node.op))
                self.visitExpr(node.vale, tokens)
                self.makeObject('STMT', tokens)

            case ast.AnnAssign:
                tokens = []
                self.visitExpr(node.target, tokens)
                self.visitExpr(node.annotation, tokens)
                tokens.append(self.toTokenFromOpAug(node.op))
                self.visitExpr(node.vale, tokens)
                self.makeObject('STMT', tokens)

            case ast.For:
                self.caseFor(node, [['for', 'for', node.lineno]])

            case ast.AsyncFor:
                self.caseFor(node, [['async', 'async', node.lineno], ['for', 'for', node.lineno]])

            case ast.While:
                self.caseIf(node, [['while', 'while', node.lineno]])

            case ast.If:
                self.caseIf(node, [['if', 'if', node.lineno]])

            case ast.With:
                self.caseWith(node, [['with', 'with', node.lineno]])

            case ast.AsyncWith:
                self.caseWith(node, [['async', 'async', node.lineno], ['with', 'with', node.lineno]])

            case ast.Match:
                node = ast.Match()
                tokens = [['match', 'match', node.lineno]]
                self.visitExpr(node.subject, tokens)
                for case in node.cases:
                    pass

            case ast.Raise:
                tokens = [['throw', 'raise', node.lineno]]
                self.visitExpr(node.exc, tokens)
                if node.cause is not None:
                    tokens.append(['from', 'from', node.cause.lineno])
                self.visitExpr(node.cause, tokens)

            case ast.Try:
                node = ast.Try()
                self.makeObject("BRANCH") [['try', 'try', node.lineno]]

            #case ast.TryStar:
            #    pass
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
                self.makeObject('STMT', [['pass', 'pass', node.lineno]])
            case ast.Break:
                self.makeObject('STMT', [['break', 'break', node.lineno]])
            case ast.Continue:
                self.makeObject('STMT', [['continue', 'continue', node.lineno]])



    def visitExpr(self, node: ast.expr, tokens: list[list[str | int]]):
        if node is None:
            return
        match node:
            case ast.BoolOp:
                pass


    
    def makeObject(self, type: str, tokens: list[list[str | int]]):
        obj = {'type': type, 'toks': tokens}
        self.tree_ref.append(obj)
        return obj


    def caseDef(self, node: ast.stmt, tokens: list[list[str | int]]):
        for arg in node.args.args:
            tokens.append(['identifier', arg.arg, arg.lineno])
        obj = self.makeObject('FUNC', tokens)
        self.resolveThen(obj, node.body)

    
    def caseFor(self, node: ast.stmt, tokens: list[list[str | int]]):
        self.visitExpr(node.target, tokens)
        self.visitExpr(node.iter, tokens)
        obj = self.makeObject('BRANCH', tokens)
        self.resolveThenElse(obj, node.body, node.orelse)


    def caseIf(self, node: ast.stmt, tokens: list[list[str | int]]):
        self.visitExpr(node.test, tokens)
        obj = self.makeObject('BRANCH', tokens)
        self.resolveThenElse(obj, node.body, node.orelse)


    def caseWith(self, node: ast.stmt, tokens: list[list[str | int]]):
        for item in node.items:
            self.visitExpr(item.context_expr, tokens)
            self.visitExpr(item.optional_vars, tokens)
        self.makeObject('STMT', tokens)
        self.resolveStmtList(node.body, self.tree_ref)


    def resolveStmtList(self, stmt_list: list[ast.stmt], ref: list):
        temp = self.tree_ref
        self.tree_ref = ref
        for stmt in stmt_list:
            self.visitStmt(stmt)
        self.tree_ref = temp


    def resolveThen(self, obj: dict, then: list[ast.stmt]):
        obj['then'] = list()
        self.resolveStmtList(then, obj['then'])


    def resolveThenElse(self, obj: dict, then: list[ast.stmt], orelse: list[ast.stmt]):
        self.resolveThen(obj, then)
        obj['else'] = list()
        self.resolveStmtList(orelse, obj['else'])
    

    def toTokenFromOp(self, op: ast.operator):
        match op:
            case ast.Add:
                return ['plus', '+', op.lineno]
            case ast.Sub:
                return ['minus', '-', op.lineno]
            case ast.Mult:
                return ['star', '*', op.lineno]
            case ast.MatMult:
                return ['matmul', '@', op.lineno]
            case ast.Div:
                return ['slash', '/', op.lineno]
            case ast.Mod:
                return ['percent', '%', op.lineno]
            case ast.Pow:
                return ['starstar', '**', op.lineno]
            case ast.LShift:
                return ['lessless', '<<', op.lineno]
            case ast.RShift:
                return ['greatergreater', '>>', op.lineno]
            case ast.BitOr:
                return ['pipe', '|', op.lineno]
            case ast.BitXor:
                return ['caret', '^', op.lineno]
            case ast.BitAnd:
                return ['amp', '&', op.lineno]
            case ast.FloorDiv:
                return ['slashslash', '//', op.lineno]
            

    def toTokenFromOpAug(self, op: ast.operator):
        token = self.toTokenFromOp(op)
        token[0] += 'equal'
        token[1] += '='
        return token






#
#
# main
#
#
def main():
    code = """if True:
    print('True')
elif True:
    print('True')
def foo(a, b):
    pass
"""
    iter = ASTIterator()
    iter.visit(ast.parse(code))
    print(json.dumps(iter.tree, indent=4))
    return

    print(ast.dump(ast.parse(code), indent=4, include_attributes=True))
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