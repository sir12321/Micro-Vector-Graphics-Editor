#include "diagram.h"

#include <iostream>

using namespace std;

#include "../model/headers/circle.h"
#include "../model/headers/freehand.h"
#include "../model/headers/hexagon.h"
#include "../model/headers/line.h"
#include "../model/headers/rectangle.h"
#include "../model/headers/rounded_rectangle.h"
#include "../model/headers/text.h"

// Adds a new graphics object to the diagram
void Diagram::AddObject(unique_ptr<GraphicsObject> object) {
  objects_.push_back(move(object));
}

// Removes the object at the specified index
void Diagram::RemoveObject(size_t index) {
  if (index < objects_.size()) {
    objects_.erase(objects_.begin() + index);
  }
}

// Clears all objects from the diagram
void Diagram::Clear() { objects_.clear(); }

const vector<unique_ptr<GraphicsObject>>& Diagram::objects() const {
  return objects_;
}

size_t Diagram::size() const { return objects_.size(); }

// Generates SVG string representation of the diagram
std::string Diagram::ToSvg() const {
  std::string out = "";
  out += "<svg width=\"800\" height=\"600\">\n";
  for (const auto& obj : objects_) {
    out += obj->ToSvg();
  }
  out += "</svg>\n";
  return out;
}

// Helper to split string by newlines for parsing
vector<string> split_by_newline(const std::string& s) {
  vector<string> result;
  std::string current;
  for (char c : s) {
    if (c == '\n') {
      result.push_back(current);
      current.clear();
    } else {
      current += c;
    }
  }
  if (!current.empty()) {
    result.push_back(current);
  }
  return result;
}

// Parses SVG string to reconstruct diagram objects
void Diagram::FromSvg(const std::string& svg) {
  vector<std::string> lines = split_by_newline(svg);
  if (lines.size() < 2) return;
  for (const auto& line : lines) {
    if (line.find("<rect") != std::string::npos &&
        line.find("rx=\"") != std::string::npos) {
      RoundedRectangle temp(0, 0, 0, 0, 10.0, 1);
      auto obj = temp.FromSvg(line);
      AddObject(move(obj));
    } else if (line.find("<rect") != std::string::npos) {
      Rectangle temp(0, 0, 0, 0, 1);
      auto obj = temp.FromSvg(line);
      AddObject(move(obj));
    } else if (line.find("<circle") != std::string::npos) {
      Circle temp(0, 0, 0, 1);
      auto obj = temp.FromSvg(line);
      AddObject(move(obj));
    } else if (line.find("<line") != std::string::npos) {
      Line temp(0, 0, 0, 0, 1);
      auto obj = temp.FromSvg(line);
      AddObject(move(obj));
    } else if (line.find("<polygon") != std::string::npos) {
      Hexagon temp(0, 0, 0, 0, 1);
      auto obj = temp.FromSvg(line);
      AddObject(move(obj));
    } else if (line.find("<text") != std::string::npos) {
      TextObject temp(0, 0, "", 12, "Deja Vu Sans");
      auto obj = temp.FromSvg(line);
      AddObject(move(obj));
    } else if (line.find("<path") != std::string::npos) {
      Freehand temp;
      auto obj = temp.FromSvg(line);
      AddObject(move(obj));
    }
  }
}