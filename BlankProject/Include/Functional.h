#pragma once
#include "Core/IFunctional.h"
#include "Common/Signal.h"

#include <string>

class Functional : public IFunctional {

private:
	float m_freqIncrement;
	int m_number;

	float m_frequency;

	int m_bufferSize;
	float m_buffer[100];

	float m_timeSinceUpdate;

public:
	Functional(const Credentials& creds, IApplication* p_app);

public:
	int getPlotSize();
	float* getPlotData();

	float getFreqIncrement();
	void setFreqIncrement(float freqIncrement);

	int getNumber();
	void setNumber(int number);

	Signal<> onUpdatePlot;

private:
	void onTick(float deltaTime) override;

	IMPLEMENT_LOADSAVE(Functional);

};