#ifndef WARREN_WX_CUSTOM_TEXTURING_WXIMAGES_PACK_H
#define WARREN_WX_CUSTOM_TEXTURING_WXIMAGES_PACK_H

#include "fileSystem/fileSystem.h"
#include <wx/image.h>
#include <vector>

class WxImagesPack
{
private:
	std::vector< wxImage > images;
	
public:
	WxImagesPack() = default;
	WxImagesPack(const fs::path& packFilePath);
	~WxImagesPack() = default;
	WxImagesPack( const WxImagesPack& toCopy );
	WxImagesPack& operator= ( const WxImagesPack& toCopy );
	
	void addImage(const fs::path& imagePath);
	void freeImages();
	void addTexturesPackFromFile(const fs::path& packFilePath);
	
	const wxImage& operator[] (std::size_t index) const;
	operator bool() const;
	
};

#endif //WARREN_WX_CUSTOM_TEXTURING_WXIMAGES_PACK_H