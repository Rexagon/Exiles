#pragma once

#include "GUI.h"

class State
{
public:
	State() {}
	virtual ~State() {}

	// ���������� ��� �������� ����� (���������� � � ����)
	virtual void OnInit() {}

	// ���������� ������ ����
	virtual void OnUpdate(const float dt) {}

	// ���������� ����� OnUpdate � ������ ������
	virtual void OnDraw(const float dt) {}

	// ���������� ��� ��������� �������� ������
	virtual void OnResize() {}

	// ���������� ��� ������������ �� ���� ����
	virtual void OnFocusGained() {}

	// ���������� ��� ������������ �� ������ ����
	virtual void OnFocusLost() {}

	// ���������� ��� �������� �����
	virtual void OnClose() {}
protected:
	friend class Core;

	GUI m_gui;
};