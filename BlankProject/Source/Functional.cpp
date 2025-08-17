#include "Gui.h"
#include "Functional.h"
#include "Common/Reflection/Internal.h"

#include <numbers>

Functional::Functional(const Credentials& creds, IApplication* p_app) : IFunctional(creds, p_app), m_freqIncrement(1.0f), m_frequency(1.0f), m_number(0), m_bufferSize(100), m_timeSinceUpdate(0.0f) {

	// add members to reflection
	ADD_FIELD(float, m_freqIncrement);
	ADD_FIELD(int, m_number);

	// initialize buffer
	for (int i = 0; i < m_bufferSize; ++i) {
		m_buffer[i] = sin(i / 50.0f * m_frequency * std::numbers::pi);
	}
}

int Functional::getPlotSize() {

	return m_bufferSize;
}

float* Functional::getPlotData() {

	return &m_buffer[0];
}

float Functional::getFreqIncrement() {
	return m_freqIncrement;
}

void Functional::setFreqIncrement(float freqIncrement) {

	m_freqIncrement = freqIncrement;
}

int Functional::getNumber() {

	return m_number;
}

void Functional::setNumber(int number) {

	m_number = number;
}

void Functional::onTick(float deltaTime) {

	m_timeSinceUpdate += deltaTime;

	if (m_timeSinceUpdate > 0.1f) {

		// reset timer
		m_timeSinceUpdate = 0;

		// update buffer
		m_frequency += m_freqIncrement;

		if (m_frequency > 5.0f) {
			m_frequency = 1.0f;
		}

		for (int i = 0; i < m_bufferSize; ++i) {
			m_buffer[i] = sin(i / 50.0f * m_frequency * std::numbers::pi);
		}

		// update plot
		EMIT(onUpdatePlot)
	}
}
