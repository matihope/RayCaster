#include <JsonBridge/JsonBridge.hpp>
#include <fstream>

bool JsonBridge::load(const std::string &filePath) {
  m_file_path = filePath;
  std::ifstream jsonFile(m_file_path.c_str());

  if (!jsonFile.is_open())
    return false;

  jsonFile >> data;
  jsonFile.close();
  return true;
}

std::string JsonBridge::getFilePath() const {
  return m_file_path;
}

bool JsonBridge::saveCurrentState() {
  std::fstream jsonFile(m_file_path.c_str(), std::ios::out);
  if (!jsonFile.is_open())
    return false;
  jsonFile << data.dump(4) << std::endl;
  jsonFile.close();
  return true;
}
