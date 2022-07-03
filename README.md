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

LL? LR?...

### executor

실행함..
싱글 커맨드면 포크 안하고
멀티면 포크 해서 머 알아서잘..리다이렉션하던가..
끝나면 자료들 해제해라..