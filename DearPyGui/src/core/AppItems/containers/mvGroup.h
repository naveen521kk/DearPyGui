#pragma once

#include "mvTypeBases.h"

namespace Marvel {

	struct mvGroupConfig : public mvAppItemConfig
	{
		bool horizontal = false;
		float horizontal_spacing = -1;
	};

	MV_REGISTER_WIDGET(mvGroup);
	class mvGroup : public mvAppItem
	{
		MV_APPITEM_TYPE(mvAppItemType::mvGroup, add_group)

		MV_CREATE_CONSTANT(mvThemeStyle_Group_ItemSpacingX, 13L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Group_ItemSpacingY, 13L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

		MV_START_COLOR_CONSTANTS
		MV_END_COLOR_CONSTANTS

		MV_START_STYLE_CONSTANTS
			MV_ADD_CONSTANT(mvThemeStyle_Group_ItemSpacingX, 8, 20),
			MV_ADD_CONSTANT(mvThemeStyle_Group_ItemSpacingY, 4, 20),
		MV_END_STYLE_CONSTANTS

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

	public:

			mvGroup(const std::string& name);

		void draw()               override;

		void setExtraConfigDict(PyObject* dict) override;
		void getExtraConfigDict(PyObject* dict) override;

	private:

		bool  m_horizontal = false;
		float m_hspacing = -1.0f;

	};

}