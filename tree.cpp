#include "tree.hpp"

void Tree::walk(std::string directory, std::string prefix) {
    std::vector<std::filesystem::directory_entry> entries;

  for (const auto &entry : std::filesystem::directory_iterator(directory)) {
    if (entry.path().filename().string()[0] != '.') {
      entries.push_back(entry);
    }
  }

  sort(entries.begin(), entries.end(), [](const std::filesystem::directory_entry &left, const std::filesystem::directory_entry &right) -> bool {
    return left.path().filename() < right.path().filename();
  });

  for (size_t index = 0; index < entries.size(); index++) {
    std::filesystem::directory_entry entry = entries[index];
    std::vector<std::string> pointers = index == entries.size() - 1 ? final_pointers : inner_pointers;

    std::cout << prefix << pointers[0] << entry.path().filename().string() << std::endl;

    if (!entry.is_directory()) {
      files++;
    } else {
      dirs++;
      walk(entry.path(), prefix + pointers[1]);
    }
  }
}

void Tree::summary() {
  std::cout << "\n" << dirs << " directories," << " " << files << " files" << std::endl;
}
