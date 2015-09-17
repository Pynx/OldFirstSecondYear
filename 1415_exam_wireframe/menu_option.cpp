#include "menu_option.h"

float Clamp(const float fValue, const float fMin, const float fMax)
{
	if (fValue < fMin) return fMin;
	if (fValue > fMax) return fMax;
	return fValue;
}

bool TMenuOption::IncValue() const
{
	const float fOldValue = m_pValueFloat ? *m_pValueFloat : *m_pValueInt;
	const float fNewvalue = Clamp(fOldValue + m_fIncrement, m_fMinValue, m_fMaxValue);

	if (m_pValueFloat)
	{
		*m_pValueFloat = fNewvalue;
	}
	else
	{
		*m_pValueInt = int(fNewvalue);
	}

	return (fNewvalue != fOldValue);
}

bool TMenuOption::DecValue() const
{
	const float fOldValue = m_pValueFloat ? *m_pValueFloat : *m_pValueInt;
	const float fNewvalue = Clamp(fOldValue - m_fIncrement, m_fMinValue, m_fMaxValue);

	if (m_pValueFloat)
	{
		*m_pValueFloat = fNewvalue;
	}
	else
	{
		*m_pValueInt = int(fNewvalue);
	}

	return (fNewvalue != fOldValue);
}

template<>
void TMenuOption::SetValue(int & tValue)
{
	m_pValueFloat = nullptr;
	m_pValueInt = &tValue;
}

template<>
void TMenuOption::SetValue(float & tValue)
{
	m_pValueFloat = &tValue;
	m_pValueInt = nullptr;
}
