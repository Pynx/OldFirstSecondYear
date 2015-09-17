#include "menu.h"
#include <string.h>

const int TEXT_SPACING = 8;

TMenu::TMenu(const char * pName)
	: m_iSelection(-1)
	, m_pName(pName)
{
}

const char * TMenu::GetName() const
{
	return m_pName;
}

bool TMenu::Update()
{
	if (m_tOptions.GetCount() > 0)
	{
		const int iOldSelection = m_iSelection;

		if (GfxInputIsJustPressed(EGfxInputID_AnyPadDown) || GfxInputIsJustPressed(EGfxInputID_KeyArrowDown))
		{
			m_iSelection++;
		}
		if (GfxInputIsJustPressed(EGfxInputID_AnyPadUp) || GfxInputIsJustPressed(EGfxInputID_KeyArrowUp))
		{
			m_iSelection--;
		}

		if (m_iSelection < 0)
		{
			m_iSelection = 0;
		}
		if (m_iSelection >= m_tOptions.GetCount())
		{
			m_iSelection = m_tOptions.GetCount() - 1;
		}

		bool bChanged = false;

		if (GfxInputIsJustPressed(EGfxInputID_AnyPadRight) || GfxInputIsJustPressed(EGfxInputID_KeyArrowRight))
		{
			bChanged = m_tOptions[m_iSelection].IncValue();
		}
		if (GfxInputIsJustPressed(EGfxInputID_AnyPadLeft) || GfxInputIsJustPressed(EGfxInputID_KeyArrowLeft))
		{
			bChanged = m_tOptions[m_iSelection].DecValue();
		}

		if (iOldSelection != m_iSelection || bChanged)
		{
			for (int i = 0; i < m_tOptions.GetCount(); ++i)
			{
				if (!m_tOptions[i].m_pTextSprite) m_tOptions[i].m_pTextSprite = GfxTextSpriteCreate();
				GfxTextSpritePrintf(m_tOptions[i].m_pTextSprite, "%c%s: %g", (i == m_iSelection) ? '>' : ' ', m_tOptions[i].m_pTextLabel, m_tOptions[i].m_pValueFloat ? *m_tOptions[i].m_pValueFloat : float(*m_tOptions[i].m_pValueInt));
				GfxSpriteSetPosition(m_tOptions[i].m_pTextSprite, 0, static_cast<float>(TEXT_SPACING * i));
			}
		}

		return bChanged;
	}

	return false;
}

void TMenu::Render()
{
	for (int i = 0; i < m_tOptions.GetCount(); ++i)
	{
		GfxSpriteRender(m_tOptions[i].m_pTextSprite);
	}
}
