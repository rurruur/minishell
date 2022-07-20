## test cases
---
### 1. echo (x / leak : ?)
- echo $?
- echo ??
- echo ?
- echo $??
- echo $USERname
- echo $USER name
- echo “$USER na”me
- echo ‘$USER na’me
- > echo “$$USER”
	- bash 결과 : 13037USER
	- minishell 결과 : jrimR
- echo hi$USER
- echo hi”$USER”
- echo $USEEER
- echo ?$USER
- echo hell”o”" “from ” 42"
- echo “$USER ?”
- echo -nnnnn 도 echo -n과 같다...
- echo -nnnnn -n -nn hello
- > echo "\\\\"
	- bash : \\
	- minishell : ( ༎ຶД༎ຶ): quote is not closed
---
### 2. ls (✓ / leak : OK)
- ls
- l"s"
- ls -l
- ls -al
---
### 3. < 기본? (✓ / leak : OK)
- ( infile이 없는 경우 / infile이 있는 경우 모두 해보기 )
- < infile cat
- < infile cat | grep a
- < infile cat | grep a | wc
- < infile cat | grep a | wc -l
- cat < infile
---
### 4. export / unset (✓ / leak : OK)
- export a=b b=c c=d
- export a=aa b=cc
- export A=B B=C
- unset a
- unset b c A B
- *exportO=o
- *exportO+=o
- export a="ls -al"
---
### 5. export + echo (✓ / leak : OK)
- export TEST=abc
- echo test \ test
	- escape는 quote 앞에 있는 경우를 제외하고는 일반 문자로 처리됨
- echo “test
	- 닫히지 않은 quote는 에러로 처리
- echo $TEST
- echo “$TEST”
- echo ‘$TEST’”
- echo “$TEST$TEST$TEST”
- echo “$TEST$TEST=lol$TEST”
- echo ” $TEST lol $TEST”
- echo $TEST$TEST$TEST
- echo $TEST$TEST=lol$TEST”“lol
- echo $TEST lol $TEST
- echo test “” test “” test
---
### 6. pwd / cd (x / leak : ?)
- pwd
- cd ~
- cd
- > cd -
	- bash : /Users/jrim
	- minishell : ( ༎ຶД༎ຶ): cd: -: No such file or directory (후에 종료됨)
- echo $OLDPWD
- > 없는 경로로 갔을 때 cd가 종료됨...
- > 현재 위치하고 있는 디렉토리를 지워버린 경우
	- 잘 되는 것 같은데 다시 확인해보기
---
### 7. 경로까지 있는 명령어 (x / leak : ?)
- /bin/ls
- /bin/ls -l
- /bin/echo
---
### signal (✓ / leak : -)
- ctrl + D
- ctrl + C
- ctrl + \
---
### 반환값 테스트 (아직 안함)
- ./minishell
- quit 113
- echo $?
- wrongcmd
- echo $?
- ls
- echo $?