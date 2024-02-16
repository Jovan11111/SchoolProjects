# 1 "src/popRegisters.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/riscv64-linux-gnu/include/stdc-predef.h" 1 3
# 32 "<command-line>" 2
# 1 "src/popRegisters.S"
.global _ZN5Riscv12popRegistersEv
.type _ZN5Riscv12popRegistersEv, @function

_ZN5Riscv12popRegistersEv:
ld x0, 0(sp)
ld x1, 8(sp)
ld x2, 16(sp)
ld x3, 24(sp)
ld x4, 32(sp)
ld x5, 40(sp)
ld x6, 48(sp)
ld x7, 56(sp)
ld x8, 64(sp)
ld x9, 72(sp)
ld x10, 80(sp)
ld x11, 88(sp)
ld x12, 96(sp)
ld x13, 104(sp)
ld x14, 112(sp)
ld x15, 120(sp)
ld x16, 128(sp)
ld x17, 136(sp)
ld x18, 144(sp)
ld x19, 152(sp)
ld x20, 160(sp)
ld x21, 168(sp)
ld x22, 176(sp)
ld x23, 184(sp)
ld x24, 192(sp)
ld x25, 200(sp)
ld x26, 208(sp)
ld x27, 216(sp)
ld x28, 224(sp)
ld x29, 232(sp)
ld x30, 240(sp)
ld x31, 248(sp)

addi sp, sp, 256
ret
