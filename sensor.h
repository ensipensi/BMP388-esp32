#include "Arduino.h"
#include "def.h"

/**
 * @brief Inicialización del sensor
 *
 * @return SensorEnum_t error/success
 */
SensorEnum_t Init_BMP();

/**
 * @brief Obtención de la presión
 *
 * @param press : parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Press(float *rslt);

/**
 * @brief Seteo de oversampling
 *
 * @param ovrs_p : oversampling elegido para la presión
 * @param ovrs_t : oversampling elegido para la temperatura
 * @return SensorEnum_t error/success
 */
SensorEnum_t Set_Oversampling(uint8_t ovrs_p, uint8_t ovrs_t);

/**
 * @brief sete de filtro
 * 
 * @param filter : filtro elegido
 * @return SensorEnum_t error/success
 */
SensorEnum_t Set_IRR_Filter(uint8_t filter);

/**
 * @brief seteo de ODR
 * 
 * @param rate : elección del ODR
 * @return SensorEnum_t error/success
 */
SensorEnum_t Set_Output_Data_Rate(uint8_t rate);

/**
 * @brief Obtener oversampling
 * 
 * @param rslt : parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Oversampling(uint8_t *rslt);

/**
 * @brief obtener filtro
 * 
 * @param rslt : parametro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_IRR_Filter(uint8_t *rslt);

/**
 * @brief obtención de ODR
 * 
 * @param rslt : Parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Output_Data_Rate(uint8_t *rslt);

/**
 * @brief Obtención de temperatura
 *
 * @param temp : parámetro de salida
 * @return SensorEnum_t error/success
 */
SensorEnum_t Get_Temp(float *data);
