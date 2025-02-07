#pragma once

#include <utility>
#include "mvItemRegistry.h"

namespace Marvel{

	MV_REGISTER_WIDGET(mvSimplePlot, MV_ITEM_DESC_DEFAULT, StorageValueTypes::FloatVect, 1);
	class mvSimplePlot : public mvAppItem
	{

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

		MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvSimplePlot, add_simple_plot)

		MV_START_COMMANDS
		MV_END_COMMANDS

		MV_START_CONSTANTS
		MV_END_CONSTANTS

	public:

		explicit mvSimplePlot(mvUUID uuid);

		void draw(ImDrawList* drawlist, float x, float y) override;
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return _value; }
		PyObject* getPyValue() override;
		void setPyValue(PyObject* value) override;
		void handleSpecificKeywordArgs(PyObject* dict) override;
		void getSpecificConfiguration(PyObject* dict) override;

	private:

		mvRef<std::vector<float>> _value = CreateRef<std::vector<float>>(std::vector<float>{0.0f});
		std::string               _overlay;
		float                     _min = 0.0f;
		float                     _max = 0.0f;
		bool                      _histogram = false;
		bool                      _autosize = true;

	};

}