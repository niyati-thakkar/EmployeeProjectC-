#include "pch.h"
#include "Log.h"

namespace Lognspace {
	void createFile(const std::string& filePath) {
		std::ofstream file(filePath, std::ios::app);
		if (file.is_open()) {
			file.close();
			//std::cout << "File created: " << filePath << std::endl;
		}
		else {
			std::cerr << "Error creating file: " << filePath << std::endl;
		}
	}

	Log::Log(Level level, std::string filep, bool to_file) : m_LogLevel{ level }, buffer{ NULL }, file_path{ filep }, printToFile{ to_file }
	{
		ID = get_id();
		registry r = registry::get_instance();
		
		if (to_file || file_path.string().length() > 0) {
			printToFile = true;
			std::filesystem::path normalizedPath = std::filesystem::absolute(file_path);

			if (filep.length() == 0) {
				// If user didn't provide a file path, create a file in the current directory
				file_path = "Logging" + std::to_string(ID / 100) + ".txt";
				createFile(file_path.string());
			}
			else {
				std::filesystem::path normalizedPath = std::filesystem::absolute(filep);

				if (std::filesystem::is_regular_file(normalizedPath)) {
					if (normalizedPath.extension() == ".txt") {
						// Use the provided file path
						file_path = filep;
					}
					else {
						// Create a new file in the same directory with a modified extension
						std::string parentDir = normalizedPath.parent_path().string();
						std::string fileName = normalizedPath.stem().string() + ".txt";
						file_path = (std::filesystem::path(parentDir) / fileName).string();
						createFile(file_path.string());
					}
				}
				else if (std::filesystem::is_directory(normalizedPath)) {
					// Create a new file in the specified directory with a modified extension
					std::string fileName = "Logging" + std::to_string(ID / 100) + ".txt";
					file_path = (normalizedPath / fileName).string();
					createFile(file_path.string());
				}
				else {
					// Check if the provided path contains only the file name
					if (normalizedPath.has_filename()) {
						// Create a new file with the provided name in the current directory
						std::string fileName = normalizedPath.filename().string();
						if (std::filesystem::path(fileName).extension() != ".txt") {
							fileName = fileName.substr(0, fileName.find_last_of('.')) + ".txt"; // Change extension to ".txt"
						}
						file_path = fileName;
						createFile(file_path.string());
					}
					else {
						std::cerr << "Invalid file path" << std::endl;
					}
				}
			}
		}
		else {
			std::cout << "File path not provided" << std::endl;
			return;
		}
		
		auto ptr = std::make_shared<Log>(*this);
		r.logger_objects[ID] = ptr;
	}

	


	Log::~Log() {
		registry r = registry::get_instance();
		r.logger_objects.erase(ID);
	}


	unsigned int Log::Log::get_id() {
		try {
			if (((RAND_MAX + 1u) / 10000) != 0)
				return 1 + std::rand() / ((RAND_MAX + 1u) / 10000);
		}
		catch (...) {
			return -1;
		}
		return -1;
		
	}

	void Log::set_log_level(Log::Level level)
	{
		m_LogLevel = level;
	}




	#include <filesystem>

void Log::log_it(int i) {
    std::string date = getDateTime();
    //std::string message = default_message[i].first;
    std::cout << date << " " << default_message[i].second << " " << buffer << "\n";
    
    if (printToFile) {
        std::error_code ec;
             
        std::ofstream outf{ file_path, std::ios::app };
        if (!outf.is_open()) {
            std::cerr << "Uh oh, " << file_path << " could not be opened for writing!\n";
            return;
        }
		
        outf << date << " " << default_message[i].first << " " << buffer << "\n";
        outf.close(); // Close the file explicitly
    }
    
    buffer = "";
}


	std::string Log::getDateTime() {
		auto _Time = std::chrono::system_clock::now();
		const auto time_tt = std::chrono::system_clock::to_time_t(_Time);
		std::tm tm;
		localtime_s(&tm, &time_tt);
		char date_buf[26];
		std::strftime(date_buf, sizeof(date_buf), "%d-%m-%Y %H:%M:%S", &tm);
		return date_buf;
	}
}