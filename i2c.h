
#include "Arduino.h"
#include "Wire.h"
#include "math.h"
#include "stdio.h"

typedef enum
{
    I2C_FAILED = 0,
    I2C_SUCCESS,
    I2C_READING_BYTES_SUCCESS,
    I2C_READING_BYTES_FAILED
} I2CEnum_t;

// Funciones i2c

/*!
 * @brief Inicialización del i2c
 */
I2CEnum_t Init_I2C();

/**
 * @brief Lectura de registros de 8 bits
 *
 * @param reg_addr : dirección de registros
 * @param i2c_addr : dirección i2c
 * @param data : lectura
 * @return I2CEnum_t Error
 */
I2CEnum_t Read8_bit(uint8_t reg_addr, uint8_t i2c_addr, uint8_t *data);

/**
 * @brief Lectura de registros de 16 bits
 *
 * @param reg_addr : dirección de registro
 * @param i2c_addr : dirección de i2c
 * @param data : lectura
 * @return I2CEnum_t Error
 */
I2CEnum_t Read16_Bit(uint8_t reg_addr, uint8_t i2c_addr, uint16_t *data);

/**
 * @brief Lectura de registros de 24 bits
 *
 * @param reg_addr : dirección de registro
 * @param i2c_addr : dirección de i2c
 * @param data : lectura de registro
 * @return I2CEnum_t Error
 */
I2CEnum_t Read24_Bit(uint8_t reg_addr, uint8_t i2c_addr, uint32_t *data);

/*!
 * @brief pone a 1 el bit que deseemos de un número
 * @param[in] binary_num : el número que usaremos
 * @param[in] flag : el seteo a 1/0
 * @param[in] pos : la posición que queremos cambiar
 * @return El número cambiado
 */
uint8_t Set_Binary(uint8_t binary_num, uint8_t flag, uint8_t pos);

/*!
 * @brief Escritura en registros de 8 bits
 * @param[in] addr_i2c : dirección de i2c
 * @param[in] reg_addr : dirección de registro
 * @param[in] data : dato que escribimos en el registro
 * @return Escribimos en el registro el dato que queremos
 */
void Write8_bit(uint8_t addr_i2c, uint8_t reg_addr, uint8_t data);

/*!
 * @brief Escritura por bandera en registro
 * @param[in] addr_i2c : dirección de i2c
 * @param[in] reg_addr : dirección de registro
 * @param[in] pos : posición a cambiar
 * @param[in] value : valor del bit
 * @return La escritura en bandera de un registro
 */
void Write8_Flag(uint8_t addr_i2c, uint8_t reg_addr, uint8_t pos, uint8_t value);

/**
 * @brief Lectura de registros 32 bits
 *
 * @param reg_addr : dirección de registro
 * @param i2c_addr : dirección de i2c
 * @param data : lectura
 * @return I2CEnum_t Error
 */
I2CEnum_t Read32_Bit(uint8_t reg_addr, uint8_t i2c_addr, uint32_t *data);
