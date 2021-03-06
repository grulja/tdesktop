/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/widgets/continuous_sliders.h"

namespace Media {
namespace Player {
struct TrackState;
} // namespace Player

namespace View {

class PlaybackProgress {
public:
	PlaybackProgress();

	void setValueChangedCallback(Fn<void(float64,float64)> callback) {
		_valueChanged = std::move(callback);
	}
	void setInLoadingStateChangedCallback(Fn<void(bool)> callback) {
		_inLoadingStateChanged = std::move(callback);
	}
	void setValue(float64 value, bool animated);
	float64 value() const;

	void updateState(const Player::TrackState &state);
	void updateLoadingState(float64 progress);

private:
	bool valueAnimationCallback(float64 now);
	bool receivedTillAnimationCallback(float64 now);
	void setReceivedTill(float64 value);
	void emitUpdatedValue();

	// This can animate for a very long time (like in music playing),
	// so it should be a Basic, not a Simple animation, because
	// Simple-s pauses mtproto responses/updates handling while playing.
	anim::value a_value, a_receivedTill;
	Ui::Animations::Basic _a_value, _a_receivedTill;
	Fn<void(float64,float64)> _valueChanged;

	bool _inLoadingState = false;
	Fn<void(bool)> _inLoadingStateChanged;

	int64 _position = 0;
	int64 _length = 0;
	int64 _receivedTill = -1;

	bool _playing = false;

};

} // namespace View
} // namespace Media
