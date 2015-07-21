#ifndef __QCLOUD_UTILS_HPP__

namespace QCloud
{

template<typename T>
std::string qc_num_to_string(T number)
{
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

}

#endif