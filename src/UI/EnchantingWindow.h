
// EnchantingWindow.h

// Representing the UI window for the enchanting block





#pragma once

#include "Window.h"





class cEnchantingWindow :
	public cWindow
{
	typedef cWindow super;

public:
	cEnchantingWindow(int a_BlockX, int a_BlockY, int a_BlockZ) :
		cWindow(wtEnchantment, "Enchant"),
		m_SlotArea(),
		m_BlockX(a_BlockX),
		m_BlockY(a_BlockY),
		m_BlockZ(a_BlockZ)
	{
		m_SlotArea = new cSlotAreaEnchanting(*this, m_BlockX, m_BlockY, m_BlockZ);
		m_SlotAreas.push_back(m_SlotArea);
		m_SlotAreas.push_back(new cSlotAreaInventory(*this));
		m_SlotAreas.push_back(new cSlotAreaHotBar(*this));
	}

	virtual void SetProperty(short a_Property, short a_Value, cPlayer & a_Player) override
	{
		if ((a_Property < 0) || ((size_t)a_Property >= ARRAYCOUNT(m_PropertyValue)))
		{
			ASSERT(!"a_Property is invalid");
			return;
		}

		m_PropertyValue[a_Property] = a_Value;
		super::SetProperty(a_Property, a_Value, a_Player);
	}

	virtual void SetProperty(short a_Property, short a_Value) override
	{
		if ((a_Property < 0) || ((size_t)a_Property >= ARRAYCOUNT(m_PropertyValue)))
		{
			ASSERT(!"a_Property is invalid");
			return;
		}

		m_PropertyValue[a_Property] = a_Value;
		super::SetProperty(a_Property, a_Value);
	}

	/** Return the Value of a Property */
	short GetPropertyValue(short a_Property)
	{
		if ((a_Property < 0) || ((size_t)a_Property >= ARRAYCOUNT(m_PropertyValue)))
		{
			ASSERT(!"a_Property is invalid");
			return 0;
		}

		return m_PropertyValue[a_Property];
	}

	virtual void DistributeStack(cItem & a_ItemStack, int a_Slot, cPlayer & a_Player, cSlotArea * a_ClickedArea, bool a_ShouldApply) override
	{
		cSlotAreas AreasInOrder;

		if (a_ClickedArea == m_SlotAreas[0])
		{
			// Enchanting Area
			AreasInOrder.push_back(m_SlotAreas[2]);  /* Hotbar    */
			AreasInOrder.push_back(m_SlotAreas[1]);  /* Inventory */
			super::DistributeStackToAreas(a_ItemStack, a_Player, AreasInOrder, a_ShouldApply, true);
		}
		else
		{
			// Inventory or Hotbar
			AreasInOrder.push_back(m_SlotAreas[0]);  /* Enchanting */
			super::DistributeStackToAreas(a_ItemStack, a_Player, AreasInOrder, a_ShouldApply, false);
		}
	}

	cSlotArea * m_SlotArea;

protected:
	short m_PropertyValue[3];
	int m_BlockX, m_BlockY, m_BlockZ;
};




