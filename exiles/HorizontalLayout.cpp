#include "HorizontalLayout.h"

#include "Widget.h"

void HorizontalLayout::Update()
{
	vec2 size = m_parent->GetSize();

	float colWidth = (size.x - (m_items.size() + 1.0f) * m_spacing) / m_items.size();
	float colHeight = size.y - m_spacing * 2.0f;
	vec2 rowSize(colWidth, colHeight);

	for (unsigned int i = 0; i < m_items.size(); ++i) {
		Item& item = m_items[i];
		item.widget->SetSize(rowSize);
		vec2 itemSize = item.widget->GetSize();

		vec2 itemPosition;
		itemPosition.x = (m_spacing + colWidth) * static_cast<float>(i);
		if (item.alignment & AlignLeft) {
			itemPosition.x += m_spacing;
		}
		else if (item.alignment & AlignRight) {
			itemPosition.x += m_spacing + colWidth - itemSize.x;
		}
		else if (item.alignment & AlignHCenter) {
			itemPosition.x += m_spacing + (colWidth - itemSize.x) / 2.0f;
		}

		if (item.alignment & AlignTop) {
			itemPosition.y = m_spacing;
		}
		else if (item.alignment & AlignBottom) {
			itemPosition.y = size.y - m_spacing - itemSize.y;
		}
		else if (item.alignment & AlignVCenter) {
			itemPosition.y = (size.y - itemSize.y) / 2.0f;
		}

		item.widget->SetPosition(m_parent->GetPosition() + itemPosition);
	}
}
