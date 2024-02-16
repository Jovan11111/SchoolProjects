.global _ZN7_thread13contextSwitchEPNS_7ContextES1_
.type _ZN7_thread13contextSwitchEPNS_7ContextES1_, @function
.align 4

_ZN7_thread13contextSwitchEPNS_7ContextES1_:
    sd sp, 0(a0)
    sd ra, 8(a0)
    ld sp, 0(a1)
    ld ra, 8(a1)
    ret
