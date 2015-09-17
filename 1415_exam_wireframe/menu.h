#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "flib.h"
#include "menu_option.h"
#include "vector.h"

class TMenu
{
public:

	TMenu(const char * pName);

	template<typename T>
	void AddOption(const char * pText, T & tValue, const T tRefValue, const float fMinValue, const float fMaxValue, const float fIncrement = 1);

	const char * GetName() const;

	bool Update();
	void Render();

private:

	TVector< TMenuOption > m_tOptions;
	int m_iSelection;
	const char * m_pName;
};

template<typename T>
void TMenu::AddOption(const char * pText, T & tValue, const T tRefValue, const float fMinValue, const float fMaxValue, const float fIncrement)
{
	GfxDbgAssert(fMinValue <= fMaxValue);
	GfxDbgAssert(tRefValue <= fMaxValue);
	GfxDbgAssert(tRefValue >= fMinValue);

	TMenuOption tOption;

	tValue = tRefValue;

	tOption.m_pTextLabel = pText;
	tOption.m_pTextSprite = nullptr;
	tOption.m_fMinValue = fMinValue;
	tOption.m_fMaxValue = fMaxValue;
	tOption.m_fIncrement = fIncrement;

	tOption.SetValue(tValue);
	m_tOptions.PushBack(tOption);
}

#endif
