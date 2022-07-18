### 환경변수
1. 환경변수 이름 규칙
	- a~z, A~Z, _, 0~9 로 구성되어있다.
	- 단, 숫자로 시작할 수 없다.

### echo
- echo	$SHELL		:	/bin/zsh
- echo	"$SHELL"	:	/bin/zsh
- echo	'$SHELL'	:	$SHELL
- echo	$"SHELL"	:	SHELL
- echo	$'SHELL'	:	SHELL
---
- echo	$SHELL***	: 	/bin/zsh
- echo	$SHELL"***"	:	/bin/zsh\*\*\*
- echo	$SHELLeee	:	
- echo	$SHELL"eee"	:	/bin/zsheee
---
- echo	eee$SHELL	:	eee/bin/zsh
- echo	"eee"$SHELL	:	eee/bin/zsh
- echo	eee"$SHELL"	:	eee/bin/zsh
---

### cd
cd 는 인자가 여러개 들어와도 맨 앞 하나의 인자만 사용
- cd		:	$HOME으로 이동
- cd	~	:	$HOME으로 이동
---
- cd	\$	:	bash: cd: $: No such file or directory
- cd	$어쩌구
	1. 하나의 환경변수만 단독으로 있는 경우
		1. 해당 환경변수가 존재 할 때
			- value가 특정 경로일 때	: 거기로 이동
			- value가 경로가 아닐 때	: 당연히 이동 못함
		2. 해당 환경변수가 존재하지 않을 때	: $HOME으로 이동
	2. 환경변수에 뭐가 붙어있거나, 환경변수 여러개가 붙어있는 경우
		- 전부 한덩이로 묶어서 판단한다.