/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _LE_AUDIO_HEADSET_H_
#define _LE_AUDIO_HEADSET_H_

#include "le_audio.h"

/**
 * @brief Generic function for a user defined button press
 *
 * @param action	User defined action
 *
 * @return	0 for success,
 *		error otherwise
 */
int le_audio_user_defined_button_press_headset(enum le_audio_user_defined_action action);

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
int le_audio_config_get_headset(uint32_t *bitrate, uint32_t *sampling_rate);

/**
 * @brief	Increase volume by one step
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_volume_up_headset(void);

/**
 * @brief	Decrease volume by one step
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_volume_down_headset(void);

/**
 * @brief	Mute volume
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_volume_mute_headset(void);

/**
 * @brief	Either resume or pause the Bluetooth LE Audio stream,
 *		depending on the current state of the stream
 *
 * @return	0 for success, error otherwise
 */
int le_audio_play_pause_headset(void);

/**
 * @brief Send Bluetooth LE Audio data
 *
 * @param enc_audio	Encoded audio struct
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_send_headset(struct encoded_audio enc_audio);

/**
 * @brief Enable Bluetooth LE Audio
 *
 * @param recv_cb	Callback for receiving Bluetooth LE Audio data
 *
 * @return		0 for success, error otherwise
 */
int le_audio_enable_headset(le_audio_receive_cb recv_cb);

/**
 * @brief Disable Bluetooth LE Audio
 *
 * @return	0 for success, error otherwise
 */
int le_audio_disable_headset(void);

#endif /* _LE_AUDIO_HEADSET_H_ */
