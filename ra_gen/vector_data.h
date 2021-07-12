/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (20)
#endif
/* ISR prototypes */
void sci_uart_rxi_isr(void);
void sci_uart_txi_isr(void);
void sci_uart_tei_isr(void);
void sci_uart_eri_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_SCI0_RXI ((IRQn_Type) 0) /* SCI0 RXI (Receive data full) */
#define VECTOR_NUMBER_SCI0_TXI ((IRQn_Type) 1) /* SCI0 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI0_TEI ((IRQn_Type) 2) /* SCI0 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI0_ERI ((IRQn_Type) 3) /* SCI0 ERI (Receive error) */
#define VECTOR_NUMBER_SCI2_RXI ((IRQn_Type) 4) /* SCI2 RXI (Receive data full) */
#define VECTOR_NUMBER_SCI2_TXI ((IRQn_Type) 5) /* SCI2 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI2_TEI ((IRQn_Type) 6) /* SCI2 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI2_ERI ((IRQn_Type) 7) /* SCI2 ERI (Receive error) */
#define VECTOR_NUMBER_SCI1_RXI ((IRQn_Type) 8) /* SCI1 RXI (Received data full) */
#define VECTOR_NUMBER_SCI1_TXI ((IRQn_Type) 9) /* SCI1 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI1_TEI ((IRQn_Type) 10) /* SCI1 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI1_ERI ((IRQn_Type) 11) /* SCI1 ERI (Receive error) */
#define VECTOR_NUMBER_SCI9_RXI ((IRQn_Type) 12) /* SCI9 RXI (Received data full) */
#define VECTOR_NUMBER_SCI9_TXI ((IRQn_Type) 13) /* SCI9 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI9_TEI ((IRQn_Type) 14) /* SCI9 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI9_ERI ((IRQn_Type) 15) /* SCI9 ERI (Receive error) */
#define VECTOR_NUMBER_SCI3_RXI ((IRQn_Type) 16) /* SCI3 RXI (Receive data full) */
#define VECTOR_NUMBER_SCI3_TXI ((IRQn_Type) 17) /* SCI3 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI3_TEI ((IRQn_Type) 18) /* SCI3 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI3_ERI ((IRQn_Type) 19) /* SCI3 ERI (Receive error) */
typedef enum IRQn
{
    Reset_IRQn = -15,
    NonMaskableInt_IRQn = -14,
    HardFault_IRQn = -13,
    MemoryManagement_IRQn = -12,
    BusFault_IRQn = -11,
    UsageFault_IRQn = -10,
    SecureFault_IRQn = -9,
    SVCall_IRQn = -5,
    DebugMonitor_IRQn = -4,
    PendSV_IRQn = -2,
    SysTick_IRQn = -1,
    SCI0_RXI_IRQn = 0, /* SCI0 RXI (Receive data full) */
    SCI0_TXI_IRQn = 1, /* SCI0 TXI (Transmit data empty) */
    SCI0_TEI_IRQn = 2, /* SCI0 TEI (Transmit end) */
    SCI0_ERI_IRQn = 3, /* SCI0 ERI (Receive error) */
    SCI2_RXI_IRQn = 4, /* SCI2 RXI (Receive data full) */
    SCI2_TXI_IRQn = 5, /* SCI2 TXI (Transmit data empty) */
    SCI2_TEI_IRQn = 6, /* SCI2 TEI (Transmit end) */
    SCI2_ERI_IRQn = 7, /* SCI2 ERI (Receive error) */
    SCI1_RXI_IRQn = 8, /* SCI1 RXI (Received data full) */
    SCI1_TXI_IRQn = 9, /* SCI1 TXI (Transmit data empty) */
    SCI1_TEI_IRQn = 10, /* SCI1 TEI (Transmit end) */
    SCI1_ERI_IRQn = 11, /* SCI1 ERI (Receive error) */
    SCI9_RXI_IRQn = 12, /* SCI9 RXI (Received data full) */
    SCI9_TXI_IRQn = 13, /* SCI9 TXI (Transmit data empty) */
    SCI9_TEI_IRQn = 14, /* SCI9 TEI (Transmit end) */
    SCI9_ERI_IRQn = 15, /* SCI9 ERI (Receive error) */
    SCI3_RXI_IRQn = 16, /* SCI3 RXI (Receive data full) */
    SCI3_TXI_IRQn = 17, /* SCI3 TXI (Transmit data empty) */
    SCI3_TEI_IRQn = 18, /* SCI3 TEI (Transmit end) */
    SCI3_ERI_IRQn = 19, /* SCI3 ERI (Receive error) */
} IRQn_Type;
#endif /* VECTOR_DATA_H */
