### parsing
1. check_quote : line 1
	- 먼저 닫히지 않은 따옴표가 있는지 확인한다.
	- 있다면 더 이상 진행하지 않고 error + 새로운 prompt
2. split_tok :  line 2
	- line을 " <>|"라는 네 개의 delimiter를 기준으로 쪼개어준다.
	- 이때, redirection 문자 혹은 문자열을 만나면 해당 문자(열)을 pretok에 새롭게 추가해준다.
	- quote에 묶여있는 녀석들은 한 덩어리 취급하는데,
	- "hello "world' !' 같은 녀석들은 hello world !로 들어가야한다. 이에대한 처리는 뒤의 trim_pretok에서 처리하게 된다.
3. trim_pretok : pretok 1-2
	- 앞에서 말했듯이 "hello "world' !' 같은 녀석들은 hello world !로 들어갈 수 있도록 처리해주는 단계가 포함된다.
	- "leave this 'quote'" -> leave this 'quote'
	- nakkim\'s_minishell -> nakkim's_minishell
	- "escape still left here\'" -> escape still left here\' 
4. check_pretok : pretok 3-4
	- redirection error : '><' 이런거 안됨
	- pipe error : '| cmd'이런거 안됨
5. tok_to_lst : pretok 5
	- pipe를 만나거나 pretok list의 끝을 만날 때까지 toklst로 pretok에 있는 노드들을 옮겨주는 과정
6. add_to_toklst


---
### 주의할 것들
- "<<"랑 <<는 다르게 받아들여지나? : "<<"는 리다이렉션이 아니라 cmd
- "|"도 마찬가지, pipe로써의 역할을 수행하지 못한다.
	- cat Makefile "|" grep src 를 수행하면 cat Makefile 까지만을 수행한다.

---
## errors

### 1. pipe
- 1-2번은 parser에서 처리되는 에러 -> executor로 안넘어감
	1. | 단독으로 있는 경우나 '| 명령어'
		> bash: syntax error near unexpected token `|'
	2. '명령어 |'
		- 원래는 뒤에 올 내용을 새로 입력받아야하는데 잇몸쉘에서는 에러로 처리
		- 1의 경우랑 같은 에러 출력하는 방식으로 구현해놨어요.
	3. '좋은 명령어 | 멋진 명령어'	: 정상작동
	4. 'ls | asdf'
		- bash: asdf: command not found
	5. 'asdf | ls'
		- asdf는 에러메세지 뜨고 ls는 잘 작동됨
	6. 파이프 두 개일 때는 뭐... 

### 2. redirection
리다이렉션 기호를 기준으로 항상 오른쪽에 파일이 오고 왼쪽에 명령어가 온다는 사실 기억하기
1. 뒤에 인자가 와야하는데 오지 않은 경우
	- 'echo hello >' 같은 거
	> bash: syntax error near unexpected token `newline'
	- '> asdf'는 asdf가 만들어짐! 놀라워!
2. 중간에 인자가 안오고 리다이렉션 기호만 막 있는 경우
	- 'cat Makefile > <<' 같은거
	> bash: syntax error near unexpected token `<<'
	- 뒤에 아무리 많은 리다이렉션 기호들이 붙어도 인자가 없는 리다이렉션 기호 중 가장 앞에 있는 녀석의 바로 뒤가 들어간다.
		- 즉 'cat Makefile > << < >' 이렇게 있어도 에러 메서지는 위와 동일
- '<>'
	> bash: syntax error near unexpected token `newline'
- '< >'
	> bash: syntax error near unexpected token `>' 
- 'cat << A >> >> aaaa.txt'

### 3. quote
- 우리의 잇몸쉘은 닫히지 않은 quote는 거부한다.
	> minishell: quote is not closed 
### 4. memory allocation
- 널가드에 걸린 경우
	> minishell : cannot allocate memory