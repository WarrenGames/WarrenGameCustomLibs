#include "files/stringsLoader.h"
#include <wx/textctrl.h>
#include <fstream>
#include <string>
#include <iostream>
#include <cassert>

WxTextsBlocks::WxTextsBlocks(wxTextCtrl* logFrame, const fs::path& textsEnumFilePath)
{
	openFile(logFrame, textsEnumFilePath);
}

WxTextsBlocks::WxTextsBlocks(wxTextCtrl* logFrame, const fs::path& textsEnumFilePath, std::size_t expectedSize)
{
	openFile(logFrame, textsEnumFilePath);
	checkExpectedSize(logFrame, textsEnumFilePath, expectedSize);
}

const wxString& WxTextsBlocks::operator[](const std::size_t textIndex) const
{
	assert( textIndex < texts.size() );
	return texts[textIndex];
}

std::size_t WxTextsBlocks::size() const
{
	return texts.size();
}

std::vector< wxString >::const_iterator WxTextsBlocks::begin() const
{
	return texts.cbegin();
}

std::vector< wxString >::const_iterator WxTextsBlocks::end() const
{
	return texts.cend();
}

void WxTextsBlocks::openFile(wxTextCtrl* logFrame, const fs::path& textsEnumFilePath)
{
	if( logFrame )
	{
		openTextEnumFile(*logFrame, textsEnumFilePath);
	}
	else{
		std::cout << "Error: log wxTextCtrl wasn't initialized for reading '" << textsEnumFilePath << "' .\n";
	}
}

void WxTextsBlocks::checkExpectedSize(wxTextCtrl* logFrame, const fs::path& textsEnumFilePath, std::size_t expectedSize)
{
	if( texts.size() != expectedSize )
	{
		if( logFrame )
		{
			*logFrame << "Error: '" << textsEnumFilePath.string() << "' file didn't supplied expected number of text lines: " << static_cast<int>(expectedSize) 
						<< " . Current size is : " << static_cast<int>(texts.size()) << '\n';
		}
		else{
			std::cout << "Error: '" << textsEnumFilePath.string() << "' file didn't supplied expected number of text lines: " << expectedSize 
						<< " . Current size is : " << texts.size() << '\n';
		}
	}
}

void WxTextsBlocks::openTextEnumFile(wxTextCtrl& logFrame, const fs::path& textsEnumFilePath)
{
	if( std::ifstream file{ textsEnumFilePath } )
	{
		std::string fileLine;
		while( std::getline( file, fileLine ) )
		{
			texts.emplace_back( wxString{ fileLine } );
		}
	}
	else{
		logFrame << "Error: cound't open '" << textsEnumFilePath.string() << "' text file.\n";
	}
}