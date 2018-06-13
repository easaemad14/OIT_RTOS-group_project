#include "ISR_Support.h"
    
    .set    nomips16
    .set    noreorder
    
    .extern vUART_ISR
    .extern xISRStackTop
    .global vUART_ISR_Wrapper
    .set    noreorder
    .set    noat
    .ent    vUART_ISR_Wrapper
    
vUART_ISR_Wrapper:
    portSAVE_CONTEXT
    
    jal vUART_ISR
    nop
    
    portRESTORE_CONTEXT
    
    .end vUART_ISR_Wrapper
