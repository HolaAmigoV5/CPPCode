#include "Test.h"
#include "imgui\imgui.h"

namespace test {
	TestMenu::TestMenu(Test*& currentTestPointer) :m_CurrentTest(currentTestPointer)
	{

	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& t : m_Tests) {
			if (ImGui::Button(t.first.c_str()))
				m_CurrentTest = t.second();
		}
	}
}

