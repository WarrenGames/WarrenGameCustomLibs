#ifndef WARREN_WX_CUSTOM_FILES_STRINGS_LOADER_H
#define WARREN_WX_CUSTOM_FILES_STRINGS_LOADER_H

#include "fileSystem/fileSystem.h"
#include <wx/string.h>
#include <vector>

class wxTextCtrl;

class WxTextsBlocks
{
private:
	std::vector< wxString > texts;
	
public:
	WxTextsBlocks() = default;
	WxTextsBlocks(wxTextCtrl* logFrame, const fs::path& textsEnumFilePath);
	WxTextsBlocks(wxTextCtrl* logFrame, const fs::path& textsEnumFilePath, std::size_t expectedSize);
	~WxTextsBlocks() = default;
	WxTextsBlocks( const WxTextsBlocks& ) = default;
	WxTextsBlocks& operator= ( const WxTextsBlocks& ) = default;
	WxTextsBlocks( WxTextsBlocks&& ) = default;
	WxTextsBlocks& operator= ( WxTextsBlocks&& ) = default;
	
	const wxString& operator[](const std::size_t textIndex) const;
	std::size_t size() const;
	std::vector< wxString >::const_iterator begin() const;
	std::vector< wxString >::const_iterator end() const;
	
	void openFile(wxTextCtrl* logFrame, const fs::path& textsEnumFilePath);
	void checkExpectedSize(wxTextCtrl* logFrame, const fs::path& textsEnumFilePath, std::size_t expectedSize);
	
private:
	void openTextEnumFile(wxTextCtrl& logFrame, const fs::path& textsEnumFilePath);
};

#endif //WARREN_WX_CUSTOM_FILES_STRINGS_LOADER_H