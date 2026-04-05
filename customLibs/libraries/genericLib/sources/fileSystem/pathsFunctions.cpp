#include "fileSystem/pathsFunctions.h"
#include <cassert>

fs::path pathFunc::getLastDirectoryName(const fs::path& path)
{
	if( path.empty() )
	{
		assert( false && "Error: supplied path is empty !" );
		return path;
	}
	else{
		fs::path temp{ path };
		fs::path lastDirectory;
		if( temp.has_filename() )
		{
			temp.remove_filename();
		}
		for( auto it = temp.begin() ; it != temp.end() ; ++it )
		{
			if( it->empty() == false )
			{
				lastDirectory = *it;
			}
		}
		
		if( lastDirectory.empty() )
		{
			assert( false && "Error: computed path is empty !" );
			return path;
		}
		else{
			return lastDirectory;
		}
	}
}