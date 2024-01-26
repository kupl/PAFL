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
            "type": 'BRANCH'                // CLASS | FUNC | BRANCH | STMT
            "toks": [
                ["if", "if", 12],           // [ type, name, line ]
                ["identifier", "x", 12],
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
    | identifier        async
    | identifier        with
    | identifier        from
    | identifier        import

    | matmul            @
    | starstar          **
    | slashslash        //
    | slashslashequal   //=
    | colonequal        :=
    | tilde             ~
    | in                in
"""


class ASTIterator:

    def __init__(self):
        self.tree = list()
        self.tree_ref = self.tree


    def visit(self, node: ast.Module):
        for stmt in node.body:
            self.visitStmt(stmt)


    """
    Tree: list[stmt]
    stmt:   -toks: list[token]
            -then: list[stmt]
            -else: list[stmt]
    """
    def visitStmt(self, node: ast.stmt):
        match type(node):

            case ast.FunctionDef:
                self.caseDef(node, [['identifier', node.name, node.lineno]])

            case ast.AsyncFunctionDef:
                self.caseDef(node, [['identifier', 'async', node.lineno], ['identifier', node.name, node.lineno]])

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
                self.caseFor(node, [['identifier', 'async', node.lineno], ['for', 'for', node.lineno]])

            case ast.While:
                self.caseIf(node, [['while', 'while', node.lineno]])

            case ast.If:
                self.caseIf(node, [['if', 'if', node.lineno]])

            case ast.With:
                self.caseWith(node, [['identifier', 'with', node.lineno]])

            case ast.AsyncWith:
                self.caseWith(node, [['identifier', 'async', node.lineno], ['with', 'with', node.lineno]])

            case ast.Match:
                node = ast.Match()
                tokens = [['match', 'match', node.lineno]]
                self.visitExpr(node.subject, tokens)
                obj = self.makeObject('BRANCH', tokens)

                temp = self.tree_ref
                self.tree_ref = obj['then'] = list()
                self.resolveCase(node.cases)
                self.tree_ref = temp
                    
            case ast.Raise:
                tokens = [['throw', 'raise', node.lineno]]
                self.visitExpr(node.exc, tokens)
                if node.cause is not None:
                    tokens.append(['identifier', 'from', node.cause.lineno])
                self.visitExpr(node.cause, tokens)
                self.makeObject('STMT', tokens)

            case ast.Try:
                self.resolveStmtList(node.body, self.tree_ref)
                self.resolveHandlers(node.handlers, node.orelse)
                self.resolveStmtList(node.finalbody, self.tree_ref)

            #case ast.TryStar:
            #    pass
                
            case ast.Assert:
                tokens = [['identifier', 'assert', node.lineno]]
                self.visitExpr(node.test, tokens)
                self.visitExpr(node.msg, tokens)
                self.makeObject('STMT', tokens)

            case ast.Import:
                self.caseImport(node, [['identifier', 'import', node.lineno]])

            case ast.ImportFrom:
                tokens = [] if node.module is None else [['identifier', 'from', node.lineno], ['identifier', node.module, node.lineno]]
                tokens.append(['identifier', 'import', node.lineno])
                self.caseImport(node, tokens)

            case ast.Global:
                tokens = ['identifier', 'global', node.lineno]
                for name in node.names:
                    tokens.append(['identifier', name, node.lineno])
                self.makeObject('STMT', tokens)

            case ast.Nonlocal:
                tokens = ['identifier', 'nonlocal', node.lineno]
                for name in node.names:
                    tokens.append(['identifier', name, node.lineno])
                self.makeObject('STMT', tokens)

            case ast.Expr:
                tokens = []
                self.visitExpr(node, tokens)
                self.makeObject('STMT', tokens)

            case ast.Pass:
                self.makeObject('STMT', [['identifier', 'pass', node.lineno]])
            case ast.Break:
                self.makeObject('STMT', [['break', 'break', node.lineno]])
            case ast.Continue:
                self.makeObject('STMT', [['continue', 'continue', node.lineno]])



    """
    visitExpr(expr) -> list[token]
    """
    def visitExpr(self, node: ast.expr, tokens: list[list[str | int]]):
        if node is None:
            return
        
        match node:
            case ast.BoolOp:
                self.visitExpr(node.values[0], tokens)
                op_type = 'ampamp' if node.op is ast.And else 'pipepipe'
                op_name = 'and' if node.op is ast.And else 'or'
                for value in node.values[1:]:
                    tokens.append([op_type, op_name, value.lineno])
                    self.visitExpr(value, tokens)
                
            case ast.NamedExpr:
                self.visitExpr(node.target, tokens)
                tokens.append(['colonequal', ':=', node.target.lineno])
                self.visitExpr(node.value, tokens)

            case ast.BinOp:
                self.visitExpr(node.left, tokens)
                tokens.append(self.toTokenFromOp(node.op))
                self.visitExpr(node.right, tokens)

            case ast.UnaryOp:
                match node.op:
                    case ast.Invert:
                        tokens.append(['tilde', '~', node.op.lineno])
                    case ast.Not:
                        tokens.append(['exclaim', 'not', node.op.lineno])
                    case ast.UAdd:
                        tokens.append(['tilde', '~', node.op.lineno])
                    case ast.USub:
                        tokens.append(['tilde', '~', node.op.lineno])
                self.visitExpr(node.operand, tokens)

            case ast.Lambda:
                pass
            case ast.IfExp:
                pass
            case ast.Dict:
                pass
            case ast.Set:
                pass
            case ast.ListComp:
                pass
            case ast.SetComp:
                pass
            case ast.DictComp:
                pass
            case ast.GeneratorExp:
                pass
            case ast.Await:
                pass
            case ast.Yield:
                pass
            case ast.YieldFrom:
                pass
            case ast.Compare:
                pass
            case ast.Call:
                pass
            case ast.FormattedValue:
                pass
            case ast.JoinedStr:
                pass
            case ast.Constant:
                pass
            case ast.Attribute:
                pass
            case ast.Subscript:
                pass
            case ast.Starred:
                pass
            case ast.Name:
                pass
            case ast.List:
                pass
            case ast.Tuple:
                pass
            case ast.slice:
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


    def caseImport(self, node: ast.stmt, tokens: list[list[str | int]]):
        tokens = [['identifier', 'import', node.lineno]]
        for name in node.names:
            tokens.append(['identifier', name.name, name.lineno])
            if name.asname is not None:
                tokens.append(['identifier', name.asname, name.lineno])
        self.makeObject('STMT', tokens)


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


    def resolveCase(self, cases: list[ast.match_case]):
        match cases:
            case []:
                pass
            
            case [match_case, *tail]:
                tokens = [['case', 'case', match_case.lineno]]
                self.visitPattern(match_case.pattern, tokens)
                self.visitExpr(match_case.guard, tokens)
                obj = self.makeObject('BRANCH', tokens)
                self.resolveThen(obj, match_case.body)

                temp = self.tree_ref
                self.tree_ref = obj['else'] = list()
                self.resolveCase(*tail)
                self.tree_ref = temp


    def resolveHandlers(self, handlers: list[ast.excepthandler], orelse: list[ast.stmt]):
        match handlers:
            case []:
                if len(orelse) > 0:
                    self.resolveStmtList(orelse, self.tree_ref)

            case [handler, *tail]:
                tokens = [['catch', 'except', handler.lineno]]
                self.visitExpr(handler.type, tokens)
                if handler.name is not None:
                    tokens.append(['identifier', handler.name, handler.lineno])
                obj = self.makeObject('BRANCH', tokens)
                self.resolveThen(obj, handler.body)

                temp = self.tree_ref
                self.tree_ref = obj['else'] = list()
                self.resolveHandlers(tail, orelse)
                self.tree_ref = temp


    def toTokenFromOp(self, op: ast.operator) -> list[str | int]:
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
    

    def visitPattern(self, pattern: ast.pattern, tokens: list[list[str | int]]):
        match pattern:
            case ast.MatchValue:
                self.visitExpr(pattern.value, tokens)
                
            case ast.MatchSingleton:
                pass

            case ast.MatchSequence:
                for p in pattern.patterns:
                    self.visitPattern(p, tokens)

            case ast.MatchMapping:
                for i in range(len(pattern.keys)):
                    self.visitExpr(pattern.keys[i], tokens)
                    self.visitPattern(pattern.patterns[i], tokens)

            case ast.MatchClass:
                pass
            case ast.MatchStar:
                pass
            case ast.MatchAs:
                pass
            case ast.MatchOr:
                pass



#
#
# main
#
#
def main():
    code = """
try:
    pass
except E as e:
    pass
except EE:
    pass
else:
    pass
finally:
    pass
"""
    print(ast.dump(ast.parse('x or y or z'), indent=4))
    return 

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