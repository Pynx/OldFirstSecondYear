#ifndef MENU_OPTION_H_INCLUDED
#define MENU_OPTION_H_INCLUDED

struct TGfxSprite;

struct TMenuOption
{
	TGfxSprite * m_pTextSprite;
	const char * m_pTextLabel;
	float * m_pValueFloat;
	int * m_pValueInt;
	float m_fMinValue;
	float m_fMaxValue;
	float m_fIncrement;

	bool IncValue() const;
	bool DecValue() const;

	template<typename T>
	void SetValue(T & tValue);
};

#endif
