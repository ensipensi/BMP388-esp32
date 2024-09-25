#include "i2c.h"

TwoWire my_wire = TwoWire(0);

/*!
 * @brief Inicialización del i2c
 */
I2CEnum_t Init_I2C()
{

    I2CEnum_t reslt;
    if (my_wire.begin())
    {
        reslt = I2C_SUCCESS;
    }
    else
    {
        reslt = I2C_FAILED;
    }
    return reslt;
}

/**
 * @brief Lectura de registros de 8 bits
 *
 * @param reg_addr : dirección de registros
 * @param i2c_addr : dirección i2c
 * @param data : lectura
 * @return I2CEnum_t Error
 */
I2CEnum_t Read8_bit(uint8_t reg_addr, uint8_t i2c_addr, uint8_t *data)
{
    I2CEnum_t rtrn = I2C_READING_BYTES_FAILED;
    uint8_t byte_size = 1;

    my_wire.beginTransmission(i2c_addr);
    my_wire.write(reg_addr);
    my_wire.endTransmission();
    my_wire.requestFrom(i2c_addr, byte_size);
    uint8_t bytes_to_read = my_wire.available();

    if (bytes_to_read == byte_size)
    {

        if (my_wire.available())
        {
            *data = my_wire.read();
            rtrn = I2C_READING_BYTES_SUCCESS;
        }
    }
    return rtrn;
}

/**
 * @brief Lectura de registros de 16 bits
 *
 * @param reg_addr : dirección de registro
 * @param i2c_addr : dirección de i2c
 * @param data : lectura
 * @return I2CEnum_t Error
 */
I2CEnum_t Read16_Bit(uint8_t reg_addr, uint8_t i2c_addr, uint16_t *data)
{
    I2CEnum_t rtrn = I2C_READING_BYTES_FAILED;

    uint8_t byte_size = 2;
    my_wire.beginTransmission(i2c_addr);
    my_wire.write(reg_addr);
    my_wire.endTransmission();
    my_wire.requestFrom(i2c_addr, byte_size);
    uint8_t bytes_to_read = my_wire.available();

    if (bytes_to_read == byte_size)
    {

        if (my_wire.available())
        {
            uint8_t first = my_wire.read();

            uint8_t second = my_wire.read();

            *data = (second << 8) | first;
            rtrn = I2C_READING_BYTES_SUCCESS;
        }
    }

    return rtrn;
}

/**
 * @brief Lectura de registros de 24 bits
 *
 * @param reg_addr : dirección de registro
 * @param i2c_addr : dirección de i2c
 * @param data : lectura de registro
 * @return I2CEnum_t Error
 */
I2CEnum_t Read24_Bit(uint8_t reg_addr, uint8_t i2c_addr, uint32_t *data)
{
    I2CEnum_t rtrn = I2C_READING_BYTES_FAILED;
    uint8_t byte_size = 3;

    my_wire.beginTransmission(i2c_addr);
    my_wire.write(reg_addr);
    my_wire.endTransmission();
    my_wire.requestFrom(i2c_addr, byte_size);
    uint8_t bytes_to_read = my_wire.available();

    if (bytes_to_read == byte_size)
    {
        if (my_wire.available())
        {
            uint32_t first = my_wire.read();

            uint32_t second = my_wire.read();

            uint32_t third = my_wire.read();

            *data = (third << 16) | (second << 8) | first;

            rtrn = I2C_READING_BYTES_SUCCESS;
        }
    }

    return rtrn;
}

/**
 * @brief Lectura de registros 32 bits
 *
 * @param reg_addr : dirección de registro
 * @param i2c_addr : dirección de i2c
 * @param data : lectura
 * @return I2CEnum_t Error
 */
I2CEnum_t Read32_Bit(uint8_t reg_addr, uint8_t i2c_addr, uint32_t *data)
{
    I2CEnum_t rtrn = I2C_READING_BYTES_FAILED;
    uint8_t byte_size = 4;

    my_wire.beginTransmission(i2c_addr);
    my_wire.write(reg_addr);
    my_wire.endTransmission();
    my_wire.requestFrom(i2c_addr, byte_size);
    uint8_t bytes_to_read = my_wire.available();

    if (bytes_to_read == byte_size)
    {
        if (my_wire.available())
        {
            uint32_t first = my_wire.read();

            uint32_t second = my_wire.read();

            uint32_t third = my_wire.read();

            uint32_t fourth = my_wire.read();

            *data = (fourth << 24) | (third << 16) | (second << 8) | first;

            rtrn = I2C_READING_BYTES_SUCCESS;
        }
    }

    return rtrn;
}

/*!
 * @brief Escritura en registros de 8 bits
 * @param[in] addr_i2c : dirección de i2c
 * @param[in] reg_addr : dirección de registro
 * @param[in] data : dato que escribimos en el registro
 * @return Escribimos en el registro el dato que queremos
 */
void Write8_bit(uint8_t addr_i2c, uint8_t reg_addr, uint8_t data)
{

    my_wire.beginTransmission(addr_i2c);
    my_wire.write(reg_addr);
    my_wire.write(data);
    my_wire.endTransmission();
}

/*!
 * @brief pone a 1 el bit que deseemos de un número
 * @param[in] binary_num : el número que usaremos
 * @param[in] flag : el seteo a 1/0
 * @param[in] pos : la posición que queremos cambiar
 * @return El número cambiado
 */
uint8_t Set_Binary(uint8_t binary_num, uint8_t flag, uint8_t pos)
{

    uint8_t rslt;
    if (flag == 1)
    {
        rslt = binary_num | (1 << pos);
    }
    return rslt;
}

/*!
 * @brief Escritura por bandera en registro
 * @param[in] addr_i2c : dirección de i2c
 * @param[in] reg_addr : dirección de registro
 * @param[in] pos : posición a cambiar
 * @param[in] value : valor del bit
 * @return La escritura en bandera de un registro
 */
void Write8_Flag(uint8_t addr_i2c, uint8_t reg_addr, uint8_t pos, uint8_t value)
{
    uint8_t value_byte;

    uint8_t rslt = Read8_bit(reg_addr, addr_i2c, &value_byte);
    uint8_t reading = value_byte;

    if (rslt == I2C_READING_BYTES_SUCCESS)
    {
        reading = Set_Binary(reg_addr, value, pos);
        Write8_bit(addr_i2c, reg_addr, reading);
    }
}


