#include "BakkesModInstallation.h"
#include <fstream>
#include <string>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qmessagebox.h>
#include <fstream>
#include <sstream>
#include "logger.h"
#include "vdf_parser.h"
#include <fstream>
#include <shlobj_core.h>
#include "json.hpp"
//std::string BakkesModInstallation::overrideBakkesModFolder = "";

void BakkesModInstallation::resetBMFolder()
{
	bakkesModFolder = "";
}

BakkesModInstallation::BakkesModInstallation()
{
}


BakkesModInstallation::~BakkesModInstallation()
{
}

std::filesystem::path BakkesModInstallation::GetBakkesModFolder()
{
	//if (!overrideBakkesModFolder.empty())
	//	return overrideBakkesModFolder;

	if (bakkesModFolder.empty())
	{
		LOG_LINE(INFO, "Not BakkesModFolder set this run");
		PWSTR path_tmp;
		auto get_folder_path_ret = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path_tmp);
		/* Error check */
		if (get_folder_path_ret != S_OK)
		{
			LOG_LINE(INFO, "SHGetKnownFolderPath failed somehow? " << get_folder_path_ret);
			CoTaskMemFree(path_tmp);
			//SHOULD NEVER REACH

		}
		else
		{

			/* Convert the Windows path type to a C++ path */
			LOG_LINE(INFO, "Converting path to filesystem path");
			std::filesystem::path bmPath = path_tmp;
			bmPath = bmPath / "bakkesmod" / "bakkesmod";
			bakkesModFolder = bmPath;
			LOG_LINE(INFO, bakkesModFolder.string());
			CoTaskMemFree(path_tmp);
			return bakkesModFolder;
		}
		
		/*std::wstring registryString = settings.GetStringSetting(L"BakkesModPath", RegisterySettingsManager::REGISTRY_DIR_APPPATH);
		if (!registryString.empty() && WindowsUtils::FileExists(windowsUtils.WStringToString(registryString) + "../RocketLeague.exe"))
		{
			bakkesModFolder = windowsUtils.WStringToString(registryString);
			return bakkesModFolder;
		}

		std::string newDetectedFolder = DetectRocketLeagueFolder();
		std::string rlPath = windowsUtils.GetRocketLeagueDirFromLog();
		if (!rlPath.empty() && WindowsUtils::FileExists(rlPath + "RocketLeague.exe"))
		{
			bakkesModFolder = rlPath + "bakkesmod\\";
			LOG_LINE(INFO, "Automatically detected Rocket League path: " << rlPath)
		} else if (!newDetectedFolder.empty()) {
			LOG_LINE(INFO, "Advanced detection found installation path " << newDetectedFolder)
			rlPath = newDetectedFolder;
			bakkesModFolder = rlPath + "bakkesmod\\";

		}
		else
		{
			LOG_LINE(INFO, "Could not find Rocket League path, asking user.")
			{
				QMessageBox msgBox2;
				std::stringstream ss;
				ss << "Could not find the Rocket League folder, please select it in the next window" << std::endl;
				ss << "The executable can be found in SteamLibrary\\steamapps\\common\\rocketleague\\Binaries\\Win64\\RocketLeague.exe";
				msgBox2.setText(ss.str().c_str());
				msgBox2.setStandardButtons(QMessageBox::Ok);
				msgBox2.setDefaultButton(QMessageBox::Ok);
				int ret = msgBox2.exec();
			}
			QString path = QFileDialog::getOpenFileName(this,
				QString("Select the Rocket League executable"), QString(QDir::currentPath()), QString("RocketLeague.exe (RocketLeague.exe)"));
			std::string rlPath = path.toStdString().substr(0, path.size() - std::string("RocketLeague.exe").size());
			bakkesModFolder = rlPath +"bakkesmod\\";
			LOG_LINE(INFO, "User selected executable: " << path.toStdString())
			if (!WindowsUtils::FileExists(rlPath))
			{

				LOG_LINE(INFO, "Folder does not exist: " << rlPath)
				QMessageBox msgBox2;
				msgBox2.setText("Did not select bakkesmod folder?");
				msgBox2.setStandardButtons(QMessageBox::Ok);
				msgBox2.setDefaultButton(QMessageBox::Ok);
				int ret = msgBox2.exec();
				bakkesModFolder = "";
				return "";
			}
		}
		auto converted = bakkesModFolder.wstring();
		settings.SaveSetting(L"BakkesModPath", converted, RegisterySettingsManager::REGISTRY_DIR_APPPATH);

	}

	return bakkesModFolder;*/
	}
	return std::filesystem::path("");
}



std::filesystem::path BakkesModInstallation::GetOldBakkesModFolder()
{
	//auto test = GetBakkesModFolder();
	auto oldPath = settings.GetStringSetting(L"BakkesModPath", RegisterySettingsManager::REGISTRY_DIR_APPPATH);
	if (ci_find_substr(oldPath, std::wstring(L"appdata")))
	{
		return std::filesystem::path(oldPath);
	}
	return std::filesystem::path("");
}

bool BakkesModInstallation::IsInstalled()
{
	return GetVersion() > 0;
}

unsigned int BakkesModInstallation::GetVersion()
{
	std::filesystem::path versionFilePath = GetBakkesModFolder() / "\\version.txt";
	if (!windowsUtils.FileExists(versionFilePath))
		return 0;
	std::ifstream versionFile;
	versionFile.open(versionFilePath);
	int version = 0;
	versionFile >> version;
	versionFile.close();
	return version;
}

bool BakkesModInstallation::IsSafeToInject(UpdateStatus currentVersion)
{
	bool steamReady = IsSteamVersionReady(currentVersion);
	if (steamReady)
	{
		LOG_LINE(INFO, "Steam is ready!");
		return steamReady;
	}
	bool epicReady = IsEpicVersionReady(currentVersion);
	if (epicReady)
	{
		LOG_LINE(INFO, "Epic is ready!");
		return epicReady;
	}
	return false;
}

bool BakkesModInstallation::ManifestFileExists()
{
	auto manifest = GetBakkesModFolder() / "..\\..\\..\\..\\..\\appmanifest_252950.acf";
	return (WindowsUtils::FileExists(manifest));
}

std::filesystem::path BakkesModInstallation::DetectRocketLeagueFolder()
{
	std::wstring path_str = settings.GetStringSetting(L"SteamPath", L"SOFTWARE\\Valve\\Steam") + L"\\steamapps\\";
	std::filesystem::path path = std::filesystem::path(path_str);
	std::filesystem::path vdfFile = path / L"libraryfolders.vdf";
	if (!WindowsUtils::FileExists(WindowsUtils::WStringToString(vdfFile)))
	{
		LOG_LINE(INFO, "Could not find steamapps folder, detected " << vdfFile.c_str());
		return "";
	}
	std::ifstream vdfStream(vdfFile);
	tyti::vdf::object root = tyti::vdf::read(vdfStream);
	if (root.name.compare("LibraryFolders") == std::string::npos)
	{
		LOG_LINE(INFO, "File root is not LibraryFolders, but " << root.name.c_str());
		return "";
	}

	std::filesystem::path installationPath = "";
	int lastBuildId = -1;
	for (auto child : root.attribs)
	{
		bool isPath = WindowsUtils::FileExists(child.second);
		LOG_LINE(INFO, "Key " << child.first << " = " << child.second << ". is path=" << (isPath ? "true" : "false"));
		if (isPath)
		{
			std::filesystem::path newPath = std::filesystem::path(child.second) / "\\steamapps\\";
			auto manifestPath = newPath / "appmanifest_252950.acf";
			auto executablePath = newPath / "common\\rocketleague\\Binaries\\Win64\\";
			auto executableLocation = executablePath / "RocketLeague.exe";
			if (WindowsUtils::FileExists(manifestPath))
			{
				try
				{
					LOG_LINE(INFO, "Path contains a manifest file");
					std::ifstream manifestStream(manifestPath);
					tyti::vdf::object manifestRoot = tyti::vdf::read(manifestStream);

					if (manifestRoot.name.compare("AppState") == std::string::npos)
					{
						LOG_LINE(INFO, "Manifest is invalid, skipping");
						continue;
					}

					if (manifestRoot.attribs.find("buildid") == manifestRoot.attribs.end())
					{
						LOG_LINE(INFO, "Manifest does not contain a buildid");
						continue;
					}
					std::string buildId = manifestRoot.attribs["buildid"];
					int buildIdInteger = stoi(buildId);
					if (buildIdInteger > lastBuildId)
					{
						LOG_LINE(INFO, "Found buildid " << buildIdInteger << " (newest high)");
						if (!WindowsUtils::FileExists(executableLocation))
						{
							LOG_LINE(INFO, "Could not find RocketLeague.exe at " << executableLocation);
							continue;
						}
						lastBuildId = buildIdInteger;
						installationPath = executablePath;
						LOG_LINE(INFO, "Found RocketLeague.exe at " << installationPath);
					}
				}
				catch (...)
				{
					LOG_LINE(INFO, "Error parsing manifest file, skipping this one")
				}
			}
		}
	}

	return installationPath;
}

std::filesystem::path BakkesModInstallation::GetSteamInstallLocation()
{
	std::filesystem::path newDetectedFolder = DetectRocketLeagueFolder();
	std::filesystem::path rlPath = windowsUtils.GetSteamRocketLeagueDirFromLog();
	if (!rlPath.string().empty() && WindowsUtils::FileExists(rlPath / "RocketLeague.exe"))
	{
		LOG_LINE(INFO, "Automatically detected Rocket League path using log: " << rlPath)
	}
	else if (!newDetectedFolder.empty())
	{
		LOG_LINE(INFO, "Advanced detection found installation path " << newDetectedFolder)
			rlPath = newDetectedFolder;
	}
	else
	{
		return std::filesystem::path("");
	}
	return rlPath;
}

std::string BakkesModInstallation::GetSteamVersion()
{
	std::filesystem::path manifest = GetSteamInstallLocation() / "..\\..\\..\\..\\" / "appmanifest_252950.acf";
	LOG_LINE(INFO, "Looking for steam manifest in " << manifest.string());
	std::string buildId = "";
	if (WindowsUtils::FileExists(manifest))
	{
		LOG_LINE(INFO, "Path contains a manifest file");
		std::ifstream manifestStream(manifest);
		std::string str((std::istreambuf_iterator<char>(manifestStream)),
			std::istreambuf_iterator<char>());
		if (str.find("buildid") == std::string::npos) //broken
		{
			LOG_LINE(INFO, "Manifest is broken? Could not find buildid string");
			return "";
		}
		manifestStream = std::ifstream(manifest);
		tyti::vdf::object manifestRoot;
		try
		{
			manifestRoot = tyti::vdf::read(manifestStream);
		}
		catch (...)
		{
			manifestStream.seekg(0, manifestStream.beg);
			std::string line = "";
			while (std::getline(manifestStream, line))
			{
				if (line.find("buildid") != std::string::npos)
				{
					std::string bid = "";
					for (auto c : line)
					{
						if (c >= '0' && c <= '9')
						{
							bid += c;
						}
					}
					buildId = bid;
					break;
				}
			}
			manifestRoot.name = "ERR";
		}
		
		if (buildId.size() == 0)
		{
			if (manifestRoot.name.compare("AppState") == std::string::npos)
			{
				LOG_LINE(INFO, "Manifest at " << manifest << " corrupt??")
				
			}
			else if (manifestRoot.attribs.find("buildid") == manifestRoot.attribs.end())
			{
				LOG_LINE(INFO, "Manifest does not contain a buildid");
			}
			else
			{
				buildId = manifestRoot.attribs["buildid"];
			}
		}
		LOG_LINE(INFO, "Steam buildID " << buildId);
	}
	else
	{
		LOG_LINE(INFO, "Could not find any RL manifest file!");
	}
	return buildId;
}

using json = nlohmann::json;
std::string BakkesModInstallation::GetEpicVersion()
{
	TCHAR szPath[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szPath)))
	{
		
		std::filesystem::path manifestsPath = std::filesystem::path(szPath) / "Epic" / "EpicGamesLauncher" / "Data" / "Manifests";
		LOG_LINE(INFO, "Checking Epic path " << manifestsPath.string());
		if (std::filesystem::exists(manifestsPath))
		{
			for (auto& p : std::filesystem::directory_iterator(manifestsPath))
			{
				//LOG_LINE(INFO, "Extension: " << p.path().extension().string())
				if (p.path().extension().string().compare(".item") == 0)
				{
					json js;
					bool requestFailed = false;
					LOG_LINE(INFO, "FOUND MANIFEST " << p.path().string());
					try
					{

						js = json::parse(std::ifstream(p));
					}
					catch (...)
					{
						requestFailed = true;
					}
					if (js.is_discarded())
					{
						requestFailed = true;
					}
					if (requestFailed)
					{
						LOG_LINE(INFO, "Parsing JSON failed (" << p.path().string() << ")")
							continue;
					}
					else
					{
						if (js.value("MandatoryAppFolderName", "").compare("rocketleague") == 0 ||
							js.value("LaunchExecutable", "").find("RocketLeague") != std::string::npos)
							{
								LOG_LINE(INFO, "This one is most likely RL manifest file");
								if (auto found = js.find("AppVersionString"); found != js.end())
								{
									std::string versionNumber = found->get<std::string>();
									LOG_LINE(INFO, "Found Epic version " << versionNumber);
									if (!versionNumber.empty())
									{
										return versionNumber;
									}
								}
							}
					}
				}
				
			}
		}
	}
	return "";
}

bool BakkesModInstallation::IsSteamVersionInstalled()
{
	return !GetSteamVersion().empty();
}

bool BakkesModInstallation::IsEpicVersionInstalled()
{
	return !GetEpicVersion().empty();
}

bool BakkesModInstallation::IsSteamVersionReady(UpdateStatus currentVersion)
{
	{
		std::string steamBuildId = GetSteamVersion();
		LOG_LINE(INFO, "Test " << steamBuildId);
		if (!steamBuildId.empty())
		{
			if (currentVersion.buildIds.size() > 0)
			{
				
				for (std::string buildidz : currentVersion.buildIds)
				{
					LOG_LINE(INFO, "Comparing steam buildid " << steamBuildId << " to " << buildidz)
						if (steamBuildId.compare(buildidz) == 0)
							return true;
				}
			}
		}
		else
		{
			LOG_LINE(INFO, "Could not find a proper steam manifest!")
				
		}
	}
	return false;
}

bool BakkesModInstallation::IsEpicVersionReady(UpdateStatus currentVersion)
{
	{
		LOG_LINE(INFO, "Checking Epic version");
		std::string epicBuildId = GetEpicVersion();
		if (!epicBuildId.empty())
		{
			LOG_LINE(INFO, "Found epic build ID " << epicBuildId);
			if (currentVersion.egsBuildIds.size() > 0)
			{
				for (std::string buildidz : currentVersion.egsBuildIds)
				{
					LOG_LINE(INFO, "Comparing EGS buildid " << epicBuildId << " to " << buildidz)
						if (epicBuildId == buildidz)
							return true;
				}
			}
		}
	}
	return false;
}
