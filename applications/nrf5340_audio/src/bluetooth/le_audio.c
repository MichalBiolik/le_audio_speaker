#include "le_audio.h"
#include "le_audio_headset.h"
#include "le_audio_gateway.h"

extern uint8_t config_audio_dev_var;

int le_audio_user_defined_button_press(enum le_audio_user_defined_action action)
{
	if (config_audio_dev_var == GATEWAY)
	{
		return le_audio_user_defined_button_press_gateway(action);
	}
	else
	{
		return le_audio_user_defined_button_press_headset(action);
	}
}

int le_audio_config_get(uint32_t *bitrate, uint32_t *sampling_rate)
{
	if (config_audio_dev_var == GATEWAY)
	{
		return le_audio_config_get_gateway(bitrate, sampling_rate);
	}
	else
	{
		return le_audio_config_get_headset(bitrate, sampling_rate);
	}
}

int le_audio_volume_up(void)
{
	if (config_audio_dev_var == GATEWAY)
	{
		return le_audio_volume_up_gateway();
	}
	else
	{
		return le_audio_volume_up_headset();
	}
}

int le_audio_volume_down(void)
{
	if (config_audio_dev_var == GATEWAY)
	{
		return le_audio_volume_down_gateway();
	}
	else
	{
		return le_audio_volume_down_headset();
	}
}

int le_audio_volume_mute(void)
{
	if (config_audio_dev_var == GATEWAY)
	{
		return le_audio_volume_mute_gateway();
	}
	else
	{
		return le_audio_volume_mute_headset();
	}
}

int le_audio_play_pause(void)
{
	if (config_audio_dev_var == GATEWAY)
	{
		return le_audio_play_pause_gateway();
	}
	else
	{
		return le_audio_play_pause_headset();
	}
}

int le_audio_send(struct encoded_audio enc_audio)
{
	if (config_audio_dev_var == GATEWAY)
	{
		return le_audio_send_gateway(enc_audio);
	}
	else
	{
		return le_audio_send_headset(enc_audio);
	}
}

int le_audio_enable(le_audio_receive_cb recv_cb)
{
	if (config_audio_dev_var == GATEWAY)
	{
		return le_audio_enable_gateway(recv_cb);
	}
	else
	{
		return le_audio_enable_headset(recv_cb);
	}
}

int le_audio_disable(void)
{
	if (config_audio_dev_var == GATEWAY)
	{
		return le_audio_disable_gateway();
	}
	else
	{
		return le_audio_disable_headset();
	}
}
