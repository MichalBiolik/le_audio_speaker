/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _AUDIO_SPI_H_
#define _AUDIO_SPI_H_

/**
 * @brief Set fifo buffers to be used by USB module and start sending/receiving data
 *
 * @param fifo_tx_in  Pointer to fifo structure for tx
 * @param fifo_rx_in  Pointer to fifo structure for rx
 *
 * @return 0 if successful, error otherwise
 */
void audio_spi_start(struct data_fifo *fifo_tx_in, struct data_fifo *fifo_rx_in);

/**
 * @brief Stop sending/receiving data
 *
 * @note The USB device will still be running, but all data sent to
 *       it will be discarded
 */
void audio_spi_stop(void);

/**
 * @brief Stop and disable USB device
 *
 * @return 0 if successful, error otherwise
 */
void audio_spi_disable(void);

/**
 * @brief Register and enable USB device
 *
 * @return 0 if successful, error otherwise
 */
void audio_spi_init(void);

#endif /* _AUDIO_SPI_H_ */
