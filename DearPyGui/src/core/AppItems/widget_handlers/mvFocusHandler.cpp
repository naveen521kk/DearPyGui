#include "mvFocusHandler.h"
#include "mvLog.h"
#include "mvItemRegistry.h"
#include "mvPythonExceptions.h"
#include "mvUtilities.h"

namespace Marvel {

	void mvFocusHandler::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{

		mvPythonParser parser(mvPyDataType::UUID, "Adds a handler which runs a given callback when the specified item is focused.", { "Events", "Widgets" });
		mvAppItem::AddCommonArgs(parser, (CommonParserArgs)(
			MV_PARSER_ARG_ID |
			MV_PARSER_ARG_SHOW |
			MV_PARSER_ARG_CALLBACK)
		);

		parser.addArg<mvPyDataType::UUID>("parent");

		parser.finalize();

		parsers->insert({ s_command, parser });
	}

	mvFocusHandler::mvFocusHandler(mvUUID uuid)
		:
		mvAppItem(uuid)
	{

	}

	bool mvFocusHandler::isParentCompatible(mvAppItemType type)
	{
		return true;

		//mvThrowPythonError(mvErrorCode::mvN1one, "Drawing item parent must be a drawing.");
		//MV_ITEM_REGISTRY_ERROR("Drawing item parent must be a drawing.");
		//assert(false);
		//return false;
	}

	void mvFocusHandler::draw(ImDrawList* drawlist, float x, float y)
	{
		bool run = false;
		if (_parentPtr->getType() == mvAppItemType::mvWindowAppItem)
		{
			if (ImGui::IsWindowFocused())
				run = true;
		}
		else if (ImGui::IsItemFocused())
			run = true;

		if (run)
		{
			mvApp::GetApp()->getCallbackRegistry().submitCallback([=]()
				{
					mvApp::GetApp()->getCallbackRegistry().runCallback(getCallback(false), _uuid, GetPyNone(), _user_data);
				});
		}
	}

	void mvFocusHandler::handleSpecificRequiredArgs(PyObject* dict)
	{
		if (!mvApp::GetApp()->getParsers()[s_command].verifyRequiredArguments(dict))
			return;

		for (int i = 0; i < PyTuple_Size(dict); i++)
		{
			PyObject* item = PyTuple_GetItem(dict, i);
			switch (i)
			{
			case 0:
				_parent = ToUUID(item);
				break;

			default:
				break;
			}
		}
	}
}