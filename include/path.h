
#ifndef HEAP_PATH_H_
#define HEAP_PATH_H_

#include <string>

namespace heap
{
	class Path
	{
		public:
			static void        init(const std::string & argv0);

			static std::string getAbsolutePath (const std::string & path);
			static std::string baseName        (const std::string & path, bool ext);
			static std::string dirName	       (const std::string & path);
			static std::string normalize       (const std::string & path);
			static std::string getExecDir      ();  


			template<typename... Next>
			static std::string join 			(Next... next);

			const static char delimiter;

		private:
			template<typename... Next>
			static std::string joinRec (const std::string & str, Next... next);
			static std::string joinRec ();

			static std::string execDir;

		
	};
}

#include "path.inl"

#endif