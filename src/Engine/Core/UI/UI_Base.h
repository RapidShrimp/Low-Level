#pragma once
#include "UI_Element.h"
#include "Engine/Core/Events/Event.h"
#include "Engine/Core/Input/InputSystem.h"

#include <vector>

class UI_Base : public GameObject {

public:

	virtual void Init(Object* OwningObject) override;

	void NavigateNext();
	void NavigatePrevious();

	void AddToNavigationPath(UI_Element* Element);
	void RemoveFromNavigationPath(UI_Element* Element);
	virtual void Render(sf::RenderWindow& Renderer) override;
	void AddElement(UI_Element* Element,bool StartActive = true);
	virtual void OnDestroy() override;


protected:

	std::vector<UI_Element*> m_Elements;

	//Navigation 
	std::vector<UI_Element*> m_NavigationPath;
	UI_Element* m_CurrentFocus;
	int m_NavigationIndex = 0;


	void SetNavigationFocus();
private:

};