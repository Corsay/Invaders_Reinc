#include <iostream>
#include "gameclasses/space.hpp"

#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "main_window.hpp"

#include <pugixml.hpp>
#include <json/json.h>
#include <json/writer.h>
#include <fstream>
#include <iostream>

void WriteJson()
{
  Json::Value settings;
  Json::Value resolutions(Json::arrayValue);
  resolutions.append(Json::Value("800x600"));
  resolutions.append(Json::Value("1024x768"));
  resolutions.append(Json::Value("1280x1024"));

  auto & root = settings["settings"];
  root["resolution"] = resolutions;
  root["aliensCount"] = 100;
  root["bulletsCount"] = 200;

  root["entities"]["gun"]["health"] = 50;
  root["entities"]["alien"]["health"] = 20;
  root["entities"]["obstacle"]["health"] = 15;

  std::ofstream settingsFile;
  settingsFile.open("settings.json");
  if (settingsFile.is_open())
  {
    Json::StyledWriter styledWriter;
    settingsFile << styledWriter.write(settings);
    settingsFile.close();
  }
}

void ReadJson()
{
  Json::Value settings;
  std::ifstream file("settings.json");
  if (file.is_open())
  {
    file >> settings;
    file.close();
  }

  Json::Value & resolutions = settings["settings"]["resolution"];
  if (resolutions.isArray())
  {
    for (Json::Value::ArrayIndex i = 0; i < resolutions.size(); i++)
      std::cout << resolutions[i].asString() << std::endl;
  }
  std::cout << settings["settings"]["aliensCount"].asInt() << std::endl;
  std::cout << settings["settings"]["bulletsCount"].asInt() << std::endl;

  Json::Value & entities = settings["settings"]["entities"];
  std::cout << entities["gun"]["health"].asInt() << std::endl;
  std::cout << entities["alien"]["health"].asInt() << std::endl;
  std::cout << entities["obstacle"]["health"].asInt() << std::endl;
}

void WriteXml()
{
  pugi::xml_document doc;
  auto declarationNode = doc.append_child(pugi::node_declaration);
  declarationNode.append_attribute("version") = "1.0";
  declarationNode.append_attribute("encoding") = "UTF-8";

  auto root = doc.append_child("settings");
  pugi::xml_node resolutions = root.append_child("resolutions");
  resolutions.append_child("resolution").append_child(pugi::node_pcdata).set_value("800x600");
  resolutions.append_child("resolution").append_child(pugi::node_pcdata).set_value("1024x768");
  resolutions.append_child("resolution").append_child(pugi::node_pcdata).set_value("1280x1024");

  root.append_child("aliensCount").append_attribute("value").set_value(100);
  root.append_child("bulletsCount").append_attribute("value").set_value(200);

  pugi::xml_node entities = root.append_child("entities");
  entities.append_child("gun").append_attribute("health").set_value(50);
  entities.append_child("alien").append_attribute("health").set_value(20);
  entities.append_child("obstacle").append_attribute("health").set_value(15);

  doc.save_file("settings.xml", PUGIXML_TEXT("  "));
}

void ReadXml()
{
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file("settings.xml", pugi::parse_default | pugi::parse_declaration);
  if (result)
  {
    pugi::xml_node root = doc.document_element();
    pugi::xml_node resolutions = root.child("resolutions");
    if (!resolutions.empty())
    {
      for (pugi::xml_node const & resolution : resolutions.children())
        std::cout << resolution.child_value() << std::endl;
    }

    pugi::xml_node aliensCount = root.child("aliensCount");
    if (!aliensCount.empty())
      std::cout << aliensCount.attribute("value").as_int() << std::endl;

    pugi::xml_node bulletsCount = root.child("bulletsCount");
    if (!bulletsCount.empty())
      std::cout << bulletsCount.attribute("value").as_int() << std::endl;

    pugi::xml_node entities = root.child("entities");
    if (!entities.empty())
    {
      pugi::xml_node gun = entities.child("gun");
      if (!gun.empty())
        std::cout << gun.attribute("health").as_int() << std::endl;

      pugi::xml_node alien = entities.child("alien");
      if (!alien.empty())
        std::cout << alien.attribute("health").as_int() << std::endl;

      pugi::xml_node obstacle = entities.child("obstacle");
      if (!obstacle.empty())
        std::cout << obstacle.attribute("health").as_int() << std::endl;
    }
  }
}

int main(int argc, char ** argv)
{
  try
  {
    QApplication app(argc, argv);

    MainWindow mw;
    mw.show();

    return app.exec();
  }
  catch (...)
  {
    std::cerr << "Unknown error!";
  }
  return 0;
}
