#include "../Utility/Utility.h"

int main()
{
    std::string content;
    //content.append("struct MatPBR_Test\n");
    //content.append("{\n");
    content.append("	[Editor(Albedo1, Range(0, 1))]");
    content.append("	[Editor(Albedo2, Range(0, 1))]");
    content.append("	[Editor(Albedo2, Range(0, 1))]");
    content.append("	float3 albedo[32] = float3(1.0, 1.0, 1.0);\n");
    content.append("	[Editor(Metallic, Range(0, 1))]");
    content.append("	float metallic = float(1.0);\n");
    content.append("	[Editor(Roughness, Range(0, 1))]");
    content.append("	float roughness;\n");
    content.append("	[Editor(AO)]");
    content.append("	float ao;\n");
    content.append("	[Editor(CD)]");
    content.append("	float cd[16];\n");
    content.append("	[Editor(EEE, Range(0, 1))]");
    content.append("	float eee = float(1.0);\n");
    //content.append("};");

    std::regex regex_all(R"((?:(\[\w+\(.*\)\])\s*)*(\w+)\s+(\w+)\[?(\d*)\]?([\s\S]*?);)");
    std::regex regex_define(R"((\w+)\s+(\w+)\[?(\d*)\]?[\s\S]*?;)");
    std::regex regex_constraint(R"(\[(\w+\(.*?\))\]\s*)");
    std::regex regex_constraint_name_value(R"((\w+)\((.*)\))");
    std::regex regex_constraint_value(R"((.+?)\s*,\s*(.+?))");

    std::regex regex_space(R"(\s)");
    std::regex regex_remove_constraint(R"(\[\w+\(.*\)\]\s*)");
    std::sregex_iterator end;

    auto match_all = std::sregex_iterator(content.begin(), content.end(), regex_all);
    while (match_all != end)
    {
        std::string constraints = (*match_all)[1];

        auto match_constraint = std::sregex_iterator((*match_all)[1].first, (*match_all)[1].second, regex_constraint);
        while (match_constraint != end)
        {
            std::string constraint = (*match_constraint)[1];
            std::smatch match_name_value;
            std::regex_match((*match_constraint)[1].first, (*match_constraint)[1].second, match_name_value, regex_constraint_name_value);
            std::string constraint_name = match_name_value[1];
            std::string constraint_value = match_name_value[2];

            std::smatch match_value;
            std::regex_match(match_name_value[2].first, match_name_value[2].second, match_value, regex_constraint_value);
            std::string show_name = match_value[1];
            std::string range = match_value[2];

            show_name = std::regex_replace(show_name, regex_space, "");
            range = std::regex_replace(range, regex_space, "");

            auto pos = range.find_first_of("Range");
            if (pos != range.npos)
            {
                range = range.substr(pos + 5, range.size() - pos);
                range.erase(range.begin());
                range.erase(range.end() - 1);

                pos = range.find_first_of(',');
                std::string min = range.substr(0, pos);
                std::string max = range.substr(pos + 1, range.size() - pos - 1);
            }

            ++match_constraint;
        }

        std::string value_type = (*match_all)[2];
        std::string value_name = (*match_all)[3];
        std::string value_count = (*match_all)[4];
        std::string value_ext = (*match_all)[5];

        ++match_all;
    }

    content = std::regex_replace(content, regex_remove_constraint, "");

    MY_CONSOLE_WRITE_LINE(content);

    return 0;
}
