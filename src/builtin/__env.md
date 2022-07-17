### echo
- echo	$SHELL		:	/bin/zsh
- echo	"$SHELL"	:	/bin/zsh
- echo	'$SHELL'	:	$SHELL
- echo	$"SHELL"	:	SHELL
- echo	$'SHELL'	:	SHELL
---
- echo	$SHELL***	: 	/bin/zsh			->	근데 이것까지 처리해야하나?
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