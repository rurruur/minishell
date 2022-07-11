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

### 주의할 것들
- "<<"랑 <<는 다르게 받아들여지나? : "<<"는 리다이렉션이 아니라 cmd
- "|"도 마찬가지, pipe로써의 역할을 수행하지 못한다.
	- cat Makefile "|" grep src 를 수행하면 cat Makefile 까지만을 수행한다.