#include "../../headers/text.h"

using namespace std;

// Exports to SVG.
string TextObject::ToSvg() const {
  return "<text x=\"" + to_string(x_) + "\" y=\"" + to_string(y_) +
         "\" stroke-fill=\"" + stroke_color_ + "\" fill=\"" + fill_color_ +
         "\" font-size=\"" + to_string(font_size_) + "\" font-family=\"" +
         font_family_ + "\">" + text_ + "</text>\n";
}

// Helper to split text by spaces.
vector<std::string> split_by_space_text(const std::string& s) {
  vector<std::string> result;
  std::string current;
  for (char c : s) {
    if (c == ' ') {
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

// Imports from SVG.
std::unique_ptr<GraphicsObject> TextObject::FromSvg(const std::string& svg) {
  double x = 0, y = 0;
  int font_size = 12;
  std::string text, fill_color = "black", font_family = "Deja Vu Sans",
                    stroke_color = "black";
  vector<std::string> parts = split_by_space_text(svg);

  for (const std::string& part : parts) {
    try {
      // Check complex attributes first to avoid substring matches
      if (part.find("font-family=\"") != std::string::npos) {
        font_family =
            part.substr(part.find("font-family=\"") + 13,
                        part.find("\"", part.find("font-family=\"") + 13) -
                            (part.find("font-family=\"") + 13));
      } else if (part.find("font-size=\"") != std::string::npos) {
        font_size = std::stoi(
            part.substr(part.find("font-size=\"") + 11,
                        part.find("\"", part.find("font-size=\"") + 11) -
                            (part.find("font-size=\"") + 11)));
      } else if (part.find("stroke-fill=\"") != std::string::npos) {
        stroke_color =
            part.substr(part.find("stroke-fill=\"") + 13,
                        part.find("\"", part.find("stroke-fill=\"") + 13) -
                            (part.find("stroke-fill=\"") + 13));
      } else if (part.find("fill=\"") != std::string::npos) {
        fill_color = part.substr(part.find("fill=\"") + 6,
                                 part.find("\"", part.find("fill=\"") + 6) -
                                     (part.find("fill=\"") + 6));
      } else if (part.find("x=\"") != std::string::npos) {
        x = std::stod(part.substr(
            part.find("x=\"") + 3,
            part.find("\"", part.find("x=\"") + 3) - (part.find("x=\"") + 3)));
      } else if (part.find("y=\"") != std::string::npos) {
        y = std::stod(part.substr(
            part.find("y=\"") + 3,
            part.find("\"", part.find("y=\"") + 3) - (part.find("y=\"") + 3)));
      }
    } catch (...) {
      // Skip invalid attributes
    }
  }

  // Extract text content between > and </text>
  size_t start = svg.find('>');
  size_t end = svg.find("</text>");
  if (start != std::string::npos && end != std::string::npos && start < end) {
    text = svg.substr(start + 1, end - start - 1);
  }

  auto obj = std::make_unique<TextObject>(x, y, text, font_size, font_family);
  obj->SetFillColor(fill_color);
  obj->SetStrokeColor(stroke_color);
  return obj;
}