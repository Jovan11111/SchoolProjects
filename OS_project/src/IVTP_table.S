.global IVTP_TABLE

.extern _ZN5Riscv15interrupt_ecallEv
.extern _ZN5Riscv15interrupt_timerEv
.extern _ZN5Riscv17interrupt_consoleEv

.align 4

IVTP_TABLE:
    .org IVTP_TABLE
    j _ZN5Riscv15interrupt_ecallEv
    .org IVTP_TABLE + 4
    j _ZN5Riscv15interrupt_timerEv
    .org IVTP_TABLE + 36
    j _ZN5Riscv17interrupt_consoleEv