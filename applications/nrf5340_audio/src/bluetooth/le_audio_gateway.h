/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _LE_AUDIO_GATEWAY_H_
#define _LE_AUDIO_GATEWAY_H_

/**
 * @brief Generic function for a user defined button press
 *
 * @param action	User defined action
 *
 * @return	0 for success,
 *		error otherwise
 */
int le_audio_user_defined_button_press_gateway(enum le_audio_user_defined_action action);

/**
 * @brief Get configuration for audio stream
 *
 * @param bitrate	Pointer to bitrate used
 * @param sampling_rate	Pointer to sampling rate used
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_config_get_gateway(uint32_t *bitrate, uint32_t *sampling_rate);

/**
 * @brief	Increase volume by one step
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_volume_up_gateway(void);

/**
 * @brief	Decrease volume by one step
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_volume_down_gateway(void);

/**
 * @brief	Mute volume
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_volume_mute_gateway(void);

/**
 * @brief	Either resume or pause the Bluetooth LE Audio stream,
 *		depending on the current state of the stream
 *
 * @return	0 for success, error otherwise
 */
int le_audio_play_pause_gateway(void);

/**
 * @brief Send Bluetooth LE Audio data
 *
 * @param enc_audio	Encoded audio struct
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_send_gateway(struct encoded_audio enc_audio);

/**
 * @brief Enable Bluetooth LE Audio
 *
 * @param recv_cb	Callback for receiving Bluetooth LE Audio data
 *
 * @return		0 for success, error otherwise
 */
int le_audio_enable_gateway(le_audio_receive_cb recv_cb);

/**
 * @brief Disable Bluetooth LE Audio
 *
 * @return	0 for success, error otherwise
 */
int le_audio_disable_gateway(void);

#endif /* _LE_AUDIO_GATEWAY_H_ */
