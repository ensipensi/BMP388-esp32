#include "sensor.h"
#include "i2c.h"

#define POS_TEMP 0x01
#define POS_PRESS 0x00
#define FLAG 0x01

static struct DataCoefficients coeff;
static struct RegCalibData reg_calib_data;

/*************************************************** FUNCIONES PRIVADAS ***************************************************/

/*!
 * @brief Lectura de registro de la temperatura

 */
SensorEnum_t Get_Uncompensate_temperature(uint32_t *uncomp_temp);

/*!
 * @brief Lectura de registro de la presión

 */
SensorEnum_t Get_Uncompensate_Pressure(uint32_t *uncomp_press);

/**
 * @brief Lectura de los datos de calibración
 *
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Calib_Data();

/*!
 * @brief Obtención de los coeficientes de calibración
 */
void Get_Calib_Coefficients();

/**
 * @brief Obtención de temperatura sin compensar
 *
 * @param uncomp_temp : parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Uncompensate_temperature(uint32_t *uncomp_temp)
{
    SensorEnum_t error = GET_UNCOMP_MEASURES_FAILED;
    uint32_t data;

    if (Read24_Bit(REG_TEMP, ADDR_I2C, &data) == I2C_READING_BYTES_SUCCESS)
    {
        *uncomp_temp = data;
        error = GET_UNCOMP_MEASURES_SUCCESS;
    }

    return error;
}

/**
 * @brief Obtención de presión sin compensar
 *
 * @param uncomp_press : parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Uncompensate_Pressure(uint32_t *uncomp_press)
{
    SensorEnum_t error = GET_UNCOMP_MEASURES_FAILED;
    uint32_t data;

    if (Read24_Bit(REG_PRESS, ADDR_I2C, &data) == I2C_READING_BYTES_SUCCESS)
    {
        *uncomp_press = data;
        error = GET_UNCOMP_MEASURES_SUCCESS;
    }

    return error;
}

/**
 * @brief Obtención de temperatura calibrada
 *
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Calib_Temperature();

/**
 * @brief Obtención de la presión calibrada
 *
 * @param calib_data : parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Calib_Press(float *calib_data);

/**
 * @brief Lectura de los datos de calibración
 *
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Calib_Data()
{
    SensorEnum_t error = GET_CALIB_DATA_FAILED;
    uint8_t value_byte;
    uint16_t value_2bytes;
    uint8_t count = 0;

    if (Read16_Bit(NVM_PAR_T1, ADDR_I2C, &value_2bytes) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_t1 = value_2bytes;
        count++;
    }

    if (Read16_Bit(NVM_PAR_T2, ADDR_I2C, &value_2bytes) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_t2 = value_2bytes;
        count++;
    }

    if (Read8_bit(NVM_PAR_T3, ADDR_I2C, &value_byte) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_t3 = int8_t(value_byte);
        count++;
    }

    if (Read16_Bit(NVM_PAR_P1, ADDR_I2C, &value_2bytes) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_p1 = (int16_t)value_2bytes;
        count++;
    }

    if (Read16_Bit(NVM_PAR_P2, ADDR_I2C, &value_2bytes) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_p2 = (int16_t)value_2bytes;
        count++;
    }

    if (Read8_bit(NVM_PAR_P3, ADDR_I2C, &value_byte) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_p3 = (int8_t)value_byte;
        count++;
    }

    if (Read8_bit(NVM_PAR_P4, ADDR_I2C, &value_byte) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_p4 = (int8_t)value_byte;
        count++;
    }

    if (Read16_Bit(NVM_PAR_P5, ADDR_I2C, &value_2bytes) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_p5 = value_2bytes;
        count++;
    }

    if (Read16_Bit(NVM_PAR_P6, ADDR_I2C, &value_2bytes) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_p6 = value_2bytes;
        count++;
    }

    if (Read8_bit(NVM_PAR_P7, ADDR_I2C, &value_byte) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_p7 = (int8_t)value_byte;
        count++;
    }

    if (Read8_bit(NVM_PAR_P8, ADDR_I2C, &value_byte) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_p8 = (int8_t)value_byte;
        count++;
    }

    if (Read16_Bit(NVM_PAR_P9, ADDR_I2C, &value_2bytes) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_p9 = (int16_t)value_2bytes;
        count++;
    }

    if (Read8_bit(NVM_PAR_P10, ADDR_I2C, &value_byte) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_p10 = (int8_t)value_byte;
        count++;
    }

    if (Read8_bit(NVM_PAR_P11, ADDR_I2C, &value_byte) == I2C_READING_BYTES_SUCCESS)
    {
        reg_calib_data.nvm_par_p11 = (int8_t)value_byte;
        count++;
    }

    if (count == 14)
    {
        error = GET_CALIB_DATA_SUCCESS;
    }
    return error;
}

/*!
 * @brief Obtención de los coeficientes de calibración
 */
void Get_Calib_Coefficients()
{
    if (Get_Calib_Data() == GET_CALIB_DATA_SUCCESS)
    {
        coeff.nvm_t1 = reg_calib_data.nvm_par_t1 / pow(2, -8);
        coeff.nvm_t2 = reg_calib_data.nvm_par_t2 / pow(2, 30);
        coeff.nvm_t3 = reg_calib_data.nvm_par_t3 / pow(2, 48);
        coeff.nvm_p1 = ((reg_calib_data.nvm_par_p1 - pow(2, 14)) / pow(2, 20));

        coeff.nvm_p2 = ((reg_calib_data.nvm_par_p2 - pow(2, 14)) / pow(2, 29));
        coeff.nvm_p3 = reg_calib_data.nvm_par_p3 / pow(2, 32);

        coeff.nvm_p4 = reg_calib_data.nvm_par_p4 / pow(2, 37);

        coeff.nvm_p5 = reg_calib_data.nvm_par_p5 / pow(2, -3);
        coeff.nvm_p6 = reg_calib_data.nvm_par_p6 / pow(2, 6);
        coeff.nvm_p7 = reg_calib_data.nvm_par_p7 / pow(2, 8);
        coeff.nvm_p8 = reg_calib_data.nvm_par_p8 / pow(2, 15);
        coeff.nvm_p9 = reg_calib_data.nvm_par_p9 / pow(2, 48);
        coeff.nvm_p10 = reg_calib_data.nvm_par_p10 / pow(2, 48);
        coeff.nvm_p11 = reg_calib_data.nvm_par_p11 / pow(2, 65);
    }
}

/**
 * @brief Obtención de temperatura calibrada
 *
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Calib_Temperature()
{
    SensorEnum_t error = GET_MEASURES_FAILED;
    uint32_t uncomp_temp;
    if (Get_Uncompensate_temperature(&uncomp_temp) == GET_UNCOMP_MEASURES_SUCCESS)
    {
        Write8_Flag(ADDR_I2C, REG_PWR_CNTRL, POS_TEMP, FLAG);

        float partial_data1;
        float partial_data2;

        partial_data1 = (float)(uncomp_temp - coeff.nvm_t1);

        partial_data2 = (float)(partial_data1 * coeff.nvm_t2);

        coeff.comp_temp = partial_data2 + (partial_data1 * partial_data1) * coeff.nvm_t3;

        error = GET_MEASURES_SUCCESS;
    }

    return error;
}

/**
 * @brief Obtención de la presión calibrada
 *
 * @param calib_data : parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Calib_Press(float *calib_data)
{
    SensorEnum_t error = GET_MEASURES_FAILED;
    uint32_t uncomp_press;

    if (Get_Uncompensate_Pressure(&uncomp_press) == GET_UNCOMP_MEASURES_SUCCESS)
    {
        Write8_Flag(ADDR_I2C, REG_PWR_CNTRL, POS_PRESS, FLAG);

        float partial_data1;
        float partial_data2;
        float partial_data3;
        float partial_data4;
        float partial_out1;
        float partial_out2;

        partial_data1 = coeff.nvm_p6 * coeff.comp_temp;
        partial_data2 = coeff.nvm_p7 * (pow(coeff.comp_temp, 2));
        partial_data3 = coeff.nvm_p8 * (pow(coeff.comp_temp, 3));
        partial_out1 = coeff.nvm_p5 + partial_data1 + partial_data2 + partial_data3;

        partial_data1 = coeff.nvm_p2 * coeff.comp_temp;
        partial_data2 = coeff.nvm_p3 * (pow(coeff.comp_temp, 2));
        partial_data3 = coeff.nvm_p4 * (pow(coeff.comp_temp, 3));
        partial_out2 = uncomp_press * (coeff.nvm_p1 + partial_data1 + partial_data2 + partial_data3);

        partial_data1 = pow((float)uncomp_press, 2);
        partial_data2 = coeff.nvm_p9 + coeff.nvm_p10 * coeff.comp_temp;
        partial_data3 = partial_data1 * partial_data2;
        partial_data4 = partial_data3 + ((float)pow(uncomp_press, 3)) * coeff.nvm_p11;
        *calib_data = (partial_out1 + partial_out2 + partial_data4);
        error = GET_MEASURES_SUCCESS;
    }

    return error;
}

/*************************************************** FUNCINES PÚBLICAS ***************************************************/

/**
 * @brief Inicialización del sensor
 *
 * @return SensorEnum_t error/success
 */
SensorEnum_t Init_BMP()
{
    SensorEnum_t rtrn;
    I2CEnum_t rslt = Init_I2C();
    if (rslt == I2C_SUCCESS)
    {

        Get_Calib_Data();
        Get_Calib_Coefficients();
        Write8_Flag(ADDR_I2C, REG_PWR_CNTRL, 4, 1);
        Write8_Flag(ADDR_I2C, REG_PWR_CNTRL, 5, 1);
        rtrn = INIT_SENSOR_SUCCESS;
    }
    else
    {
        rtrn = INIT_SENSOR_FAILED;
    }

    return rtrn;
}

/**
 * @brief Obtención de temperatura
 *
 * @param temp : parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Temp(float *temp)
{

    SensorEnum_t error = GET_TEMP_FAILED;
    if (Get_Calib_Temperature() == GET_MEASURES_SUCCESS)
    {
        *temp = coeff.comp_temp;
        error = GET_TEMP_SUCCESS;
    }
    return error;
}

/**
 * @brief Obtención de la presión
 *
 * @param press : parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Press(float *press)
{
    float temp;
    SensorEnum_t get_temp = Get_Temp(&temp);
    float data;
    SensorEnum_t error = GET_PRESS_FAILED;
    if (Get_Calib_Press(&data) == GET_MEASURES_SUCCESS)
    {
        *press = data;
        error = GET_PRESS_SUCCESS;
    }
    return error;
}

/**
 * @brief Seteo de oversampling
 *
 * @param ovrs_p : oversampling elegido para la presión
 * @param ovrs_t : oversampling elegido para la temperatura
 * @return SensorEnum_t error/success
 */
SensorEnum_t Set_Oversampling(uint8_t ovrs_p, uint8_t ovrs_t) // The “OSR” register controls the oversampling settings for pressure and temperature measurements.
{
    SensorEnum_t error = SET_OVERSAMPLING_FAILED;
    uint8_t data;
    if (Read8_bit(REG_OSR, ADDR_I2C, &data) == I2C_READING_BYTES_SUCCESS)
    {
        uint8_t byte = data;
        byte = byte | ovrs_p | ovrs_t << 3;
        Write8_bit(ADDR_I2C, REG_OSR, byte);
        error = SET_OVERSAMPLING_SUCCESS;
    }
    return error;
}

/**
 * @brief Obtener oversampling
 *
 * @param rslt : parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Oversampling(uint8_t *rslt)
{
    uint8_t data;
    SensorEnum_t error = GET_OVERSAMPLING_FAILED;
    if (Read8_bit(REG_OSR, ADDR_I2C, &data) == I2C_READING_BYTES_SUCCESS)
    {
        *rslt = data;
        error = GET_OVERSAMPLING_SUCCESS;
    }

    return error;
}

/**
 * @brief sete de filtro
 *
 * @param filter : filtro elegido
 * @return SensorEnum_t error/success
 */
SensorEnum_t Set_IRR_Filter(uint8_t filter) // The “CONFIG” register controls the IIR filter coefficients.
{
    uint8_t data;
    SensorEnum_t error = SET_IRR_FILTER_FAILED;
    if (Read8_bit(REG_CONFIG, ADDR_I2C, &data) == I2C_READING_BYTES_SUCCESS)
    {
        uint8_t byte = data;
        byte = byte | filter << 1;
        Write8_bit(ADDR_I2C, REG_CONFIG, byte);
        error = SET_IRR_FILTER_SUCCESS;
    }
    return error;
}

/**
 * @brief obtener filtro
 *
 * @param rslt : parametro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_IRR_Filter(uint8_t *rslt)
{
    uint8_t data;
    SensorEnum_t error = GET_IRR_FILTER_FAILED;
    if (Read8_bit(REG_CONFIG, ADDR_I2C, &data) == I2C_READING_BYTES_SUCCESS)
    {
        *rslt = data;
        error = GET_IRR_FILTER_SUCCESS;
    }
    return error;
}

/**
 * @brief seteo de ODR
 *
 * @param rate : elección del ODR
 * @return SensorEnum_t error/success
 */
SensorEnum_t Set_Output_Data_Rate(uint8_t rate) // The “ODR” register set the configuration of the output data rates by means of setting the 36ubdivision/subsampling. Hz
{
    uint8_t data;
    SensorEnum_t error = SET_ODR_FAILED;

    if (Read8_bit(REG_ODR, ADDR_I2C, &data) == I2C_READING_BYTES_SUCCESS)
    {
        uint8_t byte = data;
        byte = byte | rate;
        Write8_bit(ADDR_I2C, REG_ODR, byte);
        error = SET_ODR_SUCCESS;
    }
    return error;
}

/**
 * @brief obtención de ODR
 *
 * @param rslt : Parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Output_Data_Rate(uint8_t *rslt)
{
    uint8_t data;
    SensorEnum_t error = GET_ODR_FAILED;
    if (Read8_bit(REG_ODR, ADDR_I2C, &data) == I2C_READING_BYTES_SUCCESS)
    {
        *rslt = data;
        error = GET_ODR_SUCCESS;
    }

    return error;
}
