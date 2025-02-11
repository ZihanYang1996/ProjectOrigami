#pragma once

extern "C" {
	void StartAudioCapture();
	void StopAudioCapture();
	float GetMicVolume();
}