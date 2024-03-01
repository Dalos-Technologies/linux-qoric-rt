// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright 2024 NXP
 */

#ifndef _QORIQ_THERMAL_INTERRUPT_
#define _QORIQ_THERMAL_INTERRUPT_

/**
 * @brief : Function to get current temperature
 *
 * @return : Max temp of all monitoring site
 */
int imx8mm_get_temp(int *temp, uint32_t sensor_id);
#endif
