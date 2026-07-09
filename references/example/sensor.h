/**
 * Copyright (c) 2026 Your Name
 * SPDX-License-Identifier: MIT
 */

/**
 * \file
 * \brief I2C temperature sensor driver
 *
 * \internal
 * \par modification history
 * - 1.00 26-07-09  dev, first implementation
 * \endinternal
 */

#ifndef __SENSOR_H__
#define __SENSOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* --- public types ---------------------------------------------------- */

typedef enum
{
        SENSOR_OK          = 0,
        SENSOR_ERR_BUS     = 1,
        SENSOR_ERR_CRC     = 2,
        SENSOR_ERR_TIMEOUT = 3,
} sensor_err_t;

/** \brief sensor calibration data */
enum
{
        SENSOR_CAL_ADDR    = 0x30,  /**< \brief calibration register address */
        SENSOR_CAL_MAGIC   = 0xA5,  /**< \brief expected magic byte */
        SENSOR_MAX_RETRIES = 3,     /**< \brief max I2C retries */
};

struct sensor;
struct i2c_bus;

/* --- public API ------------------------------------------------------ */

/**
 * \brief Initialise sensor and run calibration check
 *
 * \param[in] p_bus    I2C bus the sensor is on
 * \param[in] addr     7-bit I2C address
 * \param[out] pp_dev  returns pointer to allocated sensor handle
 *
 * \return SENSOR_OK on success, sensor_err_t on failure
 */
int sensor_init(struct i2c_bus *p_bus, uint8_t addr, struct sensor **pp_dev);

/**
 * \brief Read current temperature
 *
 * \param[in]  p_dev    sensor handle
 * \param[out] p_mc_out temperature in millidegrees Celsius (e.g. 23450 =
 *                      23.450 °C)
 *
 * \return SENSOR_OK on success, sensor_err_t on failure
 */
int sensor_read(struct sensor *p_dev, int32_t *p_mc_out);

/**
 * \brief Check whether the last read succeeded
 *
 * \param[in] p_dev  sensor handle
 *
 * \return true if sensor is healthy
 */
bool sensor_is_ok(const struct sensor *p_dev);

/**
 * \brief Release sensor handle
 *
 * \param[in] p_dev  sensor handle (may be NULL)
 */
void sensor_deinit(struct sensor *p_dev);

/* --- pure helpers (testable without hardware) ------------------------ */

/**
 * \brief Convert two raw register bytes to temperature
 *
 * \param[in] hi  high byte (MSB)
 * \param[in] lo  low byte (LSB)
 *
 * \return temperature in millidegrees Celsius
 */
int32_t sensor_raw_to_temp(uint8_t hi, uint8_t lo);

/**
 * \brief Compute CRC-8 over a buffer
 *
 * \param[in] p_data  data bytes
 * \param[in] len     number of bytes
 *
 * \return 8-bit CRC
 */
uint8_t sensor_crc8(const uint8_t *p_data, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_H__ */
