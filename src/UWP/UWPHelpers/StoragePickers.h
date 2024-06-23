// UWP STORAGE MANAGER
// Copyright (c) 2023 Bashar Astifan.
// Email: bashar@astifan.online
// Telegram: @basharastifan

// Functions:
// ChooseFolder()
// ChooseFile(std::vector<std::string> exts)

#pragma once
#if defined(_M_ARM) || defined(BUILD14393)
#include <ppl.h>
#include <ppltasks.h>
#include <string>
#include <vector>

concurrency::task<std::string> ChooseFolder();
concurrency::task<std::string> ChooseFile(std::vector<std::string> exts);

#else

#include <ppl.h>
#include <ppltasks.h>
#include <string>
#include <vector>

concurrency::task<std::string> ChooseFolder();
concurrency::task<std::string> ChooseFile(std::vector<std::string> exts);

#endif
