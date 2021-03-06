#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "debug.h"

#define _GNU_SOURCE // necessário porque getline() é extensão GNU

// Campos do formato de instrução.
// opcode  := ir(31 downto 26)
// rs      := ir(25 downto 21);
// rt      := ir(20 downto 16);
// rd      := ir(15 downto 11);
// shamt   := ir(10 downto  6);
// imm     := ir(15 downto  0);
// address := ir(25 downto  0);

/* Definição das Máscaras. */
int mascaraOpCode     = 0xFC000000;
int mascaraRs         = 0x03E00000;
int mascaraRt         = 0x001F0000;
int mascaraRd         = 0x0000F800;
int mascaraShamt      = 0x000007C0;
int mascaraFunct      = 0x0000003F;
int mascaraImmediate  = 0x0000FFFF;
int mascaraAddress    = 0x03FFFFFF;

char *registerName[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2",
                       "$a3",   "$t0", "$t1", "$t2", "$t3", "$t4", "$t5",
                       "$t6",   "$t7", "$s0", "$s1", "$s2", "$s3", "$s4",
                       "$s5",   "$s6", "$s7", "$t8", "$t9", "$k0", "$k1",
                       "$gp",   "$sp", "$fp", "$ra"};

/* Função para imprimir um número 32 bits com binário.
   Adaptado de um código encontrado na internet.    */
void bin_prnt_byte(int x) {
  PRINT_FUNC_NAME;
  int i, n;
  TRACE("bin_prnt_byte begin x: %u\n");

  char buffer [50] = {0};
  
  for (i = 0; i < 32; i++) {
    if ((x & 0x80000000) != 0) {
      // printf("1");
      n = sprintf (buffer, "%s%s", buffer, "1");
    } else {
      // printf("0");
      n = sprintf (buffer, "%s%s", buffer, "0");
    }
    if ((i % 4 == 3) && i < 31) {
      // printf(" "); /* insert a space between nybbles */
      n = sprintf (buffer, "%s%s", buffer, " ");
    }
    x = x << 1;
  }
  TRACE("[%s]\n", buffer);
  TRACE("bin_prnt_byte end.\n");
}

/* Função que recupera o campo OpCode. */
unsigned int getOpCode(unsigned int ir) {
  PRINT_FUNC_NAME;
  unsigned int opcode = ((ir & mascaraOpCode) >> 26);
  TRACE("Opcode: %u\n ", opcode);
  return opcode;
}

/* Função que recupera o campo registrador Rs. */
unsigned int getRs(unsigned int ir) {
  PRINT_FUNC_NAME;
  unsigned int rs = (ir & mascaraRs) >> 21;
  TRACE("Rs: %u\n ", rs);
  return rs;
}

/* Função que recupera o campo registrador Rt. */
unsigned int getRt(unsigned int ir) {
  PRINT_FUNC_NAME;
  unsigned int rt = (ir & mascaraRt) >> 16;
  TRACE("Rt: %u\n ", rt);
  return rt;
}

/* Função que recupera o campo registrador Rd. */
unsigned int getRd(unsigned int ir) {
  PRINT_FUNC_NAME;
  unsigned int rd = (ir & mascaraRd) >> 11;
  TRACE("Rd: %u\n ", rd);
  return rd;
}

/* Função que recupera o campo Shamt (deslocamento). */
int getShamt(unsigned int ir) {
  PRINT_FUNC_NAME;
  unsigned int shamt = (ir & mascaraShamt) >> 6;
  TRACE("Shamt: %u\n ", shamt);
  return shamt;
}

/* Função que recupera o campo Funct. */
unsigned int getFunct(unsigned int ir) {
  PRINT_FUNC_NAME;
  unsigned int funct = (ir & mascaraFunct);
  TRACE("funct: %u\n ", funct);
  return funct;
}

/* Função que recupera o campo imm. */
int getImmediate(unsigned int ir) {
  PRINT_FUNC_NAME;
  unsigned int imm = (ir & mascaraImmediate);
  TRACE("imm: %u\n ", imm);
  return imm;
}

/* Função que recupera o campo Address. */
unsigned int getAddress(unsigned int ir) {
  PRINT_FUNC_NAME;
  unsigned int address = (ir & mascaraAddress);
  TRACE("address: %u\n ", address);
  return address; 
}

/* Converte um char * representando um binário, para inteiro. */
int intFromBinary(char *s) {
  PRINT_FUNC_NAME;
  int inteiro = (int) strtol(s, 0, 2);
  TRACE("valor inteiro %d - %X - %b\n", inteiro, inteiro, inteiro);
  bin_prnt_byte(inteiro);
  TRACE("\n");

  return inteiro;
}

/* Decodificação das instruções. */
void decodificar(unsigned int ir) {
  PRINT_FUNC_NAME;
  switch (getOpCode(ir)) {
    case 0: { // 000000, Aritmética.
      switch (getFunct(ir)) {
        case 32: { // 100000 -> add, R-Type.
          printf("add ");
          printf("%s, ", registerName[getRd(ir)]);
          printf("%s, ", registerName[getRs(ir)]);
          printf("%s\n", registerName[getRt(ir)]);
          break;
        }

        case 34: { // 100010 -> sub, R-Type.
          printf("sub ");
          printf("%s, ", registerName[getRd(ir)]);
          printf("%s, ", registerName[getRs(ir)]);
          printf("%s\n", registerName[getRt(ir)]);
          break;
        }
      }
      break;
    }
    case 2: { // 000010 -> j address (26), J-Type
      printf("j ");
      printf("0x%0.8X\n", getAddress(ir));
      break;
    }
    case 35: // 100011 (lw), I-Type. lw rt, imm(rs)
      printf("lw ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%d", getImmediate(ir));
      printf("(%s)\n", registerName[getRs(ir)]);
      break;

    default: // outros casos.
      fprintf(stdout, "Instrução não implementada. OpCode: %d.\n", getOpCode(ir));
  }
}

int main(int argc, char *argv[]) {
  PRINT_FUNC_NAME;
  int i;
  unsigned int ir;
  if (argc < 2) {
    fprintf(stderr, "Uso:\n ./decodificador arquivo.b\n");
    return (0);
  }

  TRACE("Argumentos:\n");
  TRACE("argc = %d\n", argc);
  for (i = 0; i < argc; i++){
    TRACE("argv[%d] = %s\n", i, argv[i]);
  }

  FILE *arquivo = fopen(argv[1], "r");
  size_t len = 32; // tamanho da linha.
  char *linha = malloc(len);

  if (!arquivo) {
    perror(argv[1]);
    exit(1);
  }

  while (getline(&linha, &len, arquivo) > 0) {
    TRACE("Linha: %s\n", linha);
    // teste: bin_prnt_byte(0x8C130004);
    ir = intFromBinary(linha);
    TRACE("IR: %u\n", ir);
    decodificar(ir);
  }

  if (linha) {
    free(linha);
  }

  fclose(arquivo);

  return 0;
}
