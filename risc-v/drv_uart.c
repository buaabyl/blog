#include <stdint.h>

// efficiency
volatile uint32_t* UART_BASE = (volatile uint32_t*)(0x40000000);
#define UART_CTL (UART_BASE + 0)
#define UART_RXB (UART_BASE + 1)
#define UART_TXB (UART_BASE + 2)

// ok
volatile uint32_t* uart_base = (volatile uint32_t*)(0x40000000);
volatile uint32_t* uart_ctl  = (volatile uint32_t*)(0x40000000);
volatile uint32_t* uart_rxb  = (volatile uint32_t*)(0x40000004);
volatile uint32_t* uart_txb  = (volatile uint32_t*)(0x40000008);

// too many assembly codes......
struct uart_t{
    uint32_t CTL;
    uint32_t RXB;
    uint32_t TXB;
} __attribute__((packed));

typedef struct uart_t uart_t;

volatile uart_t*  UART_INST  = (volatile uart_t*)(0x40000000);


////////////////////////////////////////////////////////////
int hal_uart_receive(void)
{
    while (!(*UART_CTL & 0x80)) {
    }

    return *UART_RXB;
}

int hal_uart_receive_ptr(void)
{
    while (!(*uart_ctl & 0x80)) {
    }

    return *uart_rxb;
}

int hal_uart_receive_struct(void)
{
    while (!(UART_INST->CTL & 0x80)) {
    }

    return UART_INST->RXB;
}

////////////////////////////////////////////////////////////
void hal_uart_transmit(uint32_t val)
{
    while (!(*UART_CTL & 0x40)) {
    }

    *UART_TXB = val;
}

void hal_uart_transmit_ptr(uint32_t val)
{
    while (!(*uart_ctl & 0x40)) {
    }

    *uart_txb = val;
}

void hal_uart_transmit_struct(uint32_t val)
{
    while (!(UART_INST->CTL & 0x40)) {
    }

    UART_INST->TXB = val;
}

