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

/**
 * test input1
 * ls >> outfile > outfile2
 * outfile 내용 그대로 있고 outfile2에 새로(다 지우고) 출력
 */

/**
 * test intpu2
 * ls > outfile >> outfile2
 * outfile 지우고 새로 생성(내용 삭제)
 * outfile2: 내용 그대로 + 덧붙임
 */

/**
 * 결론: >는 지우고 새로 생성한다. >>는 내용 그대로 두고 덧붙인다.
 * => stdout redirection의 open 옵션에서 O_TRUNC 지우면 될듯
 * 마지막에 오는 > or >> 파일로 STDOUT 설정
 */