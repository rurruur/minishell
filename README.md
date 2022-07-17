# minishell ( ´Д`)>

> _Summary: The objective of this project is for you to **create a simple shell**. Yes, your
little bash or zsh. You will learn a lot about processes and file descriptors._

- [Introduction](#introduction)
- [Mandatory part](#mandatory-part)
- [구현](#구현)
	- [prompt](#prompt)

## Introduction

The existence of shells is linked to the very existence of IT. At the time, all coders agreed
that communicating with a computer using aligned 1/0 switches was seriously
irritating. It was only logical that they came up with the idea to communicate with
a computer using interactive lines of commands in a language somewhat close
to english.
With Minishell, you’ll be able to travel through time and come back to problems
people faced when Windows didn’t exist.


## Mandatory part

1. 닫히지 않은 따옴표나 특정되지 않은 특수문자에 대해 해석하지 않는다.
2. global variable은 한 개보다 많이 사용할 수 없다.
3. 새로운 명령어를 입력할 수 있는 prompt를 보여줘야한다.
4. working history가 있어야한다.
5. `PATH` 변수나 상대/절대 경로를 활용해서 올바른 실행 파일을 찾아 실행할 수 있어야 한다.
6. `‘`는 일련의 문자열에 대한 해석을 금지한다.
7. `“`는 `$`를 제외한 모든 문자열에 대한 해석을 금지한다.
8. 다음의 기능을 실행할 수 있어야한다.
    - `echo -n`
    - 상대/절대 경로로만 사용하는 `cd`
    - 옵션이 없는 경우도 실행되어야한다. : `pwd`, `export`, `unset`, `env`, `exit`
9. redirection
    - `<` : redirecting input
    - `>` : redirecting output
    - `<<` : 현재 소스에서 delimiter를 포함한 줄을 만나기 전까지 입력값을 읽어들읻다. 
          (기록을 업데이트 할 필요는 없음)
    - `>>` : 출력을 추가 모드로 redirecting
10. `|` : 각 pipeline마다 명령어의 출력은 pipe로 연결되어 다음 명령어의 input이 된다.
11. environmental variables chould expand to their values
12. `$?` : expands to the exit status of the most recently executed foreground pipeline
13. `ctrl-C`, `ctrl-D`, `ctrl-\` 는 bash와 동일하게 동작해야한다.
    
    when interactive :
    
    - `ctrl-C` : new prompt
    - `ctrl-D` : exit the shell
    - `ctrl-\` : do nothing
14. 요구하지 않은 것까진 만들 필요는 없다는군
15. 의문점이 생긴다면 bash가 답이 되어줄겁니다.

## 구현

### 에러 체크 + 시그널 핸들링

1. 안 닫힌 따옴표
2. 

### prompt

readline을 사용해서 만들자

readline 헤더
	
	-L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include -lreadline

### lexer

토큰으로 나눈 후 체크
1. 명령어가 존재하는 거니?
2. 옵션도 존재?
3. 필요한 인자가 모두 있니?

### parser

1. 공백일 때 : (문자열 "" 내부에 있는 상황이 아니면) 그냥 넘어가기 (handler 불필요할 듯)
2. 문자일 때 : 일반적인 문자일 때는 buffer를 사용해서 특수문자 만날 때까지 붙여주세요
    - open quote 이후에 나오는 문자열에 대해서는 close quote를 만날 때까지는 일반 문자열로 간주해야겠지...?
    - quote를 제외한 다른 특수문자를 만났을 때는 그동안 buf에 저장해놓았던 문자열을 t_tok에 저장하고 종료 
3. quote일 때 : 앞에서 check_quote를 통해 quote들은 무조건 쌍을 이루고 있는 문자열만 넘어오게된다. close quote를 만날 때까지 단순하게 while문 돌려서 buf에 넣어주기
    - 단, 'escape + quote'인 상황이라도 그냥 buf에 담아줍시다!
4. <, >
    - &&랑 ||은 보너스
    - input은 마지막 거만 처리하면 되고, output은 없는 파일이 생성 되어야 하니까 모두 넘겨줘야함
5. bracket 처리 어떻게해 -> 보너스래 서브젝트 잘 읽자
    - 일반적으로 쌍을 이루고 있는 상황은 상관 없는데
    - ( only : 
    - ) only :

### executor

#### heredoc

1. < / << 같이 받음
2. heredoc 먼저 전부 처리 -> 임시 파일로 생성 후 fd 리턴(파일명어떻게?)
3. 처리 끝난 후 heredoc 임시 파일만 삭제(리스트 돌면서 타입 체크)