

	.global	cla_test_func
	.sect	"Cla1Prog:cla_test_func"
	.align	2
cla_test_func_sp	.usect	".scratchpad:Cla1Prog:cla_test_func",2,0,1

cla_test_func:
	MMOVI32 MR0, #0x00004001
	MNOP
	MMOVI32 MR1, #0x00004002
	MNOP

;;EOF
