#include "hal_data.h"
#include "common_utils.h"
#include "r_sci_uart.h"
#include "r_spi.h"
#include "spi.h"
#include "uart.h"
FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/

///////////TODO LIST
///
/// ENABLE PINS
///     L86 LDO-------------------------OK
///     BOOSTER-------------------------OK
///     TAIL----------------------------OK
///     BLE POWER-----------------------OK
///     LIS3----------------------------OK
///     EEPROM--------------------------OK
///     BUZZER--------------------------OK
///     HEADLIGHT-----------------------OK
///     STORAGE MODE--------------------OK
///
/// STATUS READINGS
///     PGOOD---------------------------OK
///     CHGOK---------------------------OK
///     LOCKSTAT------------------------OK
///
/// BLDC COMMUNICATION
///     9600 BAUD
///     115200 BAUD
///
/// LOCK COMMUNICATION
///
/// BLE - MCU COMMUNICATION
///
/// BLE RF BROADCAST
///
/// L86 COMMUNICATION
///
/// L86 DATA BROADCAST
///
/// LIS3 COMMUNICATION
///
/// LIS3 INTERRUPT
///
/// EEPROM R/W
///
/// ANALOG READINGS
///
/// PWM RGB
///
/// SIMCOM COMMUNICATION
///
/// SIMCOM BRINGUP
///
/// SIMCOM MQTT
///
/// SIMCOM GPS
///
///

///////////DEFINITIONS & MACROS


#define L86_PWR_ON                  R_IOPORT_PinWrite(&g_ioport_ctrl, L86EN, BSP_IO_LEVEL_HIGH)
#define L86_PWR_OFF                 R_IOPORT_PinWrite(&g_ioport_ctrl, L86EN, BSP_IO_LEVEL_LOW)
#define L86_UART_BAUDRATE_9600      (9600)

#define SIM7500_ON                   R_IOPORT_PinWrite(&g_ioport_ctrl, SIM7500_PWRKY_CTRL, BSP_IO_LEVEL_HIGH);
#define SIM7500_OFF                  R_IOPORT_PinWrite(&g_ioport_ctrl, SIM7500_PWRKY_CTRL, BSP_IO_LEVEL_LOW);
#define SIM7500_UART_BAUDRATE_115200 (115200)

#define BOOSTER_ON                  R_IOPORT_PinWrite(&g_ioport_ctrl, BOOSTEN, BSP_IO_LEVEL_LOW)
#define BOOSTER_OFF                 R_IOPORT_PinWrite(&g_ioport_ctrl, BOOSTEN, BSP_IO_LEVEL_HIGH)

#define BLDC_ENABLE                 R_IOPORT_PinWrite(&g_ioport_ctrl, BLDCEN, BSP_IO_LEVEL_HIGH)
#define BLDC_DISABLE                R_IOPORT_PinWrite(&g_ioport_ctrl, BLDCEN, BSP_IO_LEVEL_LOW)

#define BLE_PWR_ON                  R_IOPORT_PinWrite(&g_ioport_ctrl, BLEPWREN, BSP_IO_LEVEL_LOW)
#define BLE_PWR_OFF                 R_IOPORT_PinWrite(&g_ioport_ctrl, BLEPWREN, BSP_IO_LEVEL_HIGH)

#define LIS3_PWR_ON                 R_IOPORT_PinWrite(&g_ioport_ctrl, LIS3PWR, BSP_IO_LEVEL_HIGH)
#define LIS3_PWR_OFF                R_IOPORT_PinWrite(&g_ioport_ctrl, LIS3PWR, BSP_IO_LEVEL_LOW)

#define EEPROM_PWR_ON               R_IOPORT_PinWrite(&g_ioport_ctrl, EEPROM_PWR, BSP_IO_LEVEL_HIGH)
#define EEPROM_PWR_OFF              R_IOPORT_PinWrite(&g_ioport_ctrl, EEPROM_PWR, BSP_IO_LEVEL_LOW)

#define BUZZER_ON                   R_IOPORT_PinWrite(&g_ioport_ctrl, BUZZERCTRL, BSP_IO_LEVEL_HIGH)
#define BUZZER_OFF                  R_IOPORT_PinWrite(&g_ioport_ctrl, BUZZERCTRL, BSP_IO_LEVEL_LOW)

#define HEADLIGHT_ON                R_IOPORT_PinWrite(&g_ioport_ctrl, HEADLIGHT, BSP_IO_LEVEL_HIGH)
#define HEADLIGHT_OFF               R_IOPORT_PinWrite(&g_ioport_ctrl, HEADLIGHT, BSP_IO_LEVEL_LOW)

#define STORAGE_DISABLE             R_IOPORT_PinWrite(&g_ioport_ctrl, STORAGEEN, BSP_IO_LEVEL_HIGH)
#define STORAGE_ENABLE              R_IOPORT_PinWrite(&g_ioport_ctrl, STORAGEEN, BSP_IO_LEVEL_LOW)




///////////GLOBAL VARIABLES


uint8_t dataArrivedFlag = 0;
char testCommand[20];
uint8_t ISPGOOD = 0;
uint8_t ISCHGOK = 0;
uint8_t ISLOCKED = 0;

uint8_t pcTxBuffer[20];
uint8_t pcRxBuffer[20];
uint8_t uartBufferFull_LOCK = 0;

////////FUNCTIONS

uint8_t init_lis3dh()
{

    LIS3_PWR_ON;

    R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MICROSECONDS);

    fsp_err_t err;


    /* Initialize r_spi channel as master */
    err = R_SPI_Open(&g_spi0_ctrl, &g_spi0_cfg);
    /* Handle Error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n SCI_SPI open failed");
        APP_ERR_TRAP(err);
    }

    return 0;
}

uint8_t init_EEPROM()
{
    EEPROM_PWR_ON;

    fsp_err_t err;

    /* Initialize r_spi channel as master */
    err = R_SPI_Open(&g_spi0_ctrl, &g_spi0_cfg);
    /* Handle Error */
    if ((FSP_SUCCESS != err) | (FSP_ERR_ALREADY_OPEN != err))
    {
        APP_ERR_PRINT("\r\n SCI_SPI open failed");
        APP_ERR_TRAP(err);
    }

    return err;
}

uint8_t de_init_EEPROM()
{
    EEPROM_PWR_OFF;

    fsp_err_t err;

    /* Initialize r_spi channel as master */
    err = R_SPI_Close(&g_spi0_ctrl);
    /* Handle Error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n SCI_SPI close failed");
        APP_ERR_TRAP(err);
    }

    return err;
}

void read_PGOOD_CHGOK(void){
    bsp_io_level_t *readPointer = 0;

    R_IOPORT_PinRead(&g_ioport_ctrl, PGOOD, &readPointer);
    if(readPointer == BSP_IO_LEVEL_LOW) ISPGOOD = 1;
    else ISPGOOD = 0;

    R_IOPORT_PinRead(&g_ioport_ctrl, CHGOK, &readPointer);
    if(readPointer == BSP_IO_LEVEL_LOW) ISCHGOK = 1;
    else ISCHGOK = 0;
}

void read_LOCKSTAT(void){
    bsp_io_level_t *readPointer = 0;

    R_IOPORT_PinRead(&g_ioport_ctrl, LOCKSTAT, &readPointer);
    if(readPointer == BSP_IO_LEVEL_HIGH) ISLOCKED = 1;
    else ISLOCKED = 0;
}


void initializeAll(void)
{
    R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg);

//    R_ADC_Open(&ANALOGPINS_ctrl, &ANALOGPINS_cfg);

//    R_SCI_UART_Open(&UART_LOCK_ctrl, &UART_LOCK_cfg);
//    uart_initialize(&UART_LOCK_ctrl, &UART_LOCK_cfg);
//    uart_initialize(&UART_BLE_ctrl, &UART_BLE_cfg);

    /* Initialize UART for SIMCOM. */
//    uart_initialize(&UART_SIMCOM_ctrl, &UART_SIMCOM_cfg);

//    /* Setting Baud rate for SIMCOM7500 to 115200 */
//    baud_setting_t baud_setting;
//    bool enable_bitrate_modulation = false;
//    uint32_t error_rate_x_1000 = 500;
//
//    fsp_err_t err = R_SCI_UART_BaudCalculate(SIM7500_UART_BAUDRATE_115200, enable_bitrate_modulation, error_rate_x_1000, &baud_setting);
//
//    assert(FSP_SUCCESS == err);
//
//    err = R_SCI_UART_BaudSet(&UART_SIMCOM_ctrl, (void *) &baud_setting);
//    assert(FSP_SUCCESS == err);


    /* Initialize UART for L86. */
//    uart_initialize(&UART_L86_ctrl, &UART_L86_cfg);

//
//    /* Setting baud rate for L86 to 9600 */
//
//    err = R_SCI_UART_BaudCalculate(L86_UART_BAUDRATE_9600, enable_bitrate_modulation, error_rate_x_1000, &baud_setting);
//
//    assert(FSP_SUCCESS == err);
//
//    err = R_SCI_UART_BaudSet(&UART_L86_ctrl, (void *) &baud_setting);
//    assert(FSP_SUCCESS == err);


//    init_lis3dh();

    init_EEPROM();

//    set_uart_baud_rate(&UART_L86, L86_UART_BAUDRATE_9600);
//    R_SCI_UART_Open(&UART_SCOOTER_ctrl, &UART_SCOOTER_cfg);

//    R_GPT_Open(&PWM_RED_ctrl, &PWM_RED_cfg);
//    R_GPT_Open(&PWM_GREEN_ctrl, &PWM_GREEN_cfg);
//    R_GPT_Open(&PWM_BLUE_ctrl, &PWM_BLUE_cfg);

}
void dataArrived_ISR(void){
    dataArrivedFlag = 1;
}


void user_uart_callback_SCOOTER(uart_callback_args_t *p_args){}


void almost_ms_delay(uint32_t ms){
    bsp_prv_software_delay_loop(ms*12000);
}

void write2LIS3(int addr, int msg)
{
    uint16_t data = 0;

    addr &= 0x3F; //write mode + no auto increment;

    data = addr<<8 | msg;

    R_IOPORT_PinWrite(&g_ioport_ctrl, LIS3_CS, BSP_IO_LEVEL_LOW);
    R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_LOW);

    for(int i = 0; i<16; i++)
    {

        if(data & 0x80)
        {
            R_IOPORT_PinWrite(&g_ioport_ctrl, MOSI, BSP_IO_LEVEL_HIGH);
        }
        else
        {
            R_IOPORT_PinWrite(&g_ioport_ctrl, MOSI, BSP_IO_LEVEL_LOW);
        }
        R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_HIGH);

        data = data << 1;

        R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_LOW);

    }

    R_IOPORT_PinWrite(&g_ioport_ctrl, LIS3_CS, BSP_IO_LEVEL_HIGH);
}

uint16_t readLIS3(int addr)
{
    uint16_t msg = 0;
    char *msgInput;

    addr &= 0x3F;
    addr |= 0x80;

    R_IOPORT_PinWrite(&g_ioport_ctrl, LIS3_CS, BSP_IO_LEVEL_LOW);
    R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_LOW);

    for(int i = 0; i<8; i++)
    {

        if(addr & 0x80)
        {
            R_IOPORT_PinWrite(&g_ioport_ctrl, MOSI, BSP_IO_LEVEL_HIGH);
        }
        else
        {
            R_IOPORT_PinWrite(&g_ioport_ctrl, MOSI, BSP_IO_LEVEL_LOW);
        }
        R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_HIGH);

        addr = addr << 1;

        R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_LOW);

      }

    for(int i = 0; i<8; i++)
    {
        R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_HIGH);


        R_IOPORT_PinRead(&g_ioport_ctrl, MISO, &msgInput);


        msg = msg << 1;
        msg += msgInput;


        R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_LOW);

      }

    return msg;
}

uint16_t acc_spi_us_delay = 5;
uint8_t read_single_register(uint8_t reg)
{
  uint8_t res = 0;

  R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_HIGH);
  R_IOPORT_PinWrite(&g_ioport_ctrl, LIS3_CS, BSP_IO_LEVEL_LOW);

  R_IOPORT_PinWrite(&g_ioport_ctrl, MOSI, BSP_IO_LEVEL_HIGH);
  R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_LOW);

//  R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MICROSECONDS);
  R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_HIGH);
//  R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MICROSECONDS);

  R_IOPORT_PinWrite(&g_ioport_ctrl, MOSI, BSP_IO_LEVEL_LOW);
  R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_LOW);

//  R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MICROSECONDS);

  R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_HIGH);

//  R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MICROSECONDS);


  for (uint8_t i = 0; i < 6; i++)
  {
      if (((reg >> (5 - i)) & 1) == 1)
      {
          R_IOPORT_PinWrite(&g_ioport_ctrl, MOSI, BSP_IO_LEVEL_HIGH);
      }
      else
      {
          R_IOPORT_PinWrite(&g_ioport_ctrl, MOSI, BSP_IO_LEVEL_LOW);
      }

      R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_LOW);

//      R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MICROSECONDS);

      R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_HIGH);

//      R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MICROSECONDS);
  }

  for (uint8_t i = 0; i < 8; i++)
  {
      R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_LOW);

//      R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MICROSECONDS);

      res <<= 1;
      uint8_t temp_read = 0;
      R_IOPORT_PinRead(&g_ioport_ctrl, MISO, &temp_read);
      if (temp_read != 0) // 1
      {
        res |= 1;
      }

      R_IOPORT_PinWrite(&g_ioport_ctrl, SCK, BSP_IO_LEVEL_HIGH);
//      R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MICROSECONDS);
    }

    R_IOPORT_PinWrite(&g_ioport_ctrl, LIS3_CS, BSP_IO_LEVEL_HIGH);

    return res;
}


void hal_entry(void)
{

    /* TODO: add your own code here */
    char msg2Bsent1[10] = "Babanazar\n";
    char msg2Bsent2[7] = "MIROO\n";
    uint16_t lis3message = 0;
//    int i = 0;
    initializeAll();

//    L86_PWR_ON;
//    BLE_PWR_ON;

    SIM7500_ON;

//    STORAGE_DISABLE;

//    APP_PRINT ("\r\n ** Selam ** \r\n");

//    uart_print("Here we go!\n");
//    uart_print("ATI\r is sent to SIMCOM");
    send_to_simcom("ATI\r");

//    send_to_ble("AT+START\r\n");

    while(1)
    {

//        lis3message = readLIS3(0x0F);
//     //    lis3message = read_single_register(0x0F);
//     //
//         if(lis3message == 0x33)
//         {
//             uart_print("OK LIS3\n");
//         }
//         else
//         {
//             uart_print("FAILED LIS3\n");
//         }
        /*if(dataArrivedFlag){
            dataArrivedFlag = 0;s
            R_IOPORT_PinWrite(p_ctrl, pin, level)
        }*/



        write_to_EEPROM(0x3F);

        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

//        read_from_EEPROM(0x3F);


//        BOOSTER_ON;
//        BUZZER_ON;
//        BOOSTER_OFF;
//        BUZZER_OFF;

//        if(get_lock_data_received_flag() == true)
//        {
//            set_lock_data_received_flag(false);
//            uart_print(&g_temp_buffer);
//
//        }
//
//        if(true == get_L86_data_received_flag())
//        {
//            set_L86_data_received_flag(false);
//            uart_print(&g_temp_buffer);
//        }
    }


    //While loopu kapatınca çalışacak - ana akış:

//    STORAGE_DISABLE;
//    sendDebugMessage("STORAGE DISABLED\n", 17);
//    almost_ms_delay(100);
//
//
//    sendDebugMessage("bik bik bik start\n", 18);
//    BUZZER_ON;
//    HEADLIGHT_ON;
//    almost_ms_delay(1000);
//
//    BUZZER_OFF;
//    HEADLIGHT_OFF;
//    almost_ms_delay(500);
//
//    BUZZER_ON;
//    HEADLIGHT_ON;
//    almost_ms_delay(1000);
//
//    BUZZER_OFF;
//    HEADLIGHT_OFF;
//    almost_ms_delay(500);
//
//    BUZZER_ON;
//    HEADLIGHT_ON;
//    almost_ms_delay(1000);
//
//    BUZZER_OFF;
//    HEADLIGHT_OFF;
//    almost_ms_delay(500);
//    sendDebugMessage("bik bik bik end\n", 16);
//
    almost_ms_delay(100);

//    write_to_EEPROM(0x3F);

//    read_from_EEPROM(0x3F);
    lis3message = readLIS3(0x0F);
//    lis3message = read_single_register(0x0F);
//
    if(lis3message == 0x33)
    {
        uart_print("OK LIS3\n");
    }
    else
    {
        uart_print("FAILED LIS3\n");
    }


#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}



/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open (&g_ioport_ctrl, &g_bsp_pin_cfg);
    }
}

#if BSP_TZ_SECURE_BUILD

BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
#endif
