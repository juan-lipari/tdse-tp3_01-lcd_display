//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "smart_home_system.h"

#include "display.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut incorrectCodeLed(LED3);
DigitalOut systemBlockedLed(LED2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//char codeSequenceFromUserInterface[CODE_NUMBER_OF_KEYS];

//=====[Declaration and initialization of private global variables]============
uint32_t contador = 0;
//static bool incorrectCodeState = OFF;
//static bool systemBlockedState = OFF;

//static bool codeComplete = false;
//static int numberOfCodeChars = 0;

//=====[Declarations (prototypes) of private functions]========================



static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{

    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
   
    userInterfaceDisplayUpdate();
}



//=====[Implementations of private functions]==================================

#define DISPLAY_I2C (0)
#define DISPLAY_8BITS (1)
#define DISPLAY_4BITS (2)
#define DISPLAY (DISPLAY_I2C)

static void userInterfaceDisplayInit()
{
    #if (DISPLAY == DISPLAY_I2C)
        displayInit( DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER );
    #elif (DISPLAY == DISPLAY_8BITS)
        displayInit( DISPLAY_CONNECTION_GPIO_8BITS );
    #elif (DISPLAY == DISPLAY_4BITS)
        displayInit( DISPLAY_CONNECTION_GPIO_4BITS );
    #endif

    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Temperature:" );
}

static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    char temperatureString[3] = "";
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        sprintf(temperatureString, "%.0d", contador++); //sprintf(temperatureString, "%.0f", temperatureSensorReadCelsius());
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( temperatureString );
        displayCharPositionWrite ( 14,0 );
        displayStringWrite( "'C" );
    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}

