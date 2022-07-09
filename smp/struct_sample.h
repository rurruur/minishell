
// 	parser가 executor에게 주는 선물은 다음과 같습니다...
//	각 노드(token)는 |를 기준으로 나누어져있습니다.
typedef struct s_toklst
{
	t_token			*cmd;		//	cmd와 뒤에 오는 str들
	t_token			*infile;	//	< : infile name
	t_token			*outfile;	//	> : outfile name
	t_token			*here_doc;	//	<< : here_doc에 들어가는 str들
	t_token			*append;	//	>> : append 되어야할 file name
	struct s_toklst	*next;
} 					t_toklst;

typedef struct s_token
{
	char			*str;
	struct s_token	*next;
} 					t_token;

/* example input

< test1 < test2 cmd1 -option < test3 | cmd2 "arg" > test3 >> test4 

1st node
	cmd 		: cmd1	->	-option	->	NULL
	infile 		: test1 ->	test2	->	test3	->	NULL
	outfile 	: NULL	
	here_doc	: NULL
	append		: NULL
	(next == 2nd node)

2nd node
	cmd 		: cmd2	->	arg		->	NULL
	infile 		: NULL
	outfile 	: test3	->	NULL
	here_doc	: NULL
	append		: test4	->	NULL
	(next == NULL)

*/

