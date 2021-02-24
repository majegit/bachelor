..\FlexBison\flex Scanner.l
..\FlexBison\bison -d -y Parser.y
..\FlexBison\flex Scanner.l
gcc y.tab.c lex.yy.c Tree.c main.c