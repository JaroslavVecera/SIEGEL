#include "GraphicBuilder.h"
#include "Siegel.h"

using namespace demo;

GO* GraphicBuilder::BuildGoObject(json &data) {
	if (!data.is_object() || !data.contains("type"))
		return nullptr;
	return BuildGoObject(data, data["type"].get<string>());
}

GO* GraphicBuilder::BuildGoObject(json &data, string type) {
	std::map<string, GO*(GraphicBuilder::*)(json&)> typeFunctions;

	typeFunctions["Layout"] = &GraphicBuilder::BuildLayout;
	typeFunctions["Ellipse"] = &GraphicBuilder::BuildEllipse;
	GO* (GraphicBuilder::*function)(json&) = typeFunctions.find(type)->second;
	if (function == nullptr)
		return nullptr;
	GO* object = (*this.*function)(data);
	ParseSize(data, object);
	ParsePosition(data, object);
	return object;
}

GO* GraphicBuilder::BuildEllipse(json& data) {

	siegel::Ellipse* e = new siegel::Ellipse();

	if (data.contains("color")) {
		Color *c = nullptr;
		ParseColor(data["color"], &c);
		if (c != nullptr)
			e->SetColor(*c);
		delete c;
	}
	return e;
}

void GraphicBuilder::ParseColor(json& data, Color** c) {
	if (!data.is_array() || data.size() != 3)
		return;
	if (!data[0].is_number() || !data[1].is_number() || !data[2].is_number())
		return;
	(*c) = new Color(data[0], data[1], data[2]);
}

GO* GraphicBuilder::BuildLayout(json &data) {
	Layout* l = new Layout();

	if (data.contains("outlineColor")) {
		Color* c = nullptr;
		ParseColor(data["outlineColor"], &c);
		if (c != nullptr)
			l->SetOutlineColor(*c);
		delete c;
	}

	if (data.contains("children") && data["children"].is_array()) {
		forward_list<GO*> children = ParseChildren(data["children"]);
		for (GO* child : children)
			l->AddChild(child);
	}

	return l;
}

void GraphicBuilder::ParseSize(json& data, GO *object) {
	if (!data.contains("size") || !data["size"].is_array() || data["size"].size() != 2)
		return;
	json xJson = data["size"][0];
	json yJson = data["size"][1];
	if (xJson.type() != yJson.type())
		return;
	if (xJson.is_number()) {
		object->SetHorizontalSize(new FixedSize(xJson));
		object->SetVerticalSize(new FixedSize(yJson));
	}
	else if (xJson.is_array()) {
		Size* horizontalSize = ParseLongSize(xJson);
		Size* verticalSize = ParseLongSize(yJson);
		if (horizontalSize != nullptr)
			object->SetHorizontalSize(horizontalSize);
		if (verticalSize != nullptr)
			object->SetVerticalSize(verticalSize);
	}
}

Size* GraphicBuilder::ParseLongSize(json& data) {
	if (data.size() != 2 || !data[0].is_string() || !data[1].is_number())
		return nullptr;
	if (data[0] == "fixed")
		return new FixedSize(data[1]);
	if (data[0] == "stretchable")
		return new StretchableSize(data[1]);
	if (data[0] == "shrinkable")
		throw new exception("not implemented");
}

void GraphicBuilder::ParsePosition(json& data, GO* object) {
	if (!data.contains("position") || !data["position"].is_array() || data["position"].size() != 2)
		return;
	json xJson = data["position"][0];
	json yJson = data["position"][1];
	if (!xJson.is_array() || !yJson.is_array() || xJson.size() != 3 || yJson.size() != 3)
		return;
	json xShift = xJson[0];
	json xOrigin = xJson[2];
	json xParentOrigin = xJson[1];
	json yShift = yJson[0];
	json yOrigin = yJson[2];
	json yParentOrigin = yJson[1];
	if (!xShift.is_number() || !xOrigin.is_number() || !xParentOrigin.is_number()
		|| !yShift.is_number() || !yOrigin.is_number() || !yParentOrigin.is_number())
		return;
	Position hp(xShift, xParentOrigin, xOrigin);
	Position vp(yShift, yParentOrigin, yOrigin);
	object->SetHorizontalPosition(hp);
	object->SetVerticalPosition(vp);
}


forward_list<GO*> GraphicBuilder::ParseChildren(json& data) {
	forward_list<GO*> res;
	for (int i = 0; i < data.size(); i++) {
		res.push_front(BuildGoObject(data[i]));
	}
	return res;
}
