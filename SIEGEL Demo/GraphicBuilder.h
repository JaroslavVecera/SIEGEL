#pragma once

#include <nlohmann/json.hpp>
#include <GO.h>

using json = nlohmann::json;

using namespace siegel;

namespace demo {
	class GraphicBuilder {
	private:
		GO* BuildGoObject(json &data, string type);
		GO* BuildEllipse(json &data);
		GO* BuildLayout(json &data);
		void ParseColor(json& data, Color** c);
		void ParseSize(json& data, GO* object);
		void ParseMargin(json& data, GO* object);
		Size* ParseLongSize(json& data);
		void ParsePosition(json& data, GO* object);
		double ParseBorderThickness(json& data);
		forward_list<GO*> ParseChildren(json& data);
	public:
		GO* BuildGoObject(json &data);
	};
}
