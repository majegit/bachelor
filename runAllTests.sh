#! /bin/sh
if test -f Tests/testResults.txt; then
    rm Tests/testResults.txt
fi
cd Tests
find . -name "*.s" -type f -delete
find . -name "*.out" -type f -delete
cd ..

r=Tests/testResults.txt
touch $r
chmod 755 $r

./compile.sh Tests/parsingError.txt >> $r
./compile.sh Tests/allBranchesReturn2.txt >> $r
./compile.sh Tests/allBranchesReturn3.txt >> $r
./compile.sh Tests/variableScope2.txt >> $r
./compile.sh Tests/symbolCollectionError1.txt >> $r
./compile.sh Tests/symbolCollectionError2.txt >> $r
./compile.sh Tests/typeCheckingError.txt >> $r
./compile.sh Tests/operatorNotDefined.txt >> $r
./compile.sh Tests/expressionStatement2.txt >> $r

./compile.sh Tests/allBranchesReturn1.txt
./Tests/allBranchesReturn1.out >> $r

./compile.sh Tests/allBranchesReturn4.txt
./Tests/allBranchesReturn4.out >> $r

./compile.sh Tests/booleans.txt
./Tests/booleans.out >> $r

./compile.sh Tests/integers.txt
./Tests/integers.out >> $r

./compile.sh Tests/coercion.txt
./Tests/coercion.out >> $r

./compile.sh Tests/functionCall1.txt
./Tests/functionCall1.out >> $r

./compile.sh Tests/functionCall2.txt
./Tests/functionCall2.out >> $r

./compile.sh Tests/functionCall3.txt
./Tests/functionCall3.out >> $r

./compile.sh Tests/variableScope1.txt
./Tests/variableScope1.out >> $r

./compile.sh Tests/functionScope.txt
./Tests/functionScope.out >> $r

./compile.sh Tests/functionRedeclaration.txt
./Tests/functionRedeclaration.out >> $r

./compile.sh Tests/expressionStatement1.txt
./Tests/expressionStatement1.out >> $r

./compile.sh Tests/bigTest.txt
./Tests/bigTest.out >> $r

./compile.sh Tests/factorial.txt
./Tests/factorial.out >> $r


cd Tests
find . -name "*.s" -type f -delete
find . -name "*.out" -type f -delete
cd ..
