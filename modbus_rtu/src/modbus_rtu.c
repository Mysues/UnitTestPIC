/*******************************************************************************
 * This file provides the functions for the MODBUS RTU Communication Protocol.
 *******************************************************************************/

#include "../include/modbus_rtu.h"

/*******************************************************************************
 * Modbus Registers variable
 * these variable will need to be initialized using MODBUS_RTU_Init function
 *******************************************************************************/
uint16_t *modbus_reg;
uint16_t modbus_reg_rw_start = 0;
uint16_t modbus_reg_rw_end = 0;
uint16_t modbus_reg_length = 0;
#define MODBUS_ID  0x03

/*******************************************************************************
 * UART and Interrupt handler
 *******************************************************************************/
bool (*uartRxReady)(void);
uint8_t (*uartRead)(void);
void (*uartWrite)(uint8_t);
void (*interruptDisable)(void);
void (*interruptEnable)(void);

/*******************************************************************************
 * FUNCTION: MODBUS_RTU_UartHandler
 *
 * PARAMETERS:
 * ~ bool (*uartRxReady_)(void)     - handler for uartRxReady
 * ~ uint8_t (*uartRead_)(void)     - handler for uartRead
 * ~ void (*uartWrite_)(uint8_t)    - handler for uartWrite
 *
 * RETURN:
 * ~ void
 *
 * DESCRIPTIONS:
 * initialize handler for uart communication functions
 *
 *******************************************************************************/
void MODBUS_RTU_UartHandler(
        bool (* uartRxReady_)(void), 
        uint8_t (* uartRead_)(void), 
        void (* uartWrite_)(uint8_t))
{
    uartRxReady = uartRxReady_;
    uartRead = uartRead_;
    uartWrite = uartWrite_;
}


/*******************************************************************************
 * FUNCTION: MODBUS_RTU_UartHandler
 *
 * PARAMETERS:
 * ~ void (*interruptDisable_)(void)    - handler for interruptDisable
 * ~ void (*interruptEnable_)(void)     - handler for interruptEnable
 *
 * RETURN:
 * ~ void
 *
 * DESCRIPTIONS:
 * initialize handler for interrupt enable and disable
 *
 *******************************************************************************/
void MODBUS_RTU_InterruptHandler(
        void (* interruptDisable_)(void),
        void (* interruptEnable_)(void))
{
    interruptDisable = interruptDisable_;
    interruptEnable = interruptEnable_;
}


/*******************************************************************************
 * PRIVATE DEFINITION
 *******************************************************************************/

// Function Code.
typedef enum {
    FC_READ_REG         = 0x03,
    FC_WRITE_SINGLE_REG = 0x06,
    FC_WRITE_MULTI_REG  = 0x10,
} FUNCTION_CODE;

// Error Code.
typedef enum {
    NO_ERROR                = 0x00,
    ILLEGAL_FUNCTION        = 0x01,
    ILLEGAL_DATA_ADDRESS    = 0x02,
    ILLEGAL_DATA_VALUE      = 0x03,
    SERVER_DEVICE_FAILURE   = 0x04,
} ERROR_CODE;


// MODBUS Broadcast Slave Address.
#define MODBUS_BROADCAST_ADD            0

// Index in the data buffer.
#define IND_ADDRESS                     0
#define IND_FUNCTION                    1

#define IND_READ_REG_START_ADD          2
#define IND_READ_REG_QUANTITY           4

#define IND_WRITE_SINGLE_REG_ADD        2
#define IND_WRITE_SINGLE_REG_VALUE      4

#define IND_WRITE_MULTI_REG_START_ADD   2
#define IND_WRITE_MULTI_REG_QUANTITY    4
#define IND_WRITE_MULTI_REG_BYTECOUNT   6
#define IND_WRITE_MULTI_REG_VALUE       7

#define IND_EXCEPTION                   2


/*******************************************************************************
 * PRIVATE GLOBAL VARIABLES
 *******************************************************************************/
// Table of CRC values for high order byte.
static uint8_t auchCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40
};

// Table of CRC values for low order byte.
static uint8_t auchCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
    0x40
};


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 *******************************************************************************/

static uint16_t generateCrc(uint8_t *data, uint8_t length);
static void processFunction(uint8_t *rxBuffer);
static ERROR_CODE readRegisters(uint8_t *buffer, uint16_t startAddress, uint8_t quantity);
static ERROR_CODE writeRegisters(uint8_t *buffer, uint16_t startAddress, uint8_t quantity);


/*******************************************************************************
 * FUNCTION: generateCrc
 *
 * PARAMETERS:
 * ~ *data      - Data buffer.
 * ~ length     - Data length.
 *
 * RETURN:
 * ~ CRC result.
 *
 * DESCRIPTIONS:
 * Generate the CRC value.
 *
 *******************************************************************************/
static uint16_t generateCrc(uint8_t *data, uint8_t length)
{
    uint8_t uchCRCHi = 0xFF;
    uint8_t uchCRCLo = 0xFF;
    uint8_t uIndex;
    
    // Calculate the CRC.
    while (length--) {
        uIndex = uchCRCLo ^ *data++;
        uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
        uchCRCHi = auchCRCLo[uIndex];
    }
    
    return ((uint16_t)uchCRCHi << 8 | (uint16_t)uchCRCLo) ;
}


/*******************************************************************************
 * FUNCTION: processFunction
 *
 * PARAMETERS:
 * ~ rxBuffer   - Buffer for received data.
 *
 * RETURN:
 * ~ void
 *
 * DESCRIPTIONS:
 * Process the function.
 *
 *******************************************************************************/
static void processFunction(uint8_t *rxBuffer)
{
    uint16_t i = 0;
    static uint8_t txBuffer[256];
    
    uint8_t function;
    uint16_t regAddress;
    uint8_t regQuantity;
    uint8_t byteCount;
    
    ERROR_CODE error;
    
    // Construct the response.
    txBuffer[i++] = rxBuffer[IND_ADDRESS];
    txBuffer[i++] = rxBuffer[IND_FUNCTION];
    
    function = rxBuffer[IND_FUNCTION];
    switch (function) {
        case FC_READ_REG: {
            regAddress = (uint16_t)rxBuffer[IND_READ_REG_START_ADD] << 8;
            regAddress += (uint16_t)rxBuffer[IND_READ_REG_START_ADD + 1];
            
            regQuantity = (uint8_t)((uint16_t)rxBuffer[IND_READ_REG_QUANTITY] << 8);
            regQuantity += (uint8_t)((uint16_t)rxBuffer[IND_READ_REG_QUANTITY + 1]);
            
            // Make sure the quantity is valid.
            if ((regQuantity >= 1) && (regQuantity <= 125)) {
                // Byte count = N x 2.
                byteCount = (uint8_t)(regQuantity << 1);
                txBuffer[i++] = byteCount;

                // Get the register value.
                error = readRegisters(&txBuffer[i], regAddress, regQuantity);

                // Offset the index.
                i += byteCount;
            }
            
            // Quantity is invalid.
            else {
                error = ILLEGAL_DATA_VALUE;
            }
            
            break;
        }
        
        case FC_WRITE_SINGLE_REG: {
            regAddress = (uint16_t)rxBuffer[IND_WRITE_SINGLE_REG_ADD] << 8;
            regAddress += (uint16_t)rxBuffer[IND_WRITE_SINGLE_REG_ADD + 1];
            
            // Write the register value.
            error = writeRegisters(&rxBuffer[IND_WRITE_SINGLE_REG_VALUE], regAddress, 1);
            
            // Construct the response if no error.
            if (error == NO_ERROR) {
                txBuffer[i++] = rxBuffer[IND_WRITE_SINGLE_REG_ADD];
                txBuffer[i++] = rxBuffer[IND_WRITE_SINGLE_REG_ADD + 1];

                txBuffer[i++] = rxBuffer[IND_WRITE_SINGLE_REG_VALUE];
                txBuffer[i++] = rxBuffer[IND_WRITE_SINGLE_REG_VALUE + 1];
            }
            
            break;
        }
        
        case FC_WRITE_MULTI_REG: {
            regAddress = (uint16_t)rxBuffer[IND_WRITE_MULTI_REG_START_ADD] << 8;
            regAddress += (uint16_t)rxBuffer[IND_WRITE_MULTI_REG_START_ADD + 1];
            
            regQuantity = (uint8_t)((uint16_t)rxBuffer[IND_WRITE_MULTI_REG_QUANTITY] << 8);
            regQuantity += (uint8_t)((uint16_t)rxBuffer[IND_WRITE_MULTI_REG_QUANTITY + 1]);
            
            // Make sure the quantity is valid.
            if ((regQuantity >= 1) && (regQuantity <= 123)) {
                // Write the register value.
                error = writeRegisters(&rxBuffer[IND_WRITE_MULTI_REG_VALUE], regAddress, regQuantity);
                
                // Construct the response if no error.
                if (error == NO_ERROR) {
                    txBuffer[i++] = rxBuffer[IND_WRITE_MULTI_REG_START_ADD];
                    txBuffer[i++] = rxBuffer[IND_WRITE_MULTI_REG_START_ADD + 1];

                    txBuffer[i++] = rxBuffer[IND_WRITE_MULTI_REG_QUANTITY];
                    txBuffer[i++] = rxBuffer[IND_WRITE_MULTI_REG_QUANTITY + 1];
                }
            }
            
            // Quantity is invalid.
            else {
                error = ILLEGAL_DATA_VALUE;
            }
            
            break;
        }
        
        default: {
            error = ILLEGAL_FUNCTION;
            break;
        }
    }
    
    // Send the response if the MODBUS address is not broadcast address.
    if (rxBuffer[IND_ADDRESS] != MODBUS_BROADCAST_ADD) {
        switch (error) {
            case NO_ERROR: {
                // Add in CRC value.
                uint16_t crc = generateCrc(txBuffer, (uint8_t)i);
                txBuffer[i++] = (uint8_t)crc;
                txBuffer[i++] = (uint8_t)(crc >> 8);

                // Send the response.
                int j;
                for (j = 0; j < i; j += 1)
                {
                    if (uartWrite != NULL) uartWrite(txBuffer[j]);
                }
                
                break;
            }

            default: {
                // Set the MSB of function code.
                txBuffer[IND_FUNCTION] += 0x80;

                // Set the exception code.
                txBuffer[IND_EXCEPTION] = error;

                // Add in CRC value.
                i = IND_EXCEPTION + 1;
                uint16_t crc = generateCrc(txBuffer, (uint8_t)i);
                txBuffer[i++] = (uint8_t)crc;
                txBuffer[i++] = (uint8_t)(crc >> 8);

                // Send the response.
                int j;
                for (j = 0; j < i; j += 1)
                {
                    if (uartWrite != NULL) uartWrite(txBuffer[j]);
                }
                
                break;
            }
        }
    }
}


/*******************************************************************************
 * FUNCTION: readRegisters
 *
 * PARAMETERS:
 * ~ buffer         - Buffer for register value.
 * ~ startAddress   - Start address to read from.
 * ~ quantity       - Quantity of register to read.
 *
 * RETURN:
 * ~ Return the error code.
 *
 * DESCRIPTIONS:
 * Read the register value.
 *
 *******************************************************************************/
static ERROR_CODE readRegisters(uint8_t *buffer, uint16_t startAddress, uint8_t quantity)
{
    
    // Make sure the start address is within the valid range.
    if (startAddress >= modbus_reg_length) {
        return ILLEGAL_DATA_ADDRESS;
    }
    
    // Make sure the quantity is within range.
    if ((startAddress + quantity) > modbus_reg_length) {
        return ILLEGAL_DATA_ADDRESS;
    }
    
    // Start reading the registers.
    uint8_t i = 0;
    while (quantity-- > 0) {
        if (interruptDisable != NULL) interruptDisable();
        buffer[i++] = (uint8_t)(modbus_reg[startAddress] >> 8);
        buffer[i++] = (uint8_t)(modbus_reg[startAddress]);
        if (interruptEnable != NULL) interruptEnable();
        
        startAddress++;
    }
    
    return NO_ERROR;
}


/*******************************************************************************
 * FUNCTION: writeRegisters
 *
 * PARAMETERS:
 * ~ buffer         - Buffer for register value.
 * ~ startAddress   - Start address to write to.
 * ~ quantity       - Quantity of register to write.
 *
 * RETURN:
 * ~ Return the error code.
 *
 * DESCRIPTIONS:
 * Write the register value.
 *
 *******************************************************************************/
static ERROR_CODE writeRegisters(uint8_t *buffer, uint16_t startAddress, uint8_t quantity)
{
    // Make sure the start address is within the valid range.
    if (startAddress >= modbus_reg_length) {
        return ILLEGAL_DATA_ADDRESS;
    }
    
    // Make sure the quantity is within range.
    if ((startAddress + quantity) > modbus_reg_length) {
        return ILLEGAL_DATA_ADDRESS;
    }
    
    // Start writting the registers.
    uint8_t i = 0;
    while (quantity-- > 0) {
        // The address range is writable.
        if ( (startAddress >= modbus_reg_rw_start) && 
            (startAddress <= modbus_reg_rw_end) ) {
            if (interruptDisable != NULL) interruptDisable();
            modbus_reg[startAddress] = (uint16_t)buffer[i++] << 8;
            modbus_reg[startAddress] += (uint16_t)buffer[i++];
            if (interruptEnable != NULL) interruptEnable();
        }
        
        // Address is Read-Only.
        else {
            i += 2;
        }
        
        startAddress++;
    }
    
    return NO_ERROR;
}


/*******************************************************************************
 * FUNCTION: MODBUS_RTU_Init
 *
 * PARAMETERS:
 * ~ modbus_reg_[] - the pointer to the modbus register
 * ~ modbus_reg_rw_start_ - the start index for rw registers
 * ~ modbus_reg_rw_end_ - the end index for rw registers
 * ~ modbus_reg_length_ - the length of the modbus registers
 * 
 * RETURN:
 * ~ void
 *
 * DESCRIPTIONS:
 * Initialize the MODBUS RTU registers size, length and rw start and end index
 *
 *******************************************************************************/
void MODBUS_RTU_Init(uint16_t modbus_reg_[], uint16_t modbus_reg_rw_start_, 
        uint16_t modbus_reg_rw_end_, uint16_t modbus_reg_length_)
{
    modbus_reg = modbus_reg_;
    modbus_reg_rw_start = modbus_reg_rw_start_;
    modbus_reg_rw_end = modbus_reg_rw_end_;
    modbus_reg_length = modbus_reg_length_;
}


/*******************************************************************************
 * PUBLIC FUNCTION: MODBUS_RTU_ProcessFrame
 *
 * PARAMETERS:
 * ~ void
 *
 * RETURN:
 * ~ void
 *
 * DESCRIPTIONS:
 * Process the data received via UART.
 *
 *******************************************************************************/
//variable for process
uint16_t i = 0;
uint8_t buffer[256] = {0};
uint16_t length = sizeof(buffer);

uint8_t MODBUS_RTU_ProcessFrame(void)
{   
    static uint8_t function = 0;
    uint8_t result = 0;
    
    do {
        // Read the data if available.
        if ((uartRxReady != NULL) && (uartRxReady())) {

            if (uartRead != NULL) buffer[i] = uartRead();

            // Determine the actual frame length based on function code.
            if (i == IND_FUNCTION) {
                function = buffer[IND_FUNCTION];
                switch (function) {
                    case FC_READ_REG:
                    case FC_WRITE_SINGLE_REG:
                        length = 8;
                        break;
                }
            }

            // For function FC_WRITE_MULTI_REG, we need the byte count to determine the frame length.
            if ( (i == IND_WRITE_MULTI_REG_BYTECOUNT) &&
                 (function == FC_WRITE_MULTI_REG) ){
                length = buffer[IND_WRITE_MULTI_REG_BYTECOUNT] + 9;
            }

            i++;
        }

        // Start processing after receiving all the data or timeout occured.
        if (i >= length) {
            // Make sure there is data received.
            if (i >= 8) {
                // Make sure the MODBUS slave address matched.
                uint8_t address = buffer[IND_ADDRESS];
                if ((address == MODBUS_BROADCAST_ADD) || (address == (uint8_t)modbus_reg[MODBUS_ID])) {
                    // Get the received CRC value.
                    uint16_t receivedCrc = (uint16_t)buffer[i - 2] + ((uint16_t)buffer[i - 1] << 8);

                    // Generate the CRC based on data in the buffer.
                    uint16_t generatedCrc = generateCrc(buffer, (uint8_t)(i - 2));

                    // Process the data if the CRC matched.
                    if (receivedCrc == generatedCrc) {
                        processFunction(buffer);
                        result = 1;
                    }                  
                }
            }

            // Reset the index and set the length to maximum.
            //modbusTimeout = false;
            i = 0;
            length = sizeof(buffer);
        }
    } while ((uartRxReady != NULL) && (uartRxReady()));
    
    return result;
}


/*******************************************************************************
 * PUBLIC FUNCTION: MODBUS_RTU_Timeout
 *
 * PARAMETERS:
 * ~ void
 *
 * RETURN:
 * ~ void
 *
 * DESCRIPTIONS:
 * Timeout trigger for Modbus. This function should be call after timeout occur
 * for modbus.
 *
 *******************************************************************************/
void MODBUS_RTU_Timeout(void)
{
    i = 0;
    length = sizeof(buffer);
}
