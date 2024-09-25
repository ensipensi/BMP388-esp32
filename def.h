
#include "stdint.h"
#include "stdio.h"
// Definimos pines I2C
#define SDA_I2C GPIO_NUM_13
#define SCL_I2C GPIO_NUM_16

// Definimos direccion I2C
#define ADDR_I2C                0x77 // Registro i2c

// Registros del datos
#define REG_TEMP                0x07 // Registro temperatura
#define REG_PRESS               0x04 // Registro presion

// Registros de los datos de calibración
#define NVM_PAR_T1              0x31
#define NVM_PAR_T2              0x33
#define NVM_PAR_T3              0x35
#define NVM_PAR_P1              0x36
#define NVM_PAR_P2              0x38
#define NVM_PAR_P3              0x3A
#define NVM_PAR_P4              0x3B
#define NVM_PAR_P5              0x3C
#define NVM_PAR_P6              0x3E
#define NVM_PAR_P7              0x40
#define NVM_PAR_P8              0x41
#define NVM_PAR_P9              0x42
#define NVM_PAR_P10             0x44
#define NVM_PAR_P11             0x45

// Registros para configuraciones
#define REG_PWR_CNTRL           0x1B // Registro de la inicialización del sensor para su funcionamiento
#define REG_OSR                 0x1C // Registro del oversampling
#define REG_CONFIG              0x1F // Registro del filtro
#define REG_ODR                 0x1D // Registro del output data

/*! Datos de calibración */
struct RegCalibData
{
    uint16_t nvm_par_t1;
    uint16_t nvm_par_t2;
    int8_t nvm_par_t3;
    int16_t nvm_par_p1;
    int16_t nvm_par_p2;
    int8_t nvm_par_p3;
    int8_t nvm_par_p4;
    uint16_t nvm_par_p5;
    uint16_t nvm_par_p6;
    int8_t nvm_par_p7;
    int8_t nvm_par_p8;
    int16_t nvm_par_p9;
    int8_t nvm_par_p10;
    int8_t nvm_par_p11;
};




/*! Coeficientes de calibración*/
struct DataCoefficients
{
    float nvm_t1;
    float nvm_t2;
    float nvm_t3;
    float nvm_p1;
    float nvm_p2;
    float nvm_p3;
    float nvm_p4;
    float nvm_p5;
    float nvm_p6;
    float nvm_p7;
    float nvm_p8;
    float nvm_p9;
    float nvm_p10;
    float nvm_p11;

    float comp_temp;
    
};


/*! Los datos para la elección del oversampling */
typedef enum
{
    OVRS_X1 = 0,
    OVRS_X2,
    OVRS_X4,
    OVRS_X8,
    OVRS_X16,
    OVRS_X32
} Oversampling_t;

/*! Los datos para la elección del IIRFILTER*/
typedef enum
{
    COEFF_0 = 0, // bypass mode
    COEFF_1,
    COEFF_3,
    COEFF_7,
    COEFF_15,
    COEFF_31,
    COEFF_63,
    COEF_111
} IIRfilter_t;

typedef enum
{
    ODR_200 = 0,
    ODR_100,
    ODR_50,
    ODR_25,
    ODR_12p5,
    ODR_6p25,
    ODR_3p1,
    ODR_1p5,
    ODR_0p78,
    ODR_0p39,
    ODR_0p2,
    ODR_0p1,
    ODR_0p05,
    ODR_0p02,
    ODR_0p01,
    ODR_0p006,
    ODR_0p003,
    ODR_0p0015
} OutputDataRate_t;



typedef enum
{
    INIT_SENSOR_SUCCESS,
    INIT_SENSOR_FAILED,
    GET_UNCOMP_MEASURES_SUCCESS,
    GET_UNCOMP_MEASURES_FAILED,
    GET_CALIB_DATA_SUCCESS,
    GET_CALIB_DATA_FAILED,
    GET_MEASURES_SUCCESS,
    GET_MEASURES_FAILED,
    GET_TEMP_SUCCESS,
    GET_TEMP_FAILED,
    GET_PRESS_SUCCESS,
    GET_PRESS_FAILED,
    SET_OVERSAMPLING_SUCCESS,
    SET_OVERSAMPLING_FAILED,
    GET_OVERSAMPLING_SUCCESS,
    GET_OVERSAMPLING_FAILED,
    SET_IRR_FILTER_SUCCESS,
    SET_IRR_FILTER_FAILED,
    GET_IRR_FILTER_SUCCESS,
    GET_IRR_FILTER_FAILED,
    SET_ODR_SUCCESS,
    SET_ODR_FAILED,
    GET_ODR_SUCCESS,
    GET_ODR_FAILED

}SensorEnum_t;