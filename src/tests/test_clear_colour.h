#pragma once

#include "test.h"

namespace test {

	class TestClearColour : public Test
	{
	public:
		TestClearColour();
		~TestClearColour();

		void OnUpdate(Timestep ts) override;
		void OnImGuiRender() override;

	private:
		float m_ClearColour[4];
	};

}
