#pragma once
#include "UI_Base.h"

void UI_Base::NavigateNext()
{
	if (m_NavigationIndex + 1 == m_NavigationPath.size()) {
		m_NavigationIndex == 0;
	}
	else {
		m_NavigationIndex++;
	}
	SetNavigationFocus();
}

void UI_Base::NavigatePrevious()
{
	if (m_NavigationIndex == 0) {
		m_NavigationIndex = m_NavigationPath.size();
	}
	else {
		m_NavigationIndex--;
	}
	SetNavigationFocus();
}

void UI_Base::AddToNavigationPath(UI_Element* Element)
{
	if (Element == nullptr) { return; }
	m_NavigationPath.push_back(Element);
}
 
void UI_Base::RemoveFromNavigationPath(UI_Element* Element)
{
	if (Element == nullptr) { return; }
	auto itt = std::find(m_NavigationPath.begin(), m_NavigationPath.end(), Element);
	m_NavigationPath.erase(m_NavigationPath.begin(), itt);
}

void UI_Base::Render(sf::RenderWindow& Renderer)
{
	for (int i = 0; i < m_Elements.size(); i++) {
	//m_Elements[i].
	}
}

void UI_Base::SetNavigationFocus()
{
	if (m_CurrentFocus != nullptr) {
		m_CurrentFocus->OnRemoveFocus();
	}
	m_CurrentFocus = m_NavigationPath[m_NavigationIndex];
	m_CurrentFocus->OnSetFocus();
}
