/*
 *  Copyright (c) 2021, PACKETCRAFT, INC.
 *
 *  SPDX-License-Identifier: LicenseRef-PCFT
 */

#include "audio_spi.h"

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/spi.h>

#define MY_SPI_MASTER DT_NODELABEL(my_spi_master)

#define MY_SPI_SLAVE  DT_NODELABEL(my_spi_slave)

// SPI master functionality
const struct device *spi_dev;
static struct k_poll_signal spi_done_sig = K_POLL_SIGNAL_INITIALIZER(spi_done_sig);

struct spi_cs_control spim_cs = {
	.gpio = SPI_CS_GPIOS_DT_SPEC_GET(DT_NODELABEL(reg_my_spi_master)),
	.delay = 0,
};

void spi_init(void)
{
	spi_dev = DEVICE_DT_GET(MY_SPI_MASTER);
	if(!device_is_ready(spi_dev)) {
		printk("SPI master device not ready!\n");
	}
	if(!device_is_ready(spim_cs.gpio.port)){
		printk("SPI master chip select device not ready!\n");
	}
}

// SPI slave functionality
const struct device *spi_slave_dev;
static struct k_poll_signal spi_slave_done_sig = K_POLL_SIGNAL_INITIALIZER(spi_slave_done_sig);

static const struct spi_config spi_slave_cfg = {
	.operation = SPI_WORD_SET(8) | SPI_TRANSFER_MSB |
				 SPI_MODE_CPOL | SPI_MODE_CPHA | SPI_OP_MODE_SLAVE,
	.frequency = 4000000,
	.slave = 0,
};

void spi_slave_init(void)
{
	spi_slave_dev = DEVICE_DT_GET(MY_SPI_SLAVE);
	if(!device_is_ready(spi_dev)) {
		printk("SPI slave device not ready!\n");
	}
}

static uint8_t slave_tx_buffer[2];
static uint8_t slave_rx_buffer[2];
static int spi_slave_write_test_msg(void)
{
	static uint8_t counter = 0;


	const struct spi_buf s_tx_buf = {
		.buf = slave_tx_buffer,
		.len = sizeof(slave_tx_buffer)
	};
	const struct spi_buf_set s_tx = {
		.buffers = &s_tx_buf,
		.count = 1
	};

	struct spi_buf s_rx_buf = {
		.buf = slave_rx_buffer,
		.len = sizeof(slave_rx_buffer),
	};
	const struct spi_buf_set s_rx = {
		.buffers = &s_rx_buf,
		.count = 1
	};

	// Update the TX buffer with a rolling counter
	slave_tx_buffer[1] = counter++;
	printk("SPI SLAVE TX: 0x%.2x, 0x%.2x\n", slave_tx_buffer[0], slave_tx_buffer[1]);

	// Reset signal
	k_poll_signal_reset(&spi_slave_done_sig);
	
	// Start transaction
	int error = spi_transceive_async(spi_slave_dev, &spi_slave_cfg, &s_tx, &s_rx, &spi_slave_done_sig);
	if(error != 0){
		printk("SPI slave transceive error: %i\n", error);
		return error;
	}
	return 0;
}

static int spi_slave_check_for_message(void)
{
	int signaled, result;
	k_poll_signal_check(&spi_slave_done_sig, &signaled, &result);
	if(signaled != 0){
		return 0;
	}
	else return -1;
}

void audio_spi_init(void)
{
	spi_init();

	spi_slave_init();

	printk("SPI master/slave example started\n");
	
	spi_slave_write_test_msg();

	while (1) {
		if(spi_slave_check_for_message() == 0){
			// Print the last received data
			printk("SPI SLAVE RX: 0x%.2x, 0x%.2x\n", slave_rx_buffer[0], slave_rx_buffer[1]);
			
			// Prepare the next SPI slave transaction
			spi_slave_write_test_msg();
		}
	}
}