#include "ConfigMgr.h"
#include "const.h"

ConfigMgr::ConfigMgr()
{
	//获取当前工作目录
	boost::filesystem::path current_path = boost::filesystem::current_path();
	// 构建config.ini文件的完整路径， /重载了
	boost::filesystem::path config_path = current_path / "config.ini";
	std::cout << "Config path: " << config_path << std::endl;

	//使用boost.PropertyTree来读取.ini文件
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(config_path.string(), pt);

	//遍历.ini文件中的所有section
	for (const auto& section_pair : pt) {
		const std::string& section_name = section_pair.first;
		const boost::property_tree::ptree& section_tree = section_pair.second;
		
		std::map<std::string, std::string> section_config;
		//遍历每个section的key-value对
		for (const auto& key_value_pair : section_tree) {
			const std::string& key = key_value_pair.first;
			const std::string& value = key_value_pair.second.get_value<std::string>();
			section_config[key] = value;
		}
		SectionInfo section_info;
		section_info._section_datas = section_config;
		//对应key_value到config_map中
		_config_map[section_name] = section_info;
	}

	// 输出所有的section和key-value对  
	for (const auto& section_entry : _config_map) {
		const std::string& section_name = section_entry.first;
		SectionInfo section_config = section_entry.second;
		std::cout << "[" << section_name << "]" << std::endl;
		for (const auto& key_value_pair : section_config._section_datas) {
			std::cout << key_value_pair.first << "=" << key_value_pair.second << std::endl;
		}
	}
}

ConfigMgr::~ConfigMgr()
{
}
