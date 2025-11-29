// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2023 Rene Wolf
// Copyright (c) 2024 namazso <admin@namazso.eu>

#include "clock_gen.h"

#include <hardware/clocks.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>

#define adc_rate_40mhz 78125

#define CLOCK_PIN 21

bool clock_gen_init()
{
    gpio_set_dir(CLOCK_PIN, true);
    //set_sys_clock_khz(120000, true);
    // Rather than underclock the pico, slightly overclock to 160MHz (up to 200Mhz is officially supported)
    set_sys_clock_khz(160000, true);
    
    // To help keep a stable clock on longer lines, increase GPIO drive strength from 4ma to 8ma
    //gpio_set_drive_strength(CLOCK_PIN, GPIO_DRIVE_STRENGTH_8MA);
    
    // Then, divide by 4 instead of 3 to achieve an even 40MHz
    //clock_gpio_init_int_frac(CLOCK_PIN, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_SYS, 3, 0);
    clock_gpio_init_int_frac(CLOCK_PIN, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_SYS, 4, 0);
    return true;
}

void clock_gen_default()
{
        return;
}


static const uint32_t adc_rates[] = { adc_rate_40mhz };

const uint32_t* clock_gen_get_adc_sample_rate_options(uint8_t* len)
{
	// https://www.scaler.com/topics/length-of-an-array-in-c/
	*len = sizeof(adc_rates) / sizeof(adc_rates[0]);
	return adc_rates;
}

uint32_t clock_gen_get_adc_sample_rate()
{
        return adc_rate_40mhz;
}

void clock_gen_set_adc_sample_rate(uint32_t rate_hz)
{
}

#undef adc_rate_40mhz
