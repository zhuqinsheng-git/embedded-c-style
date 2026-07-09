/**
 * Copyright (c) 2026 Your Name
 * SPDX-License-Identifier: MIT
 */

/**
 * \file
 * \brief Unit tests for sensor module — pure functions only, no hardware
 *
 * \internal
 * \par modification history
 * - 1.00 26-07-09  dev, first implementation
 * \endinternal
 */

#include "sensor.h"
#include <assert.h>
#include <stdio.h>

/* --- sensor_raw_to_temp ------------------------------------------------ */

static void test_raw_to_temp_positive(void)
{
        /* 0x0ACD = 2765 raw → 2765 * 0.0625 = 172.8125 °C → 172812 m°C */
        int32_t mc = sensor_raw_to_temp(0x0A, 0xCD);
        assert(mc == 172812);
        printf("  PASS: raw_to_temp_positive\n");
}

static void test_raw_to_temp_zero(void)
{
        assert(sensor_raw_to_temp(0x00, 0x00) == 0);
        printf("  PASS: raw_to_temp_zero\n");
}

static void test_raw_to_temp_negative(void)
{
        /* 0x8000 = -32768 raw → -2048.0 °C → -2048000 m°C */
        assert(sensor_raw_to_temp(0x80, 0x00) == -2048000);
        printf("  PASS: raw_to_temp_negative\n");
}

/* --- sensor_crc8 ------------------------------------------------------- */

static void test_crc8_known_vector(void)
{
        /* CRC-8 of {0x00, 0x00} should be 0x00 */
        uint8_t data[] = {0x00, 0x00};
        assert(sensor_crc8(data, 2) == 0x00);
        printf("  PASS: crc8_zero_data\n");
}

static void test_crc8_non_zero(void)
{
        /* CRC-8 of {0x0A, 0xCD}: verify it's not trivially zero */
        uint8_t data[] = {0x0A, 0xCD};
        uint8_t crc = sensor_crc8(data, 2);
        assert(crc != 0x00);
        printf("  PASS: crc8_non_zero (crc=0x%02X)\n", crc);
}

static void test_crc8_detects_error(void)
{
        uint8_t good[] = {0x0A, 0xCD};
        uint8_t bad[]  = {0x0A, 0xCE};    /* one bit flipped */

        assert(sensor_crc8(good, 2) != sensor_crc8(bad, 2));
        printf("  PASS: crc8_detects_single_bit_error\n");
}

static void test_crc8_idempotent(void)
{
        uint8_t data[] = {0x12, 0x34, 0x56};

        uint8_t a = sensor_crc8(data, 3);
        uint8_t b = sensor_crc8(data, 3);
        assert(a == b);
        printf("  PASS: crc8_idempotent\n");
}

/* --- sensor_is_ok ------------------------------------------------------ */

static void test_is_ok_null(void)
{
        assert(!sensor_is_ok(NULL));
        printf("  PASS: is_ok_null\n");
}

/* --- runner ------------------------------------------------------------ */

int main(void)
{
        printf("sensor_test:\n");

        printf("  sensor_raw_to_temp:\n");
        test_raw_to_temp_positive();
        test_raw_to_temp_zero();
        test_raw_to_temp_negative();

        printf("  sensor_crc8:\n");
        test_crc8_known_vector();
        test_crc8_non_zero();
        test_crc8_detects_error();
        test_crc8_idempotent();

        printf("  sensor_is_ok:\n");
        test_is_ok_null();

        printf("\nAll tests passed.\n");
        return 0;
}
