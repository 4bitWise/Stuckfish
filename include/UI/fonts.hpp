/******************************************************************************
 * File:        fonts.hpp
 * Authors:     see AUTHORS file
 * Date:        May 3, 2024
 * Description: This file contains all the data related to the fonts we are using
 *****************************************************************************/

#pragma once

extern unsigned char roboto_regular[168260];
extern unsigned char roboto_medium[168644];

class FontSizes
{
public:
	static const float LargeHeaderFontSize;
	static const float MediumHeaderFontSize;
	static const float SmallHeaderFontSize;

	static const float LargeBodyFontSize;
	static const float MediumBodyFontSize;
	static const float SmallBodyFontSize;
};
