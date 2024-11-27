#include "xml_processor.h"
#include "pugixml.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

namespace XMLLoader
{
	//Helper functions
	std::string LoadField(const pugi::xml_node& fieldNode)
	{
		if (fieldNode.child("field"))
		{
			std::string fieldVal{ "{ " };
			for (pugi::xml_node fieldNodeChild = fieldNode.child("field"); fieldNodeChild; fieldNodeChild = fieldNodeChild.next_sibling())
				fieldVal += LoadField(fieldNodeChild);

			fieldVal.append("} ");
			return fieldVal;
		}
		else
		{
			std::string fieldVal{ "{ " + std::string{fieldNode.child_value()} + " }" };
			fieldVal.append(" ");
			return fieldVal;
		}
	}

	void AddDataNode(pugi::xml_node& parent, const char* data)
	{
		parent.append_child(pugi::xml_node_type::node_pcdata);

		if (!parent.last_child().set_value(data))
			std::cout << "Unable to set value";
	}
	void AddTagNode(pugi::xml_node& parent, const std::string& name, const std::vector<std::pair<std::string, std::string>>& attributes)
	{
		pugi::xml_node child = parent.append_child(name.c_str());
		if (!attributes.empty())
		{
			for (auto& attribute : attributes)
			{
				pugi::xml_attribute child_attribute = child.append_attribute(attribute.first.c_str());
				child_attribute.set_value(attribute.second.c_str());
			}
		}
	}
	
	bool GetNextEnclosedString(std::string& stream, std::string& str, const std::pair<char, char>& enclosers)
	{
		if (!str.empty())
			str.clear();

		std::string leftEnclosers{}, rightEnclosers{};

		if (stream[0] != enclosers.first)
			return false;

		std::string::iterator streamItr{ stream.begin() };
		do
		{
			if (*streamItr == enclosers.first)
				leftEnclosers.push_back(*streamItr);

			if (*streamItr == enclosers.second)
				rightEnclosers.push_back(*streamItr);

			streamItr++;

		} while ((leftEnclosers.size() != rightEnclosers.size()) && streamItr != stream.end());

		//in the case the stream end was reached and enclosers were not matched
		if (leftEnclosers.size() != rightEnclosers.size())
			return false;

		//extract the string
		str = std::move(std::string(stream.begin() + 1, streamItr - 1));
		stream.erase(stream.begin(), streamItr);

		return true;
	}

	void BuildTree(std::string& stream, pugi::xml_node& parentNode)
	{
		std::string extractedStr{}, tag{};
		while (true)
		{
			if (!GetNextEnclosedString(stream, tag, { '[', ']' }))
				break;

			AddTagNode(parentNode, "field", { {"name", tag} });
			pugi::xml_node childNode = parentNode.last_child();

			if(!GetNextEnclosedString(stream, extractedStr, { '{', '}' }))
				break;

			if (extractedStr.empty())
				AddDataNode(childNode, extractedStr.c_str());
			else if (extractedStr.at(0) == '[')//nota: h� erro aqui
				BuildTree(extractedStr, childNode);
			else
				AddDataNode(childNode, extractedStr.c_str());
		}
	}

	void LoadFromXML(const std::string& path, std::stringstream& fieldData)
	{
		pugi::xml_document doc;
		auto result = doc.load_file(path.c_str()); // open file
		//if it fails, put the description out (should be logged)
		if (!result)
		{
			std::cout << result.description() << '\n';
			return;
		}

		for (pugi::xml_node fieldNode = doc.child("config").child("field"); fieldNode; fieldNode = fieldNode.next_sibling())
			fieldData << LoadField(fieldNode);

	}

	void SaveToXML(const std::string& path, const std::stringstream& fieldData)
	{
		//document
		pugi::xml_document doc;
		pugi::xml_node rootNode = doc.append_child("config");//create the root node

		std::string fieldDataStream{ fieldData.str() };
		BuildTree(fieldDataStream, rootNode);

		if (!fieldDataStream.empty())
			throw std::runtime_error("Stream save was not successful"); // problems

		// save xml
		if (!doc.save_file(path.c_str()))
			std::cout << "File was not saved!";
	}
}
