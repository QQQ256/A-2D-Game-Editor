#pragma once

#include "json.hpp"
#include "Singleton.hpp"
#include "Debug.hpp"

#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

using json = nlohmann::json;

class FileReader: public Singleton<FileReader>{
public:
    FileReader() = default;

    ~FileReader() = default;

    bool LoadJSONFile(const string& fileName);

    void SaveJSONFile(const json, const string& jsonFileName);

    const json& GetConfig() const;

    bool LoadTilemapText(const string& fileName);

    void SaveTilemapText(int rows, int cols, const vector<int>& mapData, const string &fileName);

    // const vector<vector<int>>& GetTilemapData() const;
    
    const vector<int>& GetTilemapData() const;
private:
    json                m_Config;

    // vector<vector<int>> m_TilemapData;
    vector<int>         m_TilemapData;
};