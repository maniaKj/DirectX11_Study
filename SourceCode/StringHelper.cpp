#include "StringHelper.h"
#include <algorithm>

std::wstring StringHelper::StringToWide(std::string str) {
	std::wstring wide_string(str.begin(), str.end());
	return wide_string;
}

std::string StringHelper::GetDirectoryFromPath(const std::string & filepath)
{
	//경로명의 \\ 혹은 / 확인
	size_t off1 = filepath.find_last_of('\\');
	size_t off2 = filepath.find_last_of('/');
	if (off1 == std::string::npos && off2 == std::string::npos) {
		return "";
	}
	if (off1 == std::string::npos) {
		return filepath.substr(0, off2);
	}
	if (off2 == std::string::npos) {
		return filepath.substr(0, off1);
	}
	return filepath.substr(0, std::max(off1, off2)); //둘 다 존재하면 높은 값으로
}

std::string StringHelper::GetFileExtension(const std::string & filename)
{
	size_t off = filename.find_last_of('.');
	if (off == std::string::npos) {
		return {};
	}

	return std::string(filename.substr(off + 1));//확장자 빼기. ex : file.png 에서 . 위치 확인하고 그 뒤로는 제거
}
