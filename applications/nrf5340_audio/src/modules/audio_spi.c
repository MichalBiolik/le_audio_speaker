// /*
//  * Copyright (c) 2018 Nordic Semiconductor ASA
//  *
//  * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
//  */

// #include "audio_spi.h"

// // #include <zephyr.h>
// // #include <device.h>
// #include "nrfx_spis.h"

// #include <zephyr/logging/log.h>

// #include "audio_datapath.h"
// #include "audio_sync_timer.h"

// LOG_MODULE_REGISTER(audio_spi, 3);

// // static nrfx_spis_config_t spi_config = NRFX_SPIS_DEFAULT_CONFIG(10, 11, 12, 13); // _pin_sck, _pin_mosi, _pin_miso, _pin_csn




// // #define SPI_DEVICE_NAME "SPI_0"  // Replace with your SPI device name
// // #define RX_BUFFER_SIZE 4096       // Size of the receive buffer

// // K_SEM_DEFINE(rx_sem, 0, 1);  // Semaphore to signal data reception

// // static uint8_t rx_buffer[RX_BUFFER_SIZE] = {0};  // Buffer to store received data

// // void spi_event_handler(const struct device *spi_dev, int event)
// // {
// //     if (event == SPI_EVENT_RX_READY) {
// //         struct spi_buf rx_buf = {
// //             .buf = rx_buffer,
// //             .len = RX_BUFFER_SIZE
// //         };

// //         struct spi_buf_set rx_bufs = {
// //             .buffers = &rx_buf,
// //             .count = 1
// //         };

// //         // Read the received data using interrupts
// //         spi_transceive_async(spi_dev, &spi_cfg, &rx_bufs, spi_event_handler);

// //     } else if (event == SPI_EVENT_TRANSFER_COMPLETE) {
// //         // Data reception is complete, process the received data
// //         printk("Received data: ");
// //         for (int i = 0; i < RX_BUFFER_SIZE; i++) {
// //             printk("%02X ", rx_buffer[i]);
// //         }
// //         printk("\n");

// //         k_sem_give(&rx_sem);  // Release the semaphore to signal data reception
// //     }
// // }

// // void audio_spi_init(void)
// // {
// //     const struct device *spi_dev;

// //     spi_dev = device_get_binding(SPI_DEVICE_NAME);
// //     if (!spi_dev) {
// //         printk("SPI device not found\n");
// //         return;
// //     }

// //     // Additional SPI configuration can be done here, such as frequency and mode
// //     struct spi_config spi_cfg = {
// //         .frequency = SPI_FREQUENCY_1M,        // Set the SPI frequency to 1 MHz (adjust as needed)
// //         .operation = (SPI_OP_MODE_MASTER |     // Set SPI as master
// //                       SPI_TRANSFER_MSB |      // MSB-first transfer
// //                       SPI_WORD_SET(8)),       // Use 8-bit word size
// //         .cs = NULL                             // The Chip Select (CS) pin will be handled manually
// //     };

// //     if (spi_configure(spi_dev, &spi_cfg) < 0) {
// //         printk("SPI configuration failed\n");
// //         return;
// //     }

// //     struct spi_buf rx_buf = {
// //         .buf = rx_buffer,
// //         .len = RX_BUFFER_SIZE
// //     };

// //     struct spi_buf_set rx_bufs = {
// //         .buffers = &rx_buf,
// //         .count = 1
// //     };

// //     // Start the first SPI transfer using interrupts
// //     spi_transceive_async(spi_dev, &spi_cfg, &rx_bufs, spi_event_handler);
// // }


// // void audio_spi_init(void)
// // {
// //     nrfx_spis_init
// // }


// /** @brief Symbol specifying SPIS instance to be used. */
// #define SPIS_INST_IDX 2

// /** @brief Symbol specifying slave's pin number for MOSI. */
// #define MOSI_PIN_SLAVE 5

// /** @brief Symbol specifying slave's pin number for MISO. */
// #define MISO_PIN_SLAVE 6

// /** @brief Symbol specifying slave's pin number for SCK. */
// #define SCK_PIN_SLAVE 7

// /** @brief Symbol specifying slave's pin number for CSN. */
// #define CSN_PIN_SLAVE 8

// /** @brief Symbol specifying message to be sent via SPIM data transfer. */
// #define MSG_TO_SEND_MASTER "Semiconductor"

// /** @brief Symbol specifying message to be sent via SPIS data transfer. */
// #define MSG_TO_SEND_SLAVE "Nordic"

// /** @brief Transmit buffer initialized with the specified message ( @ref MSG_TO_SEND_SLAVE ). */
// static uint8_t m_tx_buffer_slave[2048];

// /** @brief Receive buffer defined with the size to store specified message ( @ref MSG_TO_SEND_MASTER ). */
// static uint8_t m_rx_buffer_slave[2048];


// /**
//  * @brief Function for handling SPIS driver events.
//  *
//  * @param[in] p_event   Pointer to the SPIS driver event.
//  * @param[in] p_context Pointer to the context passed from the driver.
//  */
// static void spis_handler(nrfx_spis_evt_t const * p_event, void * p_context)
// {
//     if (p_event->evt_type == NRFX_SPIS_XFER_DONE)
//     {
//         char * p_msg = p_context;
//         LOG_INF("SPIS finished. Context passed to the handler: >%s<", p_msg);
//         LOG_INF("SPIS rx buffer: %s", m_rx_buffer_slave);
//     }
// }

// void audio_spi_init(void)
// {
//     nrfx_err_t status;
//     (void)status;

//     LOG_INF("Starting nrfx_spim_spis basic non-blocking example.");

//     NRFX_ASSERT(status == NRFX_SUCCESS);

//     nrfx_spis_t spis_inst = NRFX_SPIS_INSTANCE(SPIS_INST_IDX);
//     nrfx_spis_config_t spis_config = NRFX_SPIS_DEFAULT_CONFIG(SCK_PIN_SLAVE,
//                                                               MOSI_PIN_SLAVE,
//                                                               MISO_PIN_SLAVE,
//                                                               CSN_PIN_SLAVE);

//     status = nrfx_spis_init(&spis_inst, &spis_config, spis_handler, NULL);
//     NRFX_ASSERT(status == NRFX_SUCCESS);

// #if defined(__ZEPHYR__)
//     IRQ_DIRECT_CONNECT(NRFX_IRQ_NUMBER_GET(NRF_SPIS_INST_GET(SPIS_INST_IDX)), IRQ_PRIO_LOWEST,
//                        NRFX_SPIS_INST_HANDLER_GET(SPIS_INST_IDX), 0);
// #endif

//     status = nrfx_spis_buffers_set(&spis_inst,
//                                    m_tx_buffer_slave, sizeof(m_tx_buffer_slave),
//                                    m_rx_buffer_slave, sizeof(m_rx_buffer_slave));
//     // NRFX_ASSERT(status == NRFX_SUCCESS);

//     // nrfx_spim_xfer_desc_t spim_xfer_desc = NRFX_SPIM_XFER_TRX(m_tx_buffer_master,
//     //                                                           sizeof(m_tx_buffer_master),
//     //                                                           m_rx_buffer_master,
//     //                                                           sizeof(m_rx_buffer_master));

//     // status = nrfx_spim_xfer(&spim_inst, &spim_xfer_desc, 0);
//     // NRFX_ASSERT(status == NRFX_SUCCESS);
// }