#include "VerticalLayout.h"

#include "Widget.h"

void VerticalLayout::Update()
{
	vec2 size = m_parent->GetSize();

	float rowWidth = size.x - m_spacing * 2.0f;
	float rowHeight = (size.y - (m_items.size() + 1.0f) * m_spacing) / m_items.size();
	vec2 rowSize(rowWidth, rowHeight);

	for (unsigned int i = 0; i < m_items.size(); ++i) {
		Item& item = m_items[i];
		item.widget->SetSize(rowSize);
		vec2 itemSize = item.widget->GetSize();

		vec2 itemPosition;
		if (item.alignment & AlignLeft) {
			itemPosition.x = m_spacing;
		}
		else if (item.alignment & AlignRight) {
			itemPosition.x = size.x - m_spacing - itemSize.x;
		}
		else if (item.alignment & AlignHCenter) {
			itemPosition.x = (size.x - itemSize.x) / 2.0f;
		}

		itemPosition.y = (m_spacing + rowHeight) * static_cast<float>(i);
		if (item.alignment & AlignTop) {
			itemPosition.y += m_spacing;
		}
		else if (item.alignment & AlignBottom) {
			itemPosition.y += m_spacing + rowHeight - itemSize.y;
		}
		else if (item.alignment & AlignVCenter) {
			itemPosition.y += m_spacing + (rowHeight - itemSize.y) / 2.0f;
		}

		item.widget->SetPosition(m_parent->GetPosition() + itemPosition);
	}
}
