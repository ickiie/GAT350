#pragma once


class Image
{
public:
	bool Load(const std::string& filename, uint8_t alpha = 255);

private:
	<a pointer to a uint8_t buffer>
		<a variable to hold the widthand a variable to hold the height of the image>
};
