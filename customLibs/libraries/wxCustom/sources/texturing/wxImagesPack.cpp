#include "texturing/wxImagesPack.h"
#include <wx/string.h>
#include <fstream>
#include <string>
#include <cassert>
#include <algorithm>

WxImagesPack::WxImagesPack(const fs::path& texturesPacksFilePath)
{
	addTexturesPackFromFile( texturesPacksFilePath );
}

WxImagesPack::WxImagesPack( const WxImagesPack& toCopy )
{
	if( toCopy.images.empty() == false )
	{
		images.clear();
		for( auto const &img : toCopy.images )
		{
			images.emplace_back( wxImage{ img.Copy() } );
		}
	}
}

WxImagesPack& WxImagesPack::operator= ( const WxImagesPack& toCopy )
{
	if( toCopy.images.empty() == false )
	{
		images.clear();
		for( auto const &img : toCopy.images )
		{
			images.emplace_back( wxImage{ img.Copy() } );
		}
	}
	return *this;
}

void WxImagesPack::addImage( const fs::path& imagePath)
{
	images.emplace_back( wxImage{ wxString{ imagePath.string() } } );
}

void WxImagesPack::freeImages()
{
	for( auto &img : images )
	{
		img.Destroy();
	}
}

void WxImagesPack::addTexturesPackFromFile(const fs::path& packFilePath)
{
	if( std::ifstream texturesPackFilesEnum{ packFilePath } )
	{
		std::string fileLine;
		while( std::getline( texturesPackFilesEnum, fileLine ) )
		{
			images.emplace_back( wxImage{ wxString{ fileLine } } );
		}
	}
}

const wxImage& WxImagesPack::operator[] ( std::size_t index ) const
{
	assert( index < images.size() );
	return images[index];
}

WxImagesPack::operator bool() const
{
	return images.empty() || std::all_of( std::cbegin( images ), std::cend( images ), [](auto const &img){ return img.IsOk(); } );
}