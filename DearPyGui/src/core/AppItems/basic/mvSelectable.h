#pragma once

#include "mvItemRegistry.h"

namespace Marvel {

	MV_REGISTER_WIDGET(mvSelectable, MV_ITEM_DESC_DEFAULT, StorageValueTypes::Bool, 1);
	class mvSelectable : public mvAppItem
	{

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

		MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvSelectable, add_selectable)

		MV_START_COMMANDS
		MV_END_COMMANDS

		MV_START_CONSTANTS
		MV_END_CONSTANTS

	public:

		mvSelectable(mvUUID uuid);

		void setEnabled(bool value)     override;
		void draw(ImDrawList* drawlist, float x, float y) override;
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return _value; }
		PyObject* getPyValue() override;
		void setPyValue(PyObject* value) override;
		void handleSpecificKeywordArgs(PyObject* dict) override;
		void getSpecificConfiguration(PyObject* dict) override;

	private:
		mvRef<bool>          _value = CreateRef<bool>(false);
		bool                 _disabled_value = false;
		ImGuiSelectableFlags _flags = ImGuiSelectableFlags_None;
	};

}
