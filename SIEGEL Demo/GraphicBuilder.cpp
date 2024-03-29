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
	typeFunctions["Rectangle"] = &GraphicBuilder::BuildRectangle;
	GO* (GraphicBuilder::*function)(json&) = typeFunctions.find(type)->second;
	if (function == nullptr)
		return nullptr;
	GO* object = (*this.*function)(data);
	ParseSize(data, object);
	ParsePosition(data, object);
	ParseMargin(data, object);
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

GO* GraphicBuilder::BuildRectangle(json& data) {

	siegel::Rectangle* e = new siegel::Rectangle();

	if (data.contains("color")) {
		Color* c = nullptr;
		ParseColor(data["color"], &c);
		if (c != nullptr)
			e->SetColor(*c);
		delete c;
	}

	if (data.contains("outlineColor")) {
		Color* c = nullptr;
		ParseColor(data["outlineColor"], &c);
		if (c != nullptr)
			e->SetBorderColor(*c);
		delete c;
	}

	if (data.contains("borderThickness")) {
		double t = ParseBorderThickness(data["borderThickness"]);
		e->SetBorderThickness(t);
	}

	if (data.contains("cornerRadius")) {
		double t = ParseBorderThickness(data["cornerRadius"]);
		e->SetRadius(t);
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
	ParsePadding(data, l);

	if (data.contains("outlineColor")) {
		Color* c = nullptr;
		ParseColor(data["outlineColor"], &c);
		if (c != nullptr)
			l->SetOutlineColor(*c);
		delete c;
	}

	if (data.contains("cornerRadius")) {
		double t = ParseBorderThickness(data["cornerRadius"]);
		l->SetCornerRadius(t);
	}

	if (data.contains("borderThickness")) {
		Color* c = nullptr;
		double t = ParseBorderThickness(data["borderThickness"]);
		l->SetBorderThickness(t);
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

void GraphicBuilder::ParseMargin(json& data, GO* object) {
	if (!data.contains("margin") || !data["margin"].is_array() || data["margin"].size() != 2)
		return;
	json xJson = data["margin"][0];
	json yJson = data["margin"][1];
	if (xJson.type() != yJson.type())
		return;
	if (xJson.is_number()) {
		object->SetHorizontalMargin(Vector2f(xJson, xJson));
		object->SetVerticalMargin(Vector2f(yJson, yJson));
	}
	else if (xJson.is_array()) {
		if (xJson.size() != 2 || yJson.size() != 2)
			return;
		object->SetHorizontalMargin(Vector2f(xJson[0], xJson[1]));
		object->SetVerticalMargin(Vector2f(yJson[0], yJson[1]));
	}
}

void GraphicBuilder::ParsePadding(json& data, Layout* object) {
	if (!data.contains("padding") || !data["padding"].is_array() || data["padding"].size() != 2)
		return;
	json xJson = data["padding"][0];
	json yJson = data["padding"][1];
	if (xJson.type() != yJson.type())
		return;
	if (xJson.is_number()) {
		object->SetHorizontalPadding(Vector2f(xJson, xJson));
		object->SetVerticalPadding(Vector2f(yJson, yJson));
	}
	else if (xJson.is_array()) {
		if (xJson.size() != 2 || yJson.size() != 2)
			return;
		object->SetHorizontalPadding(Vector2f(xJson[0], xJson[1]));
		object->SetVerticalPadding(Vector2f(yJson[0], yJson[1]));
	}
}

Size* GraphicBuilder::ParseLongSize(json& data) {
	if (!data[0].is_string() || !data[1].is_number())
		return nullptr;
	if (data.size() == 3) {
		if (data[0] == "proportional")
			return new ProportionalSize(data[1], data[2]);
		else
			return nullptr;
	}
	if (data.size() != 2)
		return nullptr;
	if (data[0] == "fixed")
		return new FixedSize(data[1]);
	if (data[0] == "stretch")
		return new StretchableSize(data[1]);
	if (data[0] == "shrink")
		return new ShrinkableSize(data[1]);
	else
		return nullptr;
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

double GraphicBuilder::ParseBorderThickness(json& data) {
	if (data.is_number())
		return data;
}


forward_list<GO*> GraphicBuilder::ParseChildren(json& data) {
	forward_list<GO*> res;
	for (int i = 0; i < data.size(); i++) {
		res.push_front(BuildGoObject(data[i]));
	}
	return res;
}
