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
- cd		:
- cd	$	:
- cd	~	: