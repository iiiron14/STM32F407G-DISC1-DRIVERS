# STM32F407G-DISC1 Drivers

Questa repository contiene una libreria di driver sviluppati da zero (bare-metal) per il microcontrollore **STM32F407VG**, basato su core ARM Cortex-M4, specificamente per la scheda di sviluppo **STM32F407G-DISC1**.

L'obiettivo del progetto è fornire un'implementazione efficiente e didattica delle periferiche hardware senza l'utilizzo delle librerie HAL/LL di ST, facilitando la comprensione del funzionamento dei registri.

## 🚀 Periferiche Supportate

I driver includono il supporto completo per le seguenti periferiche:

- **GPIO (General Purpose Input/Output):** Configurazione pin, modalità (Input, Output, Alt Fun, Analog), velocità, pull-up/pull-down e gestione degli interrupt esterni (EXTI).
- **SPI (Serial Peripheral Interface):** Supporto per comunicazioni Master e Slave, gestione del clock e dei dati in modalità Full-duplex.
- **I2C (Inter-Integrated Circuit):** Implementazione della comunicazione Master con gestione degli eventi, interrupt e modalità standard/fast.
- **USART/UART:** Trasmissione e ricezione seriale asincrona, configurazione del baud rate e gestione dei flag di stato.
- **RCC (Reset and Clock Control):** Macro e funzioni per l'abilitazione dei clock periferici sui bus AHB e APB.

## 🛠️ Requisiti

### Hardware
- Scheda **STM32F407G-DISC1** (o modelli compatibili con STM32F407VG).
- Cavo Mini-USB per alimentazione e debug.

### Software
- **STM32CubeIDE** (consigliato) o toolchain basata su `arm-none-eabi-gcc`.
- **STM32CubeProgrammer** o ST-LINK Utility.

## 📂 Struttura della Repository

```text
├── drivers/
│   ├── Inc/           # File header (.h) con definizioni dei registri e API
│   └── Src/           # Implementazione delle funzioni driver (.c)
├── Startup/           # Startup code e Linker Script
└── README.md
