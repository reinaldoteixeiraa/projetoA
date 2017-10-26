.globl main

.data 
	msg_1: .asciiz "informe a quantidade de discos: " 
	msg_2: .asciiz  " Disco 1 da torre   "
	msg_3: .asciiz " Disco " 
	msg_4: .asciiz "para torre"
	
	
	#int discos
	discos: .word 0
	
.text
 
 j main 

hanoi: 
	#condicao se o valor informado for igual a 1

    addi $t0, $a0, 0		# temp save $a0
    addi $t1, $zero, 1
    bne $a0, $t1, else
    
    li $v0, 4			# printf("msg_3 Disco 1 da torre %d para a torre %d\n",orig,dest);
    la $a0, msg_2
    syscall
    
    li $v0, 1 			
    move $a0, $a1
    syscall
    
    li $v0, 4			# para 
    la $a0, msg_4
    syscall
    
    li $v0, 1 			
    move $a0, $a2
    syscall
    
    addi $a0, $t0, 0		
    jr $ra
    
else:
    #criando espaco na pilha
    addi $sp, $sp, -20
    
    #salvando na pilha
    sw $ra, 16($sp)		#store ra
    sw $a3, 12($sp)		#store a3
    sw $a2, 8($sp)		#store a2
    sw $a1, 4($sp)		#store a1
    sw $a0, 0($sp)		#store a0
	    
    #hanoi(n-1,orig,aux,dest);    
    	
    addi $t3, $a3, 0		#copia a3 em temporario 
    addi $a3, $a2, 0		#aux = dest
    addi $a2, $t3, 0		#dest = aux
    addi $a0, $a0, -1		#disco -1 		
    	
    	#chama a funcao hanoi
    jal hanoi  
    	
    #carrega pilha
    lw $ra, 16($sp)
    lw $a3, 12($sp)		#load a3
    lw $a2, 8($sp)		#load a2
    lw $a1, 4($sp)		#load a1
    lw $a0, 0($sp)		#load a0
   
    
    #move o disco da origem para o destino
    addi $t0, $a0, 0		# salva a0 em temporario 
    addi $t1, $zero, 1
    li $v0, 4			
    la $a0, msg_3
    syscall
    li $v0, 1 			
    move $a0, $a1
    syscall
    li $v0, 4			
    la $a0, msg_4
    syscall
    li $v0, 1 			
    move $a0, $a2
    syscall
    addi $a0, $t0, 0		# restaura $a0
    
    
    	#hanoi(n-1,aux,dest,orig);
    addi $t3, $a3, 0		#copia a3 para temporario
    addi $a3, $a1, 0		#aux = orig
    addi $a1, $t3, 0		#orig = aux
    addi $a0, $a0, -1		#discos -1 	
    
    		
    	#chama a funcao hanoi
    jal hanoi  
    	#carrega parametros da pilha
    lw $ra, 16($sp)
    		
    #limpa a pilha
    addi $sp, $sp, 20

    #return
    add $v0, $zero, $t5
    jr $ra    
	
main:
	
	#printf("informe a quantidade de discos: ");
	la	$a0,msg_1		#carrega o endereco da msg para syscall 
	li	$v0,4			# print_string é system call 4
	syscall
	
	#scanf("%d", &discos);
	li $v0, 5			# read_int é system call 5
	syscall				
	add $a0, $v0, $zero 			#salva o inteiro em a0
	
	addi $a1, $zero, 1		#salva a primeira torre em $a1
  	addi $a2, $zero, 3		#salva a terceira torre em $a2
    	addi $a3, $zero, 2		#salva a torre auxiliar em $a3
	
	#chama a funcao hanoi
	jal hanoi 
	
	
