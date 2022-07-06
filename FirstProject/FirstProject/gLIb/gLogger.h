#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <spdlog/spdlog.h>		
#include <spdlog/stopwatch.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/async.h>

#include <string>
#include <cstdarg>

using namespace std;
class gLogger
{
private:
	std::shared_ptr<spdlog::logger> m_logger;
	spdlog::stopwatch* m_stopwatch;

	string m_logName;
	string m_path;
	enum spdlog::level::level_enum m_level;

	void init();

public:
	gLogger(string logName, string path);
	gLogger(string logName, string path, bool isRotate, int param1, int param2);
	~gLogger();

	void setLevel(enum spdlog::level::level_enum level);
	void start();
	void end();

	std::shared_ptr<spdlog::logger> getLogger() { return m_logger; };
};

#define trace(str, ...) getLogger()->trace("[{}:{}] "##str, __FUNCTION__, __LINE__, __VA_ARGS__);
#define debug(str, ...) getLogger()->debug("[{}:{}] "##str, __FUNCTION__, __LINE__, __VA_ARGS__);
#define info(str, ...) getLogger()->info("[{}:{}] "##str, __FUNCTION__, __LINE__, __VA_ARGS__);
#define warn(str, ...) getLogger()->warn("[{}:{}] "##str, __FUNCTION__, __LINE__, __VA_ARGS__);
#define error(str, ...) getLogger()->error("[{}:{}] "##str, __FUNCTION__, __LINE__, __VA_ARGS__);
#define critical(str, ...) getLogger()->critical("[{}:{}] "##str, __FUNCTION__, __LINE__, __VA_ARGS__);

#endif /* __LOGGER_H__ */