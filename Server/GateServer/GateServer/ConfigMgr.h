#pragma once
/*****************************************************************//**
 * \file   ConfigMgr.h
 * \brief  处理.ini文件
 * 
 * \author 86187
 * \date   March 2025
 *********************************************************************/
#include "const.h"

struct SectionInfo {	//value, port
	SectionInfo(){}

	SectionInfo(const SectionInfo& src) {
		_section_datas = src._section_datas;
	}

	SectionInfo& operator = (const SectionInfo& src) {
		if (&src == this) {
			return *this;
		}
		this->_section_datas = src._section_datas;
		return *this;
	}

	~SectionInfo(){
		_section_datas.clear();
	}

	std::map<std::string, std::string> _section_datas;
	std::string operator[](const std::string& key) {	//_config_map用
		if (_section_datas.find(key) == _section_datas.end()) {
			return "";
		}
		// 可加入判断
		return _section_datas[key];
	}
};

class ConfigMgr
{
public:
	static ConfigMgr& Inst() {
		static ConfigMgr cfg_mgr;
		return cfg_mgr;
	}

	~ConfigMgr();

	ConfigMgr& operator= (const ConfigMgr& other) {
		if (&other == this) {
			return *this;
		}

		this->_config_map = other._config_map;
	}

	ConfigMgr(const ConfigMgr& other) {
		this->_config_map = other._config_map;
	}

	SectionInfo operator[] (const std::string& section) {	//[GateServer]
		if (_config_map.find(section) == _config_map.end()) {
			return SectionInfo();
		}
		return _config_map[section];
	}
private:
	ConfigMgr();

	std::map<std::string, SectionInfo> _config_map;
};

