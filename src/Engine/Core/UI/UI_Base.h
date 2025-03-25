#pragma once
#include "UI_Element.h"
#include <vector>

class UI_Base : public GameObject {

public:

	void NavigateNext();
	void NavigatePrevious();

	void AddToNavigationPath(UI_Element* Element);
	void RemoveFromNavigationPath(UI_Element* Element);
	virtual void Render(sf::RenderWindow& Renderer) override;

protected:

	std::vector<UI_Element*> m_Elements;

	//Navigation 
	std::vector<UI_Element*> m_NavigationPath;
	UI_Element* m_CurrentFocus;
	int m_NavigationIndex = 0;


	void SetNavigationFocus();
private:

};