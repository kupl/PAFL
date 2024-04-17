#
#   version = 3.10
#
import sys
import ast
import json


class ASTIterator:
    TokenID = int
    NodeID = int
    Token   = tuple[TokenID, str, int]  # (id, name, loc)
    Stmt    = list[Token]
    Branch  = tuple[Stmt, list["Node"], list["Node"]]   # (Stmt, Tree, Tree)
    Def     = tuple[Stmt, list["Node"]]                 # (Stmt, Tree)
    Node    = tuple[NodeID, Def | Branch | Stmt]
    Tree    = list[Node]

    RootID: TokenID = 0
    Nullptr: NodeID = 0


    def __init__(self):
        self.root = ASTIterator.Tree()
        self.tree_ref: ASTIterator.Tree = self.root
        self.token_id = ASTIterator.RootID
        self.node_id = ASTIterator.Nullptr


    def visit(self, stmt_list: list[ast.stmt], ref: Tree = None):
        snapshot = self.tree_ref
        if ref is not None:
            self.tree_ref = ref
        for stmt in stmt_list:
            self.visitStmt(stmt)
        self.tree_ref = snapshot


    def makeNode(self, node_type, stmt: Stmt):
        node = None
        self.node_id += 1
        if (node_type is ASTIterator.Stmt):
            node = (self.node_id, stmt)
        elif (node_type is ASTIterator.Branch):
            node = (self.node_id, (stmt, [], []))
        else: # node_type is Def
            node = (self.node_id, (stmt, []))
        self.tree_ref.append(node)
        return node
    

    def makeToken(self, name: str, loc: int) -> Token:
        self.token_id += 1
        return (self.token_id, name, loc)


    """
    visitStmt(ast.stmt)
    """
    def visitStmt(self, ast_stmt: ast.stmt):
        match type(ast_stmt):

            case ast.FunctionDef:
                self.caseDef(ast_stmt, [self.makeToken(ast_stmt.name, ast_stmt.lineno)])

            case ast.AsyncFunctionDef:
                self.caseDef(ast_stmt, [self.makeToken('async', ast_stmt.lineno), self.makeToken(ast_stmt.name, ast_stmt.lineno)])

            case ast.ClassDef:
                node = self.makeNode(ASTIterator.Def, [self.makeToken(ast_stmt.name, ast_stmt.lineno)])
                self.visit(ast_stmt.body, node[1][1])

            case ast.Return:
                stmt: ASTIterator.Stmt = [self.makeToken('return', ast_stmt.lineno)]
                self.visitExpr(ast_stmt.value, stmt)
                self.makeNode(ASTIterator.Stmt, stmt)

            case ast.Delete:
                stmt: ASTIterator.Stmt = [self.makeToken('del', ast_stmt.lineno)]
                for expr in ast_stmt.targets:
                    self.visitExpr(expr, stmt)
                self.makeNode(ASTIterator.Stmt, stmt)

            case ast.Assign:
                stmt: ASTIterator.Stmt = ASTIterator.Stmt()
                for expr in ast_stmt.targets:
                    self.visitExpr(expr, stmt)
                self.visitExpr(ast_stmt.value, stmt)
                self.makeNode(ASTIterator.Stmt, stmt)

            #case ast.TypeAlias:
            #    pass
                
            case ast.AugAssign:
                stmt: ASTIterator.Stmt = ASTIterator.Stmt()
                self.visitExpr(ast_stmt.target, stmt)
                stmt.append(self.toTokenFromOpAug(ast_stmt.op, ast_stmt.value.lineno))
                self.visitExpr(ast_stmt.value, stmt)
                self.makeNode(ASTIterator.Stmt, stmt)

            case ast.AnnAssign:
                stmt: ASTIterator.Stmt = ASTIterator.Stmt()
                self.visitExpr(ast_stmt.target, stmt)
                #self.visitExpr(ast_stmt.annotation, stmt)
                self.visitExpr(ast_stmt.value, stmt)
                self.makeNode(ASTIterator.Stmt, stmt)

            case ast.For:
                self.caseFor(ast_stmt, [self.makeToken('for', ast_stmt.lineno)])

            case ast.AsyncFor:
                self.caseFor(ast_stmt, [self.makeToken('async', ast_stmt.lineno), self.makeToken('for', ast_stmt.lineno)])

            case ast.While:
                self.caseIf(ast_stmt, [self.makeToken('while', ast_stmt.lineno)])

            case ast.If:
                self.caseIf(ast_stmt, [self.makeToken('if', ast_stmt.lineno)])

            case ast.With:
                self.caseWith(ast_stmt, [self.makeToken('with', ast_stmt.lineno)])

            case ast.AsyncWith:
                self.caseWith(ast_stmt, [self.makeToken('async', ast_stmt.lineno), self.makeToken('with', ast_stmt.lineno)])

            case ast.Match:
                stmt: ASTIterator.Stmt = [self.makeToken('match', ast_stmt.lineno)]
                self.visitExpr(ast_stmt.subject, stmt)
                node = self.makeNode(ASTIterator.Branch, stmt)
                # Match.body
                temp = self.tree_ref
                self.tree_ref = node[1][1]
                self.resolveCase(ast_stmt.cases)
                self.tree_ref = temp
                    
            case ast.Raise:
                stmt: ASTIterator.Stmt = [self.makeToken('raise', ast_stmt.lineno)]
                self.visitExpr(ast_stmt.exc, stmt)
                if ast_stmt.cause is not None:
                    stmt.append(self.makeToken('from', ast_stmt.cause.lineno))
                self.visitExpr(ast_stmt.cause, stmt)
                self.makeNode(ASTIterator.Stmt, stmt)

            case ast.Try:
                self.makeNode(ASTIterator.Stmt, [self.makeToken('try', ast_stmt.lineno)])
                self.visit(ast_stmt.body, self.tree_ref)
                self.resolveHandlers(ast_stmt.handlers, ast_stmt.orelse)
                self.visit(ast_stmt.finalbody, self.tree_ref)

            #case ast.TryStar:
            #    pass
                
            case ast.Assert:
                stmt: ASTIterator.Stmt = [self.makeToken('assert', ast_stmt.lineno)]
                self.visitExpr(ast_stmt.test, stmt)
                self.visitExpr(ast_stmt.msg, stmt)
                self.makeNode(ASTIterator.Stmt, stmt)

            case ast.Import:
                self.caseImport(ast_stmt, [self.makeToken('import', ast_stmt.lineno)])

            case ast.ImportFrom:
                stmt: ASTIterator.Stmt = ASTIterator.Stmt() if ast_stmt.module is None else [self.makeToken('from', ast_stmt.lineno), self.makeToken(ast_stmt.module, ast_stmt.lineno)]
                stmt.append(self.makeToken('import', ast_stmt.lineno))
                self.caseImport(ast_stmt, stmt)

            case ast.Global:
                stmt: ASTIterator.Stmt = [self.makeToken('global', ast_stmt.lineno)]
                for name in ast_stmt.names:
                    stmt.append(self.makeToken(name, ast_stmt.lineno))
                self.makeNode(ASTIterator.Stmt, stmt)

            case ast.Nonlocal:
                stmt: ASTIterator.Stmt = [self.makeToken('nonlocal', ast_stmt.lineno)]
                for name in ast_stmt.names:
                    stmt.append(self.makeToken(name, ast_stmt.lineno))
                self.makeNode(ASTIterator.Stmt, stmt)

            case ast.Expr:
                stmt: ASTIterator.Stmt = ASTIterator.Stmt()
                self.visitExpr(ast_stmt, stmt)
                self.makeNode(ASTIterator.Stmt, stmt)

            case ast.Pass:
                self.makeNode(ASTIterator.Stmt, [self.makeToken('pass', ast_stmt.lineno)])
            case ast.Break:
                self.makeNode(ASTIterator.Stmt, [self.makeToken('break', ast_stmt.lineno)])
            case ast.Continue:
                self.makeNode(ASTIterator.Stmt, [self.makeToken('continue', ast_stmt.lineno)])


    """
    visitExpr(expr) -> Stmt
    """
    def visitExpr(self, ast_expr: ast.expr, stmt: Stmt) -> Stmt:
        if ast_expr is None:
            return
        
        match type(ast_expr):
            case ast.BoolOp:
                self.visitExpr(ast_expr.values[0], stmt)
                op_name = 'and' if ast_expr.op is ast.And else 'or'
                for value in ast_expr.values[1:]:
                    stmt.append(self.makeToken(op_name, value.lineno))
                    self.visitExpr(value, stmt)
                
            case ast.NamedExpr:
                self.visitExpr(ast_expr.target, stmt)
                stmt.append(self.makeToken(':=', ast_expr.target.lineno))
                self.visitExpr(ast_expr.value, stmt)

            case ast.BinOp:
                self.visitExpr(ast_expr.left, stmt)
                stmt.append(self.toTokenFromOp(ast_expr.op, ast_expr.right.lineno))
                self.visitExpr(ast_expr.right, stmt)

            case ast.UnaryOp:
                match ast_expr.op:
                    case ast.Invert:
                        stmt.append(self.makeToken('~', ast_expr.op.lineno))
                    case ast.Not:
                        stmt.append(self.makeToken('not', ast_expr.op.lineno))
                    case ast.UAdd:
                        stmt.append(self.makeToken('+', ast_expr.op.lineno))
                    case ast.USub:
                        stmt.append(self.makeToken('-', ast_expr.op.lineno))
                self.visitExpr(ast_expr.operand, stmt)

            case ast.Lambda:
                stmt.append(self.makeToken('lambda', ast_expr.lineno))
                self.visitArguments(ast_expr.args, stmt)
                self.visitExpr(ast_expr.body, stmt)

            case ast.IfExp:
                self.visitExpr(ast_expr.body, stmt)
                stmt.append(self.makeToken('if-exp', ast_expr.test.lineno))
                self.visitExpr(ast_expr.test, stmt)
                stmt.append(self.makeToken('else-exp', ast_expr.orelse.lineno))
                self.visitExpr(ast_expr.orelse, stmt)

            case ast.Dict:
                stmt.append(self.makeToken('dict', ast_expr.lineno))
                for key, value in zip(ast_expr.keys, ast_expr.values):
                    self.visitExpr(key, stmt)
                    self.visitExpr(value, stmt)

            case ast.Set:
                stmt.append(self.makeToken('set', ast_expr.lineno))
                for elt in ast_expr.elts:
                    self.visitExpr(elt, stmt)

            case ast.ListComp:
                stmt.append(self.makeToken('list-comp', ast_expr.lineno))
                self.visitExpr(ast_expr.elt, stmt)
                self.caseComp(ast_expr.elt.end_lineno, ast_expr.generators, stmt)

            case ast.SetComp:
                stmt.append(self.makeToken('set-comp', ast_expr.lineno))
                self.visitExpr(ast_expr.elt, stmt)
                self.caseComp(ast_expr.elt.end_lineno, ast_expr.generators, stmt)

            case ast.DictComp:
                stmt.append(self.makeToken('dict-comp', ast_expr.lineno))
                self.visitExpr(ast_expr.key, stmt)
                self.visitExpr(ast_expr.value, stmt)
                self.caseComp(ast_expr.value.end_lineno, ast_expr.generators, stmt)

            case ast.GeneratorExp:
                self.visitExpr(ast_expr.elt, stmt)
                self.caseComp(ast_expr.elt.end_lineno, ast_expr.generators, stmt)

            case ast.Await:
                stmt.append(self.makeToken('await', ast_expr.lineno))
                self.visitExpr(ast_expr.value, stmt)

            case ast.Yield:
                stmt.append(self.makeToken('yield', ast_expr.lineno))
                self.visitExpr(ast_expr.value, stmt)

            case ast.YieldFrom:
                stmt.append(self.makeToken('yield', ast_expr.lineno))
                stmt.append(self.makeToken('from', ast_expr.lineno))
                self.visitExpr(ast_expr.value, stmt)

            case ast.Compare:
                self.visitExpr(ast_expr.left, stmt)
                for op, comparator in zip(ast_expr.ops, ast_expr.comparators):
                    stmt += self.toStmtFromCmpop(op, comparator.lineno)
                    self.visitExpr(comparator, stmt)

            case ast.Call:
                self.visitExpr(ast_expr.func, stmt)
                for arg in ast_expr.args:
                    self.visitExpr(arg, stmt)
                for keyword in ast_expr.keywords:
                    if keyword.arg is not None:
                        stmt.append(self.makeToken(keyword.arg, keyword.lineno))
                    self.visitExpr(keyword.value, stmt)
                    
            case ast.FormattedValue:
                self.visitExpr(ast_expr.value, stmt)

            case ast.JoinedStr:
                for value in ast_expr.values:
                    self.visitExpr(value, stmt)

            case ast.Constant:
                pass

            case ast.Attribute:
                self.visitExpr(ast_expr.value, stmt)
                stmt.append(self.makeToken(ast_expr.attr, ast_expr.end_lineno))

            case ast.Subscript:
                self.visitExpr(ast_expr.value, stmt)
                self.visitExpr(ast_expr.slice, stmt)

            case ast.Starred:
                stmt.append(self.makeToken('starred', ast_expr.lineno))
                self.visitExpr(ast_expr.value, stmt)

            case ast.Name:
                stmt.append(self.makeToken(ast_expr.id, ast_expr.lineno))

            case ast.List:
                stmt.append(self.makeToken('list', ast_expr.lineno))
                for elt in ast_expr.elts:
                    self.visitExpr(elt, stmt)

            case ast.Tuple:
                stmt.append(self.makeToken('tuple', ast_expr.lineno))
                for elt in ast_expr.elts:
                    self.visitExpr(elt, stmt)

            case ast.Slice:
                self.visitExpr(ast_expr.lower, stmt)
                self.visitExpr(ast_expr.upper, stmt)
                self.visitExpr(ast_expr.step, stmt)

            case ast.Expr:
                self.visitExpr(ast_expr.value, stmt)



    def visitPattern(self, pattern: ast.pattern, stmt: Stmt):
        if pattern is None:
            return

        match type(pattern):
            case ast.MatchValue:
                self.visitExpr(pattern.value, stmt)
                
            case ast.MatchSingleton:
                pass

            case ast.MatchSequence:
                for p in pattern.patterns:
                    self.visitPattern(p, stmt)

            case ast.MatchMapping:
                for key, p in zip(pattern.keys, pattern.patterns):
                    self.visitExpr(key, stmt)
                    self.visitPattern(p, stmt)

            case ast.MatchClass:
                self.visitExpr(pattern.cls, stmt)
                for p in pattern.patterns:
                    self.visitPattern(p, stmt)
                for attr, p in zip(pattern.kwd_attrs, pattern.kwd_patterns):
                    stmt.append(self.makeToken(attr, p.lineno))
                    self.visitPattern(p, stmt)

            case ast.MatchStar:
                self.visitExpr(pattern.name, stmt)

            case ast.MatchAs:
                self.visitPattern(pattern.pattern, stmt)
                if pattern.name is None:
                    if pattern.pattern is None:
                        stmt.append(self.makeToken('_', pattern.end_lineno))
                else:
                    stmt.append(self.makeToken(pattern.name, pattern.end_lineno))
                
            case ast.MatchOr:
                for p in pattern.patterns[:-1]:
                    self.visitPattern(p, stmt)
                    stmt.append(self.makeToken('|', p.end_lineno))
                self.visitPattern(pattern.patterns[-1], stmt)



    def visitArguments(self, args: ast.arguments, stmt: Stmt):
        for parg in args.posonlyargs:
            stmt.append(self.makeToken(parg.arg, parg.lineno))
        for arg in args.args:
            stmt.append(self.makeToken(arg.arg, arg.lineno))
        if args.vararg is not None:
            stmt.append(self.makeToken(args.vararg.arg, args.vararg.lineno))
        for kwonlyarg in args.kwonlyargs:
            stmt.append(self.makeToken(kwonlyarg.arg, kwonlyarg.lineno))
        if args.kwarg is not None:
            stmt.append(self.makeToken(args.kwarg.arg, args.kwarg.lineno))


    def caseDef(self, ast_stmt: ast.stmt, stmt: Stmt):
        for deco in ast_stmt.decorator_list:
            deco_stmt: ASTIterator.Stmt = ASTIterator.Stmt()
            self.visitExpr(deco, deco_stmt)
            self.makeNode(ASTIterator.Stmt, deco_stmt)
        self.visitArguments(ast_stmt.args, stmt)
        node = self.makeNode(ASTIterator.Def, stmt)
        self.visit(ast_stmt.body, node[1][1])

    
    def caseFor(self, ast_stmt: ast.stmt, stmt: Stmt):
        self.visitExpr(ast_stmt.target, stmt)
        self.visitExpr(ast_stmt.iter, stmt)
        node = self.makeNode(ASTIterator.Branch, stmt)
        self.visit(ast_stmt.body, node[1][1])
        self.visit(ast_stmt.orelse, node[1][2])


    def caseIf(self, ast_stmt: ast.stmt, stmt: Stmt):
        self.visitExpr(ast_stmt.test, stmt)
        node = self.makeNode(ASTIterator.Branch, stmt)
        self.visit(ast_stmt.body, node[1][1])
        self.visit(ast_stmt.orelse, node[1][2])


    def caseWith(self, ast_stmt: ast.stmt, stmt: Stmt):
        for item in ast_stmt.items:
            self.visitExpr(item.context_expr, stmt)
            self.visitExpr(item.optional_vars, stmt)
        self.makeNode(ASTIterator.Stmt, stmt)
        self.visit(ast_stmt.body)


    def caseImport(self, ast_stmt: ast.stmt, stmt: Stmt):
        stmt: ASTIterator.Stmt = [self.makeToken('import', ast_stmt.lineno)]
        for name in ast_stmt.names:
            stmt.append(self.makeToken(name.name, name.lineno))
            if name.asname is not None:
                stmt.append(self.makeToken(name.asname, name.lineno))
        self.makeNode(ASTIterator.Stmt, stmt)


    def caseComp(self, lineno: int, generators: list[ast.comprehension], stmt: Stmt):
        for comp in generators:
            if comp.is_async:
                stmt.append(self.makeToken('async', lineno))
            stmt.append(self.makeToken('for-comp', lineno))
            self.visitExpr(comp.target, stmt)
            self.visitExpr(comp.iter, stmt)
            lineno = comp.iter.end_lineno
            for ifex in comp.ifs:
                stmt.append(self.makeToken('if-comp', ifex.lineno))
                self.visitExpr(ifex, stmt)
                lineno = ifex.end_lineno


    def resolveCase(self, cases: list[ast.match_case]):
        match cases:
            case []:
                pass
            case [match_case, *tail]:
                stmt: ASTIterator.Stmt = [self.makeToken('case', match_case.pattern.lineno)]
                self.visitPattern(match_case.pattern, stmt)
                self.visitExpr(match_case.guard, stmt)
                node = self.makeNode(ASTIterator.Branch, stmt)
                # then
                self.visit(match_case.body, node[1][1])
                # orelse
                snapshot = self.tree_ref
                self.tree_ref = node[1][2]
                self.resolveCase(tail)
                self.tree_ref = snapshot


    def resolveHandlers(self, handlers: list[ast.excepthandler], orelse: list[ast.stmt]):
        match handlers:
            case []:
                if len(orelse) > 0:
                    self.visit(orelse, self.tree_ref)

            case [handler, *tail]:
                stmt: ASTIterator.Stmt = [self.makeToken('except', handler.lineno)]
                self.visitExpr(handler.type, stmt)
                if handler.name is not None:
                    stmt.append(self.makeToken(handler.name, handler.lineno))
                node = self.makeNode(ASTIterator.Branch, stmt)
                # then
                self.visit(handler.body, node[1][1])
                # orelse
                snapshot = self.tree_ref
                self.tree_ref = node[1][2]
                self.resolveCase(tail)
                self.tree_ref = snapshot


    def toTokenFromOp(self, op: ast.operator, lineno: int) -> Token:
        match type(op):
            case ast.Add:
                return self.makeToken('+', lineno)
            case ast.Sub:
                return self.makeToken('-', lineno)
            case ast.Mult:
                return self.makeToken('*', lineno)
            case ast.MatMult:
                return self.makeToken('@', lineno)
            case ast.Div:
                return self.makeToken('/', lineno)
            case ast.Mod:
                return self.makeToken('%', lineno)
            case ast.Pow:
                return self.makeToken('**', lineno)
            case ast.LShift:
                return self.makeToken('<<', lineno)
            case ast.RShift:
                return self.makeToken('>>', lineno)
            case ast.BitOr:
                return self.makeToken('|', lineno)
            case ast.BitXor:
                return self.makeToken('^', lineno)
            case ast.BitAnd:
                return self.makeToken('&', lineno)
            case ast.FloorDiv:
                return self.makeToken('//', lineno)
    

    def toTokenFromOpAug(self, op: ast.operator, lineno: int) -> Token:
        token = self.toTokenFromOp(op, lineno)
        return (token[0], token[1] + '=', token[2])
    

    def toStmtFromCmpop(self, cmpop: ast.cmpop, lineno: int) -> Stmt:
        match type(cmpop):
            case ast.Eq:
                return [self.makeToken('==', lineno)]
            case ast.NotEq:
                return [self.makeToken('!=', lineno)]
            case ast.Lt:
                return [self.makeToken('<', lineno)]
            case ast.LtE:
                return [self.makeToken('<=', lineno)]
            case ast.Gt:
                return [self.makeToken('>', lineno)]
            case ast.GtE:
                return [self.makeToken('>=', lineno)]
            case ast.Is:
                return [self.makeToken('is', lineno)]
            case ast.IsNot:
                return [self.makeToken('is', lineno), self.makeToken('not', lineno)]
            case ast.In:
                return [self.makeToken('in', lineno)]
            case ast.NotIn:
                return [self.makeToken('not', lineno), self.makeToken('in', lineno)]



#
# Transform AST to JSON format
#
class Converter:
    Token = tuple[ASTIterator.TokenID, str, ASTIterator.NodeID,\
                  ASTIterator.NodeID, ASTIterator.NodeID, ASTIterator.NodeID, ASTIterator.NodeID]
    Tokens = dict[str, int | list[Token]]
    Nodes = dict[str, int | list[ASTIterator.TokenID]]
    Json = dict[str, int | list[Tokens] | list[Nodes]]


    def __init__(self, tree: ASTIterator):
        self.tokens: list[Converter.Tokens] = []
        self.nodes: list[Converter.Nodes] = []
        self.json: Converter.Json = {"total_tokens": tree.token_id, "tokens": self.tokens, "total_nodes": -1, "nodes": self.nodes}
        
        self.root: ASTIterator.Tree = tree.root
        self.parent_id = ASTIterator.Nullptr
        self.pred_id = ASTIterator.Nullptr
        self.cur_lineno: int = 0
        self.cur_tokens: list[Converter.Token] = []

        self.child_node: list[ASTIterator.TokenID] | None = None
        self.node_id: ASTIterator.NodeID = tree.node_id


    def convert(self) -> Json:
        # Convert
        self._convert(self.root)
        self.json["total_nodes"] = self.node_id
        # Return
        return self.json


    def _convert(self, tree: ASTIterator.Tree):
        # Swap pred_id
        temp_pred: ASTIterator.NodeID = self.pred_id
        self.pred_id = ASTIterator.Nullptr

        # Iterate tree
        size = len(tree)
        for idx, (node_id, node) in enumerate(tree):
            if node_id == 127:
                pass
            match node:

            # Stmt
                case stmt if isinstance(node, list):
                    # New node
                    elems: list[ASTIterator.TokenID] = []
                    self.nodes.append({"id": node_id, "elems": elems})

                    for (token_id, token_name, token_loc) in stmt:
                        # New line
                        self._newLine(token_id, token_name, token_loc)
                        # Push token to node
                        elems.append(token_id)
                        if (self.child_node is not None):
                            self.child_node.append(token_id)
                        # New token
                        self.cur_tokens.append([token_id, token_name, node_id,
                                                self.parent_id, ASTIterator.Nullptr, self.pred_id,
                                                tree[idx + 1][0] if idx + 1 < size else ASTIterator.Nullptr])

            # Branch
                case (stmt, then, orelse):
                    # New node
                    elems: list[ASTIterator.TokenID] = []
                    self.nodes.append({"id": node_id, "elems": elems})

                    for (token_id, token_name, token_loc) in stmt:
                        # New line
                        self._newLine(token_id, token_name, token_loc)
                        # Push token to node
                        elems.append(token_id)
                        if (self.child_node is not None):
                            self.child_node.append(token_id)
                        # New token
                        self.cur_tokens.append([token_id, token_name, node_id,
                                                self.parent_id, ASTIterator.Nullptr, self.pred_id,
                                                tree[idx + 1][0] if idx + 1 < size else ASTIterator.Nullptr])
                        
                    # Move to then, orelse
                    # Snapshot
                    temp_child, temp_parent = self.child_node, self.parent_id
                    # New
                    (new_child_id, new_child_node), self.parent_id, self.pred_id = self._newChild(), node_id, ASTIterator.Nullptr
                    self.nodes.append({"id": new_child_id, "elems": new_child_node})
                    self.child_node = new_child_node
                    # ConvertW
                    self._convert(then)
                    self._convert(orelse)
                    # Load snapshot
                    self.child_node, self.parent_id = temp_child, temp_parent

            # Def
                case (stmt, body):
                    # New node
                    elems: list[ASTIterator.TokenID] = []
                    self.nodes.append({"id": node_id, "elems": elems})

                    for (token_id, token_name, token_loc) in stmt:
                        # New line
                        self._newLine(token_id, token_name, token_loc)
                        # Push token to node
                        elems.append(token_id)
                        if (self.child_node is not None):
                            self.child_node.append(token_id)
                        # New token
                        self.cur_tokens.append([token_id, token_name, node_id,
                                                self.parent_id, ASTIterator.Nullptr, self.pred_id,
                                                tree[idx + 1][0] if idx + 1 < size else ASTIterator.Nullptr])
                        
                    # Move to body
                    # Snapshot
                    temp_child, temp_parent = self.child_node, self.parent_id
                    # New
                    self.child_node, self.parent_id = None, ASTIterator.Nullptr
                    # Convert
                    self._convert(body)
                    # Load snapshot
                    self.child_node, self.parent_id = temp_child, temp_parent

            # End
            self.pred_id = node_id

        # Swap pred_id
        self.pred_id = temp_pred


    def _newLine(self, token_id: ASTIterator.TokenID, token_name: str, token_loc: int):
        if self.cur_lineno != token_loc:
            if len(self.cur_tokens) > 0:
                self.tokens.append({"lineno": self.cur_lineno, "tokens": self.cur_tokens.copy()})
                self.cur_tokens.clear()
            self.cur_lineno = token_loc


    def _newChild(self) -> tuple[ASTIterator.NodeID, list[ASTIterator.TokenID]]:
        self.node_id += 1
        return self.node_id, []



#
#   main
#
def main():

    code = str()
    with open(sys.argv[1], 'r') as f:
        code = f.read()

    iter = ASTIterator()
    iter.visit(ast.parse(code).body)
    with open(sys.argv[2], 'w') as f:
        f.write(json.dumps(Converter(iter).convert()))


if __name__ == '__main__':
    main()
    