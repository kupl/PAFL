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
    | matmul            @
    | starstar          **
    | slashslash        //
    | slashslashequal   //=
    | colonequal        :=
    | tilde             ~
    | in                in
    | is                is
"""


class ASTIterator:

    def __init__(self):
        self.tree = {"module": list()}
        self.tree_ref = self.tree["module"]


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
                tokens.append(self.toTokenFromOpAug(node.op, node.value.lineno))
                self.visitExpr(node.value, tokens)
                self.makeObject('STMT', tokens)

            case ast.AnnAssign:
                tokens = []
                self.visitExpr(node.target, tokens)
                #self.visitExpr(node.annotation, tokens)
                self.visitExpr(node.value, tokens)
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
                tokens = [['match', 'match', node.lineno]]
                self.visitExpr(node.subject, tokens)
                obj = self.makeObject('BRANCH', tokens)

                temp = self.tree_ref
                self.tree_ref = obj['then'] = list()
                self.resolveCase(node.cases)
                self.tree_ref = temp
                obj['else'] = list()
                    
            case ast.Raise:
                tokens = [['throw', 'raise', node.lineno]]
                self.visitExpr(node.exc, tokens)
                if node.cause is not None:
                    tokens.append(['identifier', 'from', node.cause.lineno])
                self.visitExpr(node.cause, tokens)
                self.makeObject('STMT', tokens)

            case ast.Try:
                self.makeObject('STMT', [['identifier', 'try', node.lineno]])
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
                tokens = [['identifier', 'global', node.lineno]]
                for name in node.names:
                    tokens.append(['identifier', name, node.lineno])
                self.makeObject('STMT', tokens)

            case ast.Nonlocal:
                tokens = [['identifier', 'nonlocal', node.lineno]]
                for name in node.names:
                    tokens.append(['identifier', name, node.lineno])
                self.makeObject('STMT', tokens)

            case ast.Expr:
                tokens = list()
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
        
        match type(node):
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
                tokens.append(self.toTokenFromOp(node.op, node.right.lineno))
                self.visitExpr(node.right, tokens)

            case ast.UnaryOp:
                match node.op:
                    case ast.Invert:
                        tokens.append(['tilde', '~', node.op.lineno])
                    case ast.Not:
                        tokens.append(['exclaim', 'not', node.op.lineno])
                    case ast.UAdd:
                        tokens.append(['plus', '+', node.op.lineno])
                    case ast.USub:
                        tokens.append(['minus', '-', node.op.lineno])
                self.visitExpr(node.operand, tokens)

            case ast.Lambda:
                tokens.append(['identifier', 'lambda', node.lineno])
                self.visitArguments(node.args, tokens)
                self.visitExpr(node.body, tokens)

            case ast.IfExp:
                self.visitExpr(node.body, tokens)
                tokens.append(['if', 'if-exp', node.test.lineno])
                self.visitExpr(node.test, tokens)
                tokens.append(['else', 'else-exp', node.orelse.lineno])
                self.visitExpr(node.orelse, tokens)

            case ast.Dict:
                tokens.append(['identifier', 'dict', node.lineno])
                for key, value in zip(node.keys, node.values):
                    self.visitExpr(key, tokens)
                    self.visitExpr(value, tokens)

            case ast.Set:
                tokens.append(['identifier', 'set', node.lineno])
                for elt in node.elts:
                    self.visitExpr(elt, tokens)

            case ast.ListComp:
                tokens.append(['identifier', 'list-comp', node.lineno])
                self.visitExpr(node.elt, tokens)
                self.caseComp(node.elt.end_lineno, node.generators, tokens)

            case ast.SetComp:
                tokens.append(['identifier', 'set-comp', node.lineno])
                self.visitExpr(node.elt, tokens)
                self.caseComp(node.elt.end_lineno, node.generators, tokens)

            case ast.DictComp:
                tokens.append(['identifier', 'dict-comp', node.lineno])
                self.visitExpr(node.key, tokens)
                self.visitExpr(node.value, tokens)
                self.caseComp(node.value.end_lineno, node.generators, tokens)

            case ast.GeneratorExp:
                self.visitExpr(node.elt, tokens)
                self.caseComp(node.elt.end_lineno, node.generators, tokens)

            case ast.Await:
                tokens.append(['identifier', 'await', node.lineno])
                self.visitExpr(node.value, tokens)

            case ast.Yield:
                tokens.append(['identifier', 'yield', node.lineno])
                self.visitExpr(node.value, tokens)

            case ast.YieldFrom:
                tokens.append(['identifier', 'yield', node.lineno])
                tokens.append(['identifier', 'from', node.lineno])
                self.visitExpr(node.value, tokens)

            case ast.Compare:
                self.visitExpr(node.left, tokens)
                for op, comparator in zip(node.ops, node.comparators):
                    tokens += self.toTokensFromCmpop(op, comparator.lineno)
                    self.visitExpr(comparator, tokens)

            case ast.Call:
                self.visitExpr(node.func, tokens)
                for arg in node.args:
                    self.visitExpr(arg, tokens)
                for keyword in node.keywords:
                    if keyword.arg is not None:
                        tokens.append(['identifier', keyword.arg, keyword.lineno])
                    self.visitExpr(keyword.value, tokens)
                    
            case ast.FormattedValue:
                self.visitExpr(node.value, tokens)

            case ast.JoinedStr:
                for value in node.values:
                    self.visitExpr(value, tokens)

            case ast.Constant:
                pass

            case ast.Attribute:
                self.visitExpr(node.value, tokens)
                tokens.append(['identifier', node.attr, node.end_lineno])

            case ast.Subscript:
                self.visitExpr(node.value, tokens)
                self.visitExpr(node.slice, tokens)

            case ast.Starred:
                tokens.append(['identifier', 'starred', node.lineno])
                self.visitExpr(node.value, tokens)

            case ast.Name:
                tokens.append(['identifier', node.id, node.lineno])

            case ast.List:
                tokens.append(['identifier', 'list', node.lineno])
                for elt in node.elts:
                    self.visitExpr(elt, tokens)

            case ast.Tuple:
                tokens.append(['identifier', 'tuple', node.lineno])
                for elt in node.elts:
                    self.visitExpr(elt, tokens)

            case ast.Slice:
                self.visitExpr(node.lower, tokens)
                self.visitExpr(node.upper, tokens)
                self.visitExpr(node.step, tokens)

            case ast.Expr:
                self.visitExpr(node.value, tokens)



    def visitPattern(self, pattern: ast.pattern, tokens: list[list[str | int]]):
        if pattern is None:
            return

        match type(pattern):
            case ast.MatchValue:
                self.visitExpr(pattern.value, tokens)
                
            case ast.MatchSingleton:
                pass

            case ast.MatchSequence:
                for p in pattern.patterns:
                    self.visitPattern(p, tokens)

            case ast.MatchMapping:
                for key, p in zip(pattern.keys, pattern.patterns):
                    self.visitExpr(key, tokens)
                    self.visitPattern(p, tokens)

            case ast.MatchClass:
                self.visitExpr(pattern.cls, tokens)
                for p in pattern.patterns:
                    self.visitPattern(p, tokens)
                for attr, p in zip(pattern.kwd_attrs, pattern.kwd_patterns):
                    tokens.append(['identifier', attr, p.lineno])
                    self.visitPattern(p, tokens)

            case ast.MatchStar:
                self.visitExpr(pattern.name, tokens)

            case ast.MatchAs:
                self.visitPattern(pattern.pattern, tokens)
                if pattern.name is None:
                    if pattern.pattern is None:
                        tokens.append(['identifier', '_', pattern.end_lineno])
                else:
                    tokens.append(['identifier', pattern.name, pattern.end_lineno])
                
            case ast.MatchOr:
                for p in pattern.patterns[:-1]:
                    self.visitPattern(p, tokens)
                    tokens.append('pipe', '|', p.end_lineno)
                self.visitPattern(pattern.patterns[-1], tokens)



    def visitArguments(self, args: ast.arguments, tokens: list[list[str | int]]):
        for parg in args.posonlyargs:
            tokens.append(['identifier', parg.arg, parg.lineno])
        for arg in args.args:
            tokens.append(['identifier', arg.arg, arg.lineno])
        if args.vararg is not None:
            tokens.append(['identifier', args.vararg.arg, args.vararg.lineno])
        for kwonlyarg in args.kwonlyargs:
            tokens.append(['identifier', kwonlyarg.arg, kwonlyarg.lineno])
        if args.kwarg is not None:
            tokens.append(['identifier', args.kwarg.arg, args.kwarg.lineno])


    
    def makeObject(self, type: str, tokens: list[list[str | int]]):
        obj = {'type': type, 'toks': tokens}
        self.tree_ref.append(obj)
        return obj


    def caseDef(self, node: ast.stmt, tokens: list[list[str | int]]):
        for deco in node.decorator_list:
            deco_tokens = list()
            self.visitExpr(deco, deco_tokens)
            self.makeObject('STMT', deco_tokens)

        self.visitArguments(node.args, tokens)
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


    def caseComp(self, lineno: int, generators: list[ast.comprehension], tokens: list[list[str | int]]):
        for comp in generators:
            if comp.is_async:
                tokens.append(['identifier', 'async', lineno])
            tokens.append(['for', 'for-comp', lineno])
            self.visitExpr(comp.target, tokens)
            self.visitExpr(comp.iter, tokens)
            lineno = comp.iter.end_lineno
            for ifex in comp.ifs:
                tokens.append(['if', 'if-comp', ifex.lineno])
                self.visitExpr(ifex, tokens)
                lineno = ifex.end_lineno


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
                tokens = [['case', 'case', match_case.pattern.lineno]]
                self.visitPattern(match_case.pattern, tokens)
                self.visitExpr(match_case.guard, tokens)
                obj = self.makeObject('BRANCH', tokens)
                self.resolveThen(obj, match_case.body)

                temp = self.tree_ref
                self.tree_ref = obj['else'] = list()
                self.resolveCase(tail)
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


    def toTokenFromOp(self, op: ast.operator, lineno: int) -> list[str | int]:
        match type(op):
            case ast.Add:
                return ['plus', '+', lineno]
            case ast.Sub:
                return ['minus', '-', lineno]
            case ast.Mult:
                return ['star', '*', lineno]
            case ast.MatMult:
                return ['matmul', '@', lineno]
            case ast.Div:
                return ['slash', '/', lineno]
            case ast.Mod:
                return ['percent', '%', lineno]
            case ast.Pow:
                return ['starstar', '**', lineno]
            case ast.LShift:
                return ['lessless', '<<', lineno]
            case ast.RShift:
                return ['greatergreater', '>>', lineno]
            case ast.BitOr:
                return ['pipe', '|', lineno]
            case ast.BitXor:
                return ['caret', '^', lineno]
            case ast.BitAnd:
                return ['amp', '&', lineno]
            case ast.FloorDiv:
                return ['slashslash', '//', lineno]
            

    def toTokenFromOpAug(self, op: ast.operator, lineno: int):
        token = self.toTokenFromOp(op, lineno)
        return [token[0] + 'equal', token[1] + '=', lineno]
    

    def toTokensFromCmpop(self, cmpop: ast.cmpop, lineno: int) -> list[list[str | int]]:
        match type(cmpop):
            case ast.Eq:
                return [['equalequal', '==', lineno]]
            case ast.NotEq:
                return [['exclaimequal', '!=', lineno]]
            case ast.Lt:
                return [['less', '<', lineno]]
            case ast.LtE:
                return [['lessequal', '<=', lineno]]
            case ast.Gt:
                return [['greater', '>', lineno]]
            case ast.GtE:
                return [['greaterequal', '>=', lineno]]
            case ast.Is:
                return [['is', 'is', lineno]]
            case ast.IsNot:
                return [['is', 'is', lineno], ['exclaim', 'not', lineno]]
            case ast.In:
                return [['in', 'in', lineno]]
            case ast.NotIn:
                return [['exclaim', 'not', lineno], ['in', 'in', lineno]]


#
#
# main
#
#
def main():
    code = str()
    with open(sys.argv[1], 'r') as f:
        code = f.read()

    iter = ASTIterator()
    iter.visit(ast.parse(code))
    with open(sys.argv[2], 'w') as f:
        f.write(json.dumps(iter.tree))


if __name__ == '__main__':
    main()
    