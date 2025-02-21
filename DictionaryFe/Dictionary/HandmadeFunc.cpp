#include"HandmadeFunc.h"
#include<fstream>
#include<vector>
#include<locale>
#include<codecvt>
#include<iostream>
#include<ctime>
sf::RectangleShape createRectangleShape(float width, float height, float x, float y)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(sf::Vector2f(x, y));
	return shape;

}
sf::Text createText(std::wstring string, float x, float y, int size)
{
	sf::Text text;
	text.setString(string);
	text.setPosition(sf::Vector2f(x, y));
	text.setCharacterSize(size);
	return text;
}
void removeWord(std::wstring line, std::wstring path)
{
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	std::wfstream fin(path, std::ios::in);
	fin.imbue(loc);
	std::wstring get;
	std::vector<std::wstring> save;
	while (!fin.eof())
	{
		getline(fin, get);
		if(get.empty())
			continue;
		save.push_back(get);
	}
	fin.close();
	std::wfstream fout(path, std::ios::out);
	fout.imbue(loc);
	for (int i = 0; i < save.size(); i++)
	{
		if (save[i] == line)
			continue;
		fout << save[i] << std::endl;
	}
	fout.close();
}
Trie getDataset(std::wstring dataset, data* _data)
{
	if (dataset == L"Eng-Eng")
	{
		return _data->ee;
	}
	else if (dataset == L"Eng-Vi")
	{
		return _data->ev;
	}
	else if (dataset == L"Vi-Eng")
	{
		return _data->ve;
	}
}
bool existWord(std::wstring line, std::wstring path)
{
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	std::wfstream fin(path, std::ios::in);
	fin.imbue(loc);
	std::wstring get;
	while (!fin.eof())
	{
		getline(fin, get);
		if (get == line)
		{
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}
std::wstring randomWord(data* _data, int id)
{
	srand(time(NULL));
	if (id == -1)
	{
		id = rand() % 3;
	}
	std::wstring data;
	std::wstring word;
	std::wstring line;
	if (id == 0)
	{
		data = L"Eng-Eng";
		int idx = rand() % _data->eeKeyword.size();
		word = _data->eeKeyword[idx].keyWord;
		while (existWord(word + L"(" + data + L")", L"Resource\\RemoveWord.txt"))
		{
			idx = rand() % _data->eeKeyword.size();
			word = _data->eeKeyword[idx].keyWord;
		}
		line = word + L"(" + data + L")";
	}
	if (id == 1)
	{
		data = L"Eng-Vi";
		int idx = rand() % _data->evKeyword.size();
		word = _data->evKeyword[idx].keyWord;
		while (existWord(word + L"(" + data + L")", L"Resource\\RemoveWord.txt"))
		{
			idx = rand() % _data->eeKeyword.size();
			word = _data->evKeyword[idx].keyWord;
		}
		line = word + L"(" + data + L")";
	}
	if (id == 2)
	{
		data = L"Vi-Eng";
		int idx = rand() % _data->veKeyword.size();
		word = _data->veKeyword[idx].keyWord;
		while (existWord(word + L"(" + data + L")", L"Resource\\RemoveWord.txt"))
		{
			idx = rand() % _data->eeKeyword.size();
			word = _data->veKeyword[idx].keyWord;
		}
		line = word + L"(" + data + L")";
	}
	return line;
}