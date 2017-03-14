#include "Log.h"

std::ofstream Log::m_file;
Log::Targets Log::m_target;

void Log::Create(const std::string & path, Targets target)
{
	m_target = target;
	if (m_target == Targets::FILE || m_target == Targets::ALL) {
		m_file.open(path);
	}
}

const std::string Log::GetDate()
{
	time_t now = time(0);
	struct tm* tstruct;
	char buf[80];
	tstruct = localtime(&now);
	strftime(buf, sizeof(buf), "[%d.%m.%Y %X] ", tstruct);

	return buf;
}
