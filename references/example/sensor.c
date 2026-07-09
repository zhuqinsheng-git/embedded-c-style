/**
 * Copyright (c) 2026 Your Name
 * SPDX-License-Identifier: MIT
 */

/**
 * \file
 * \brief I2C temperature sensor driver — implementation
 *
 * \internal
 * \par modification history
 * - 1.00 26-07-09  dev, first implementation
 * \endinternal
 */

#include "sensor.h"
#include <stdlib.h>

/* --- hardware stub (replace with real I2C driver) --------------------- */

/**
 * \brief Read bytes from sensor register (hardware stub)
 *
 * In a real project this calls the platform I2C driver.
 * The stub returns canned data so pure logic can be tested.
 */
static int __i2c_reg_read(struct i2c_bus *p_bus, uint8_t dev_addr,
                          uint8_t reg, uint8_t *p_buf, size_t len)
{
        (void)p_bus;
        (void)dev_addr;
        (void)reg;

        /*
         * Stub: return fixed pattern so pure functions downstream
         * get real-looking data.  Replace with i2c_read() in production.
         */
        if (len > 0)
                p_buf[0] = 0x0A;       /* MSB of 0x0ACD = 2765 */
        if (len > 1)
                p_buf[1] = 0xCD;       /* LSB */

        return 0;
}

/* --- sensor data ------------------------------------------------------ */

struct sensor
{
        struct i2c_bus *p_bus;          /**< \brief I2C bus handle */
        uint8_t         addr;           /**< \brief 7-bit device address */
        bool            healthy;        /**< \brief last read OK */
};

/* --- internal helpers ------------------------------------------------- */

/**
 * \brief Check calibration register matches expected magic value
 *
 * \param[in] p_dev  sensor handle
 *
 * \return 0 if calibration is valid, error code otherwise
 */
static int __check_calibration(const struct sensor *p_dev)
{
        uint8_t magic;

        int ret = __i2c_reg_read(p_dev->p_bus, p_dev->addr,
                                 SENSOR_CAL_ADDR, &magic, 1);
        if (ret != 0)
                return SENSOR_ERR_BUS;

        if (magic != SENSOR_CAL_MAGIC)
                return -1;

        return 0;
}

/**
 * \brief Read raw temperature register pair
 *
 * \param[in]  p_dev         sensor handle
 * \param[out] p_hi_out      high byte
 * \param[out] p_lo_out      low byte
 * \param[out] p_crc8_out    CRC byte from sensor
 *
 * \return 0 on success, error code on failure
 */
static int __read_raw(const struct sensor *p_dev,
                      uint8_t *p_hi_out, uint8_t *p_lo_out, uint8_t *p_crc8_out)
{
        uint8_t buf[3];
        int ret = 0;

        for (int attempt = 0; attempt < SENSOR_MAX_RETRIES; attempt++)
        {
                ret = __i2c_reg_read(p_dev->p_bus, p_dev->addr, 0x00, buf, 3);
                if (ret == 0)
                        break;
        }

        if (ret != 0)
                return SENSOR_ERR_TIMEOUT;

        *p_hi_out   = buf[0];
        *p_lo_out   = buf[1];
        *p_crc8_out = buf[2];
        return 0;
}

/**
 * \brief Read raw values and verify CRC
 *
 * \param[in]  p_dev      sensor handle
 * \param[out] p_hi_out   high byte
 * \param[out] p_lo_out   low byte
 *
 * \return 0 on success, error code on failure
 */
static int __read_verified(const struct sensor *p_dev,
                           uint8_t *p_hi_out, uint8_t *p_lo_out)
{
        uint8_t hi, lo, crc;

        int ret = __read_raw(p_dev, &hi, &lo, &crc);
        if (ret != 0)
                return ret;

        uint8_t buf[2] = {hi, lo};
        if (sensor_crc8(buf, 2) != crc)
                return SENSOR_ERR_CRC;

        *p_hi_out = hi;
        *p_lo_out = lo;
        return 0;
}

/* --- public API ------------------------------------------------------- */

int sensor_init(struct i2c_bus *p_bus, uint8_t addr, struct sensor **pp_dev)
{
        if (!p_bus || !pp_dev)
                return -1;

        struct sensor *p_dev = malloc(sizeof(*p_dev));
        if (!p_dev)
                return -2;

        p_dev->p_bus   = p_bus;
        p_dev->addr    = addr;
        p_dev->healthy = false;

        int ret = __check_calibration(p_dev);
        if (ret != 0)
                goto err_free;

        p_dev->healthy = true;
        *pp_dev = p_dev;
        return 0;

err_free:
        free(p_dev);
        return ret;
}

int sensor_read(struct sensor *p_dev, int32_t *p_mc_out)
{
        if (!p_dev || !p_mc_out)
                return -1;

        uint8_t hi, lo;

        int ret = __read_verified(p_dev, &hi, &lo);
        if (ret != 0)
        {
                p_dev->healthy = false;
                return ret;
        }

        *p_mc_out = sensor_raw_to_temp(hi, lo);
        p_dev->healthy = true;
        return 0;
}

bool sensor_is_ok(const struct sensor *p_dev)
{
        return p_dev && p_dev->healthy;
}

void sensor_deinit(struct sensor *p_dev)
{
        free(p_dev);
}

/* --- pure helpers (testable without hardware) ------------------------- */

int32_t sensor_raw_to_temp(uint8_t hi, uint8_t lo)
{
        int16_t raw = (int16_t)((uint16_t)hi << 8 | lo);
        return (int32_t)raw * 625 / 10;     /* 0.0625 °C LSB → millidegrees */
}

/*
 * CRC-8 with polynomial 0x07 (x^8 + x^2 + x + 1).
 * Same algorithm used by TMP117 and many other I2C sensors.
 */
uint8_t sensor_crc8(const uint8_t *p_data, size_t len)
{
        uint8_t crc = 0x00;

        for (size_t i = 0; i < len; i++)
        {
                crc ^= p_data[i];
                for (int b = 0; b < 8; b++)
                {
                        if (crc & 0x80)
                                crc = (uint8_t)(crc << 1) ^ 0x07;
                        else
                                crc = (uint8_t)(crc << 1);
                }
        }

        return crc;
}
