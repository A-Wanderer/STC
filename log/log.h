#ifndef LOG_H
#define LOG_H

#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1):__FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#endif

//定义一个在日志后添加 文件名 函数名 行号 的宏定义
#ifndef suffix
#define suffix(msg)  std::string(msg).append("  <")\
        .append(__FILENAME__).append("> <").append(__func__)\
        .append("> <").append(std::to_string(__LINE__))\
        .append(">").c_str()
//#define suffix(msg)  std::string().append(" File:")\
//        .append(__FILENAME__).append("\", Func:\"").append(__func__)\
//        .append("()\", Line:\"").append(std::to_string(__LINE__)).append("\"").append(msg).c_str()
#endif

//在  spdlog.h   之前定义，才有效
#ifndef SPDLOG_TRACE_ON
#define SPDLOG_TRACE_ON
#endif

#ifndef SPDLOG_DEBUG_ON
#define SPDLOG_DEBUG_ON
#endif

#include <sys/stat.h>
#include <sys/types.h>
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <spdlog/sinks/daily_file_sink.h>


class Logger
{

public:
	static Logger& GetInstance() {
		static Logger m_instance;
		return m_instance;
	}

    bool MakeSureDirExist(const char *dir){
	    assert(dir != NULL);
	    if (access(dir, F_OK) == -1){
		    mkdir(dir,0777);
	    }
	    return true;
    }

	auto GetLogger() { return nml_logger; }

private:
	Logger() {
		MakeSureDirExist("logs");
		//设置为异步日志
		//spdlog::set_async_mode(32768);  // 必须为 2 的幂
		std::vector<spdlog::sink_ptr> sinkList;
//#ifdef _CONSOLE
#ifdef _DEBUG
		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_level(spdlog::level::debug);
		//consoleSink->set_pattern("[multi_sink_example] [%^%l%$] %v");
		consoleSink->set_pattern("[%m-%d %H:%M:%S.%e][%^%L%$]  %v");
		sinkList.push_back(consoleSink);
#endif
		auto basicSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/basicSink.txt");
		basicSink->set_level(spdlog::level::debug);
		basicSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%5l%$]  %v");
		sinkList.push_back(basicSink);
		nml_logger = std::make_shared<spdlog::logger>("both", begin(sinkList), end(sinkList));
		//register it if you need to access it globally
		spdlog::register_logger(nml_logger);

		// 设置日志记录级别
#ifdef _DEBUG
		nml_logger->set_level(spdlog::level::info);
#else
		nml_logger->set_level(spdlog::level::info);
#endif
		//设置 logger 格式[%^%L%$]
		//nml_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%5l]  %v");
		//nml_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%5l%$]  %v");
		//设置当出发 err 或更严重的错误时立刻刷新日志到  disk
		nml_logger->flush_on(spdlog::level::err);

		spdlog::flush_every(std::chrono::seconds(1));
	}

	~Logger() {
		spdlog::drop_all();
	}

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

private:
	std::shared_ptr<spdlog::logger> nml_logger;
};

//Logger& operator<<(Logger& log, const char* s);
//Logger& operator<<(Logger& log, const std::string& s);

//#define DEBUG Logger::GetInstance()
#define LTrace(msg,...) Logger::GetInstance().GetLogger()->trace(suffix(msg),__VA_ARGS__)
//#define LDebug(msg,...) Logger::GetInstance().GetLogger()->debug(suffix(msg),__VA_ARGS__)
#define LDebug(...) Logger::GetInstance().GetLogger()->debug(__VA_ARGS__)
#define LInfo(...) Logger::GetInstance().GetLogger()->info(__VA_ARGS__)
#define LWarn(...) Logger::GetInstance().GetLogger()->warn(__VA_ARGS__)
#define LError(...) Logger::GetInstance().GetLogger()->error(__VA_ARGS__)
#define LCritical(...) Logger::GetInstance().GetLogger()->critical(__VA_ARGS__)

#define criticalif(b, ...)                        \
    do {                                       \
        if ((b)) {                             \
           Logger::GetInstance().GetLogger()->critical(__VA_ARGS__); \
        }                                      \
    } while (0)

#ifdef WIN32
#define errcode WSAGetLastError()
#endif
#endif //LOG_H