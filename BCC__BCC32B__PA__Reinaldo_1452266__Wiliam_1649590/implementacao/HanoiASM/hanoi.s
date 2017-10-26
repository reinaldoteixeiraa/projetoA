.globl main

.data 
	msg_1: .asciiz "informe a quantidade de discos: " 
	msg_2: .asciiz "Move Disco 1 da torre %c para a torre %c\n"
	msg_3: .asciiz "Move Disco %d da torre %c para a torre %c\n" 
	
	a: .word 0x00000000
	b: .word 0x00000000
	c: .word 0x00000000
	
	#int discos
	discos: .word 0
	
.text
 
 j main 

hanoi: 
	



main:
	
	#printf("informe a quantidade de discos: ");
	la	$a0,msg_1		#carrega o endereco da msg para syscall 
	li	$v0,4			# print_string é system call 4
	syscall
	
	#scanf("%d", &discos);
	li $v0, 5			# read_int é system call 5
	syscall				
	sw $v0, discos 			#salva o inteiro em v0
	
	#chama a funcao hanoi
	jal hanoi 
	
	